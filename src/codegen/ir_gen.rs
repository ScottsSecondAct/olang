use std::collections::HashMap;

use inkwell::{
    builder::Builder,
    context::Context,
    module::Module,
    types::{BasicMetadataTypeEnum, BasicType, BasicTypeEnum},
    values::{BasicMetadataValueEnum, BasicValue, BasicValueEnum, FunctionValue, PointerValue},
    AddressSpace, FloatPredicate, IntPredicate,
};

use crate::parser::ast::{
    BinOp, Expr, ExprKind, Lit, Program, PrimitiveKind, Stmt, StmtKind, Transformation, Type,
    UnOp,
};

// ── Variable slot: pointer + type (required for LLVM ≥15 opaque pointers) ─────

#[derive(Clone)]
struct VarSlot<'ctx> {
    ptr: PointerValue<'ctx>,
    ty: BasicTypeEnum<'ctx>,
}

// ── IR Generator ─────────────────────────────────────────────────────────────

pub struct IrGen<'ctx> {
    context: &'ctx Context,
    module: Module<'ctx>,
    builder: Builder<'ctx>,
    /// Named values in the current function scope (stack of maps).
    scopes: Vec<HashMap<String, VarSlot<'ctx>>>,
    /// Currently compiled function.
    current_fn: Option<FunctionValue<'ctx>>,
}

impl<'ctx> IrGen<'ctx> {
    pub fn new(context: &'ctx Context, module_name: &str) -> Self {
        Self {
            context,
            module: context.create_module(module_name),
            builder: context.create_builder(),
            scopes: vec![HashMap::new()],
            current_fn: None,
        }
    }

    pub fn module(&self) -> &Module<'ctx> { &self.module }

    /// Emit LLVM IR text.
    pub fn emit_ir(&self) -> String {
        self.module.print_to_string().to_string()
    }

    /// Verify module integrity.
    pub fn verify(&self) -> Result<(), String> {
        self.module.verify().map_err(|e| e.to_string())
    }

    // ── Scope helpers ─────────────────────────────────────────────────────

    fn push_scope(&mut self) { self.scopes.push(HashMap::new()); }
    fn pop_scope(&mut self)  { if self.scopes.len() > 1 { self.scopes.pop(); } }

    fn define_var(&mut self, name: &str, ptr: PointerValue<'ctx>, ty: BasicTypeEnum<'ctx>) {
        self.scopes.last_mut().unwrap().insert(name.to_owned(), VarSlot { ptr, ty });
    }

    fn lookup_var(&self, name: &str) -> Option<VarSlot<'ctx>> {
        for scope in self.scopes.iter().rev() {
            if let Some(slot) = scope.get(name) { return Some(slot.clone()); }
        }
        None
    }

    // ── Opaque pointer helper ─────────────────────────────────────────────

    fn ptr_type(&self) -> BasicTypeEnum<'ctx> {
        self.context.ptr_type(AddressSpace::default()).into()
    }

    // ── Type mapping ──────────────────────────────────────────────────────

    pub fn llvm_type(&self, ty: &Type) -> BasicTypeEnum<'ctx> {
        match ty {
            Type::Primitive(k) => match k {
                PrimitiveKind::Bool   => self.context.bool_type().into(),
                PrimitiveKind::Int    => self.context.i64_type().into(),
                PrimitiveKind::Long   => self.context.i64_type().into(),
                PrimitiveKind::Char   => self.context.i8_type().into(),
                PrimitiveKind::Float  => self.context.f32_type().into(),
                PrimitiveKind::Double => self.context.f64_type().into(),
                // String, null, any, never → opaque pointer
                _ => self.ptr_type(),
            },
            Type::Function { params, ret } => {
                let ret_ty = self.llvm_type(ret);
                let param_tys: Vec<BasicMetadataTypeEnum<'ctx>> =
                    params.iter().map(|p| self.llvm_type(p).into()).collect();
                let _ = ret_ty.fn_type(&param_tys, false);
                self.ptr_type()
            }
            Type::Optional(inner) => self.llvm_type(inner),
            Type::Union(ts)       => ts.first().map(|t| self.llvm_type(t)).unwrap_or_else(|| self.ptr_type()),
            // All composite types map to opaque pointer
            _ => self.ptr_type(),
        }
    }

    // ── Program codegen ───────────────────────────────────────────────────

    pub fn compile_program(&mut self, program: &Program) -> Result<(), String> {
        for stmt in &program.stmts {
            self.compile_stmt(stmt)?;
        }
        Ok(())
    }

    // ── Statement codegen ─────────────────────────────────────────────────

    fn compile_stmt(&mut self, stmt: &Stmt) -> Result<(), String> {
        match &stmt.kind {
            StmtKind::Function { name, params, ret, body } => {
                self.compile_function(name, params, ret, body)?;
            }
            StmtKind::Binding { name, ty, value } => {
                self.compile_top_level_binding(name, ty.as_ref(), value)?;
            }
            StmtKind::TypeDecl { .. }
            | StmtKind::AnnotationType { .. }
            | StmtKind::Import(_) => {}
            StmtKind::Agent { members, .. } => {
                for m in members {
                    use crate::parser::ast::AgentMember;
                    if let AgentMember::Decl(decl) = m {
                        self.compile_stmt(decl)?;
                    }
                }
            }
            StmtKind::Expr(e) => { self.compile_expr(e)?; }
            _ => {}
        }
        Ok(())
    }

    fn compile_top_level_binding(
        &mut self,
        name: &str,
        ty: Option<&Type>,
        value: &Expr,
    ) -> Result<(), String> {
        let llvm_ty = ty.map(|t| self.llvm_type(t)).unwrap_or_else(|| self.context.i64_type().into());
        let global = self.module.add_global(llvm_ty, Some(AddressSpace::default()), name);
        global.set_initializer(&llvm_ty.const_zero());

        let fn_ty = self.context.void_type().fn_type(&[], false);
        let init_fn = self.module.add_function(&format!("__init_{name}"), fn_ty, None);
        let bb = self.context.append_basic_block(init_fn, "entry");
        self.builder.position_at_end(bb);
        self.current_fn = Some(init_fn);

        if let Some(v) = self.compile_expr(value)? {
            self.builder.build_store(global.as_pointer_value(), v)
                .map_err(|e| e.to_string())?;
        }
        self.builder.build_return(None).map_err(|e| e.to_string())?;
        self.current_fn = None;
        Ok(())
    }

    // ── Function codegen ──────────────────────────────────────────────────

    fn compile_function(
        &mut self,
        name: &str,
        params: &[crate::parser::ast::TypedParam],
        ret: &Type,
        body: &Expr,
    ) -> Result<FunctionValue<'ctx>, String> {
        let param_types: Vec<BasicMetadataTypeEnum<'ctx>> = params
            .iter()
            .map(|p| self.llvm_type(&p.ty).into())
            .collect();

        let ret_type = self.llvm_type(ret);
        let fn_type = ret_type.fn_type(&param_types, false);
        let function = self.module.add_function(name, fn_type, None);

        let entry = self.context.append_basic_block(function, "entry");
        self.builder.position_at_end(entry);

        let prev_fn = self.current_fn.replace(function);
        self.push_scope();

        // Bind parameters as alloca'd locals
        for (i, param) in params.iter().enumerate() {
            let llvm_ty = self.llvm_type(&param.ty);
            let alloca = self.builder
                .build_alloca(llvm_ty, &param.name)
                .map_err(|e| e.to_string())?;
            let param_val = function.get_nth_param(i as u32)
                .ok_or_else(|| format!("missing param {i}"))?;
            self.builder.build_store(alloca, param_val).map_err(|e| e.to_string())?;
            self.define_var(&param.name, alloca, llvm_ty);
        }

        let result = self.compile_expr(body)?;
        match result {
            Some(v) => { self.builder.build_return(Some(&v)).map_err(|e| e.to_string())?; }
            None    => { self.builder.build_return(None).map_err(|e| e.to_string())?; }
        }

        self.pop_scope();
        self.current_fn = prev_fn;
        Ok(function)
    }

    // ── Expression codegen ────────────────────────────────────────────────

    fn compile_expr(&mut self, expr: &Expr) -> Result<Option<BasicValueEnum<'ctx>>, String> {
        match &expr.kind {
            ExprKind::Lit(lit) => Ok(Some(self.compile_lit(lit)?)),

            ExprKind::Ident(name) => self.compile_ident(name),

            ExprKind::Qualified(parts) => self.compile_ident(&parts.join(".")),

            ExprKind::Binary { op, lhs, rhs } =>
                Ok(Some(self.compile_binary(op, lhs, rhs)?)),

            ExprKind::Unary { op, operand } =>
                Ok(Some(self.compile_unary(op, operand)?)),

            ExprKind::Call { callee, args } =>
                self.compile_call(callee, args),

            ExprKind::Block(transformations) =>
                self.compile_block(transformations),

            ExprKind::Lambda { params, body } => {
                let fn_name = format!("__lambda_{}", self.lambda_count());
                let typed_params: Vec<crate::parser::ast::TypedParam> = params
                    .iter()
                    .map(|p| crate::parser::ast::TypedParam {
                        name: p.name.clone(),
                        ty: p.ty.clone().unwrap_or(Type::Primitive(PrimitiveKind::Any)),
                    })
                    .collect();
                let ret_ty = Type::Primitive(PrimitiveKind::Any);
                let fn_val = self.compile_function(&fn_name, &typed_params, &ret_ty, body)?;
                Ok(Some(fn_val.as_global_value().as_pointer_value().into()))
            }

            ExprKind::Match { subject, arms } =>
                self.compile_match(subject, arms),

            ExprKind::Ternary { cond, then, else_ } =>
                self.compile_ternary(cond, then, else_),

            ExprKind::NullCoalesce { lhs, rhs } => {
                let lhs_val = self.compile_expr(lhs)?;
                let rhs_val = self.compile_expr(rhs)?;
                Ok(lhs_val.or(rhs_val))
            }

            // Functional combinators — runtime call stubs
            ExprKind::Map { func, collection }          => self.compile_runtime_call("olang_map",      &[func, collection]),
            ExprKind::Filter { collection, pred }        => self.compile_runtime_call("olang_filter",   &[collection, pred]),
            ExprKind::Reduce { collection, func, init } => {
                let mut args: Vec<&Expr> = vec![collection, func];
                if let Some(i) = init.as_deref() { args.push(i); }
                self.compile_runtime_call("olang_reduce", &args)
            }
            ExprKind::Foreach { collection, func }   => self.compile_runtime_call("olang_foreach",  &[collection, func]),
            ExprKind::GroupBy { collection, key_fn } => self.compile_runtime_call("olang_group_by", &[collection, key_fn]),
            ExprKind::FlatMap { collection, func }   => self.compile_runtime_call("olang_flatmap",  &[collection, func]),
            ExprKind::Zip { left, right, combiner }  => {
                let mut args: Vec<&Expr> = vec![left, right];
                if let Some(c) = combiner.as_deref() { args.push(c); }
                self.compile_runtime_call("olang_zip", &args)
            }
            ExprKind::Partition { collection, pred }    => self.compile_runtime_call("olang_partition", &[collection, pred]),
            ExprKind::Take { collection, n }            => self.compile_runtime_call("olang_take",      &[collection, n]),
            ExprKind::Drop { collection, n }            => self.compile_runtime_call("olang_drop",      &[collection, n]),
            ExprKind::TakeWhile { collection, pred }    => self.compile_runtime_call("olang_take_while",&[collection, pred]),
            ExprKind::DropWhile { collection, pred }    => self.compile_runtime_call("olang_drop_while",&[collection, pred]),
            ExprKind::SortBy { collection, key_fn }     => self.compile_runtime_call("olang_sort_by",   &[collection, key_fn]),
            ExprKind::Distinct { collection, eq_fn }    => {
                let mut args: Vec<&Expr> = vec![collection];
                if let Some(f) = eq_fn.as_deref() { args.push(f); }
                self.compile_runtime_call("olang_distinct", &args)
            }
            ExprKind::Count { collection, pred }        => {
                let mut args: Vec<&Expr> = vec![collection];
                if let Some(p) = pred.as_deref() { args.push(p); }
                self.compile_runtime_call("olang_count", &args)
            }
            ExprKind::Find { collection, pred }      => self.compile_runtime_call("olang_find",    &[collection, pred]),
            ExprKind::Any  { collection, pred }      => self.compile_runtime_call("olang_any",     &[collection, pred]),
            ExprKind::All  { collection, pred }      => self.compile_runtime_call("olang_all",     &[collection, pred]),
            ExprKind::Join { left, right, on, select } => {
                let mut args: Vec<&Expr> = vec![left, right, on];
                if let Some(s) = select.as_deref() { args.push(s); }
                self.compile_runtime_call("olang_join", &args)
            }
            ExprKind::Window { collection, size, step } => {
                let mut args: Vec<&Expr> = vec![collection, size];
                if let Some(s) = step.as_deref() { args.push(s); }
                self.compile_runtime_call("olang_window", &args)
            }
            ExprKind::Chunk { collection, size }        => self.compile_runtime_call("olang_chunk",   &[collection, size]),
            ExprKind::Scan { collection, func, init }   => {
                let mut args: Vec<&Expr> = vec![collection, func];
                if let Some(i) = init.as_deref() { args.push(i); }
                self.compile_runtime_call("olang_scan", &args)
            }
            ExprKind::Collect { collection, func, init } =>
                self.compile_runtime_call("olang_collect", &[collection, func, init]),

            ExprKind::Always(e) | ExprKind::Eventually(e) => self.compile_expr(e),
            ExprKind::During { operand, .. } | ExprKind::Until { operand, .. } => self.compile_expr(operand),
            ExprKind::When { cond, body } => {
                // Temporal implication: compile as ternary (cond ? body : unit)
                self.compile_ternary(cond, body, &Expr::new(
                    ExprKind::Lit(Lit::Bool(true)), body.span.clone()))
            }

            ExprKind::Try(inner) => self.compile_expr(inner),

            ExprKind::List(items) => self.compile_list_literal(items),

            ExprKind::Object(_) => Ok(Some(self.context.ptr_type(AddressSpace::default()).const_null().into())),

            ExprKind::Member { object, .. } => self.compile_expr(object),

            ExprKind::Index { object, .. } => self.compile_expr(object),

            ExprKind::Mutation { target, .. } => self.compile_expr(target),

            ExprKind::Range { lo, hi, .. } => {
                self.compile_expr(hi)?;
                self.compile_expr(lo)
            }
        }
    }

    fn lambda_count(&self) -> usize {
        let mut count = 0;
        let mut it = self.module.get_first_function();
        while let Some(f) = it {
            if f.get_name().to_str().map(|n| n.starts_with("__lambda_")).unwrap_or(false) {
                count += 1;
            }
            it = f.get_next_function();
        }
        count
    }

    // ── Literal codegen ───────────────────────────────────────────────────

    fn compile_lit(&self, lit: &Lit) -> Result<BasicValueEnum<'ctx>, String> {
        Ok(match lit {
            Lit::Bool(b)  => self.context.bool_type().const_int(*b as u64, false).into(),
            Lit::Int(i)   => self.context.i64_type().const_int(*i as u64, true).into(),
            Lit::Float(f) => self.context.f64_type().const_float(*f).into(),
            Lit::Str(s)   => {
                let gstr = self.builder.build_global_string_ptr(s, ".str")
                    .map_err(|e| e.to_string())?;
                gstr.as_pointer_value().into()
            }
            Lit::Null => self.context.ptr_type(AddressSpace::default()).const_null().into(),
        })
    }

    // ── Identifier load ───────────────────────────────────────────────────

    fn compile_ident(&mut self, name: &str) -> Result<Option<BasicValueEnum<'ctx>>, String> {
        if let Some(slot) = self.lookup_var(name) {
            // LLVM ≥15: build_load requires explicit type
            let val = self.builder
                .build_load(slot.ty, slot.ptr, name)
                .map_err(|e| e.to_string())?;
            return Ok(Some(val));
        }
        if let Some(g) = self.module.get_global(name) {
            // For globals: type is the value type (stored at definition time)
            // We use i64 as a safe fallback
            let ty = self.context.i64_type();
            let val = self.builder
                .build_load(ty, g.as_pointer_value(), name)
                .map_err(|e| e.to_string())?;
            return Ok(Some(val));
        }
        if let Some(f) = self.module.get_function(name) {
            return Ok(Some(f.as_global_value().as_pointer_value().into()));
        }
        Err(format!("undefined variable '{name}'"))
    }

    // ── Binary ops ────────────────────────────────────────────────────────

    fn compile_binary(&mut self, op: &BinOp, lhs: &Expr, rhs: &Expr) -> Result<BasicValueEnum<'ctx>, String> {
        let lv = self.compile_expr(lhs)?.ok_or("lhs has no value")?;
        let rv = self.compile_expr(rhs)?.ok_or("rhs has no value")?;

        Ok(match (lv, rv) {
            (BasicValueEnum::IntValue(l), BasicValueEnum::IntValue(r)) => match op {
                BinOp::Add => self.builder.build_int_add(l, r, "add").map_err(|e| e.to_string())?.into(),
                BinOp::Sub => self.builder.build_int_sub(l, r, "sub").map_err(|e| e.to_string())?.into(),
                BinOp::Mul => self.builder.build_int_mul(l, r, "mul").map_err(|e| e.to_string())?.into(),
                BinOp::Div => self.builder.build_int_signed_div(l, r, "div").map_err(|e| e.to_string())?.into(),
                BinOp::Mod => self.builder.build_int_signed_rem(l, r, "mod").map_err(|e| e.to_string())?.into(),
                BinOp::And => self.builder.build_and(l, r, "and").map_err(|e| e.to_string())?.into(),
                BinOp::Or  => self.builder.build_or(l, r, "or").map_err(|e| e.to_string())?.into(),
                BinOp::Eq  => self.builder.build_int_compare(IntPredicate::EQ,  l, r, "eq").map_err(|e| e.to_string())?.into(),
                BinOp::Neq => self.builder.build_int_compare(IntPredicate::NE,  l, r, "neq").map_err(|e| e.to_string())?.into(),
                BinOp::Lt  => self.builder.build_int_compare(IntPredicate::SLT, l, r, "lt").map_err(|e| e.to_string())?.into(),
                BinOp::Le  => self.builder.build_int_compare(IntPredicate::SLE, l, r, "le").map_err(|e| e.to_string())?.into(),
                BinOp::Gt  => self.builder.build_int_compare(IntPredicate::SGT, l, r, "gt").map_err(|e| e.to_string())?.into(),
                BinOp::Ge  => self.builder.build_int_compare(IntPredicate::SGE, l, r, "ge").map_err(|e| e.to_string())?.into(),
                _ => lv,
            },
            (BasicValueEnum::FloatValue(l), BasicValueEnum::FloatValue(r)) => match op {
                BinOp::Add => self.builder.build_float_add(l, r, "fadd").map_err(|e| e.to_string())?.into(),
                BinOp::Sub => self.builder.build_float_sub(l, r, "fsub").map_err(|e| e.to_string())?.into(),
                BinOp::Mul => self.builder.build_float_mul(l, r, "fmul").map_err(|e| e.to_string())?.into(),
                BinOp::Div => self.builder.build_float_div(l, r, "fdiv").map_err(|e| e.to_string())?.into(),
                BinOp::Mod => self.builder.build_float_rem(l, r, "fmod").map_err(|e| e.to_string())?.into(),
                BinOp::Eq  => self.builder.build_float_compare(FloatPredicate::OEQ, l, r, "feq").map_err(|e| e.to_string())?.into(),
                BinOp::Neq => self.builder.build_float_compare(FloatPredicate::ONE, l, r, "fneq").map_err(|e| e.to_string())?.into(),
                BinOp::Lt  => self.builder.build_float_compare(FloatPredicate::OLT, l, r, "flt").map_err(|e| e.to_string())?.into(),
                BinOp::Le  => self.builder.build_float_compare(FloatPredicate::OLE, l, r, "fle").map_err(|e| e.to_string())?.into(),
                BinOp::Gt  => self.builder.build_float_compare(FloatPredicate::OGT, l, r, "fgt").map_err(|e| e.to_string())?.into(),
                BinOp::Ge  => self.builder.build_float_compare(FloatPredicate::OGE, l, r, "fge").map_err(|e| e.to_string())?.into(),
                _ => lv,
            },
            (lv, _) => lv, // Pipeline/parallel and other combinator ops pass through
        })
    }

    // ── Unary ops ─────────────────────────────────────────────────────────

    fn compile_unary(&mut self, op: &UnOp, operand: &Expr) -> Result<BasicValueEnum<'ctx>, String> {
        let val = self.compile_expr(operand)?.ok_or("unary operand has no value")?;
        Ok(match (op, val) {
            (UnOp::Neg, BasicValueEnum::IntValue(v)) =>
                self.builder.build_int_neg(v, "neg").map_err(|e| e.to_string())?.into(),
            (UnOp::Neg, BasicValueEnum::FloatValue(v)) =>
                self.builder.build_float_neg(v, "fneg").map_err(|e| e.to_string())?.into(),
            (UnOp::Not, BasicValueEnum::IntValue(v)) =>
                self.builder.build_not(v, "not").map_err(|e| e.to_string())?.into(),
            _ => val,
        })
    }

    // ── Call codegen ──────────────────────────────────────────────────────

    fn compile_call(
        &mut self,
        callee: &Expr,
        args: &[crate::parser::ast::Argument],
    ) -> Result<Option<BasicValueEnum<'ctx>>, String> {
        let fn_name = match &callee.kind {
            ExprKind::Ident(n)      => n.clone(),
            ExprKind::Qualified(p)  => p.join("."),
            ExprKind::Member { member, .. } => member.clone(),
            _ => return Err("indirect calls not yet supported".to_owned()),
        };

        let func = self.module.get_function(&fn_name)
            .ok_or_else(|| format!("undefined function '{fn_name}'"))?;

        // Compile args first (need mutable borrow), then build call
        let mut arg_vals: Vec<BasicValueEnum<'ctx>> = Vec::new();
        // Clone the args list to avoid borrow issues
        let arg_exprs: Vec<crate::parser::ast::Argument> = args.to_vec();
        for a in &arg_exprs {
            if let Some(v) = self.compile_expr(&a.value)? {
                arg_vals.push(v);
            }
        }
        let compiled: Vec<BasicMetadataValueEnum<'ctx>> =
            arg_vals.iter().map(|v| (*v).into()).collect();

        let call = self.builder
            .build_call(func, &compiled, "call")
            .map_err(|e| e.to_string())?;
        // inkwell 0.9: try_as_basic_value() → ValueKind<'ctx>; use .basic()
        Ok(call.try_as_basic_value().basic())
    }

    // ── Block codegen ─────────────────────────────────────────────────────

    fn compile_block(&mut self, body: &[Transformation]) -> Result<Option<BasicValueEnum<'ctx>>, String> {
        self.push_scope();
        let mut last = None;
        for t in body {
            match t {
                Transformation::Let { name, ty, value } => {
                    let llvm_ty = ty.as_ref().map(|t| self.llvm_type(t))
                        .unwrap_or_else(|| self.context.i64_type().into());
                    let alloca = self.builder.build_alloca(llvm_ty, name)
                        .map_err(|e| e.to_string())?;
                    if let Some(v) = self.compile_expr(value)? {
                        self.builder.build_store(alloca, v).map_err(|e| e.to_string())?;
                    }
                    self.define_var(name, alloca, llvm_ty);
                    last = None;
                }
                Transformation::Expr(e) => {
                    last = self.compile_expr(e)?;
                }
            }
        }
        self.pop_scope();
        Ok(last)
    }

    // ── Ternary codegen ───────────────────────────────────────────────────

    fn compile_ternary(
        &mut self,
        cond: &Expr,
        then: &Expr,
        else_: &Expr,
    ) -> Result<Option<BasicValueEnum<'ctx>>, String> {
        let func = self.current_fn.ok_or("ternary outside function")?;
        let cond_val = self.compile_expr(cond)?.ok_or("ternary cond has no value")?;
        let bool_val = match cond_val {
            BasicValueEnum::IntValue(v) => v,
            _ => return Err("ternary condition must be bool/int".into()),
        };

        let then_bb  = self.context.append_basic_block(func, "then");
        let else_bb  = self.context.append_basic_block(func, "else");
        let merge_bb = self.context.append_basic_block(func, "merge");

        self.builder.build_conditional_branch(bool_val, then_bb, else_bb)
            .map_err(|e| e.to_string())?;

        self.builder.position_at_end(then_bb);
        let then_val = self.compile_expr(then)?;
        self.builder.build_unconditional_branch(merge_bb).map_err(|e| e.to_string())?;
        let then_end = self.builder.get_insert_block().unwrap();

        self.builder.position_at_end(else_bb);
        let else_val = self.compile_expr(else_)?;
        self.builder.build_unconditional_branch(merge_bb).map_err(|e| e.to_string())?;
        let else_end = self.builder.get_insert_block().unwrap();

        self.builder.position_at_end(merge_bb);
        match (then_val, else_val) {
            (Some(tv), Some(ev)) => {
                let phi = self.builder
                    .build_phi(tv.get_type(), "ternary")
                    .map_err(|e| e.to_string())?;
                // inkwell 0.9 add_incoming takes &[(&dyn BasicValue, BasicBlock)]
                phi.add_incoming(&[
                    (&tv as &dyn BasicValue<'ctx>, then_end),
                    (&ev as &dyn BasicValue<'ctx>, else_end),
                ]);
                Ok(Some(phi.as_basic_value()))
            }
            _ => Ok(None),
        }
    }

    // ── Match codegen ─────────────────────────────────────────────────────

    fn compile_match(
        &mut self,
        subject: &Expr,
        arms: &[crate::parser::ast::MatchArm],
    ) -> Result<Option<BasicValueEnum<'ctx>>, String> {
        let func = self.current_fn.ok_or("match outside function")?;
        let subj_val = self.compile_expr(subject)?;
        let merge_bb = self.context.append_basic_block(func, "match.merge");

        // Collect arm results for phi
        let mut phi_incoming: Vec<(BasicValueEnum<'ctx>, inkwell::basic_block::BasicBlock<'ctx>)> = Vec::new();
        let mut current_bb = self.builder.get_insert_block().unwrap();

        for (i, arm) in arms.iter().enumerate() {
            let arm_bb  = self.context.append_basic_block(func, &format!("arm.{i}"));
            let next_bb = if i + 1 < arms.len() {
                self.context.append_basic_block(func, &format!("arm.{i}.skip"))
            } else {
                merge_bb
            };

            self.builder.position_at_end(current_bb);
            let test = self.compile_pattern_test(&arm.pattern, subj_val.as_ref())?;
            if let Some(cond) = test {
                self.builder.build_conditional_branch(cond, arm_bb, next_bb)
                    .map_err(|e| e.to_string())?;
            } else {
                self.builder.build_unconditional_branch(arm_bb)
                    .map_err(|e| e.to_string())?;
            }

            self.builder.position_at_end(arm_bb);
            let arm_val = self.compile_expr(&arm.body)?;
            self.builder.build_unconditional_branch(merge_bb).map_err(|e| e.to_string())?;
            let arm_end = self.builder.get_insert_block().unwrap();
            if let Some(v) = arm_val { phi_incoming.push((v, arm_end)); }

            current_bb = next_bb;
        }

        self.builder.position_at_end(merge_bb);
        if phi_incoming.is_empty() { return Ok(None); }

        let result_ty = phi_incoming[0].0.get_type();
        let phi = self.builder
            .build_phi(result_ty, "match.result")
            .map_err(|e| e.to_string())?;
        let refs: Vec<(&dyn BasicValue<'ctx>, inkwell::basic_block::BasicBlock<'ctx>)> =
            phi_incoming.iter().map(|(v, bb)| (v as &dyn BasicValue<'ctx>, *bb)).collect();
        phi.add_incoming(&refs);
        Ok(Some(phi.as_basic_value()))
    }

    fn compile_pattern_test(
        &mut self,
        pattern: &crate::parser::ast::Pattern,
        subject: Option<&BasicValueEnum<'ctx>>,
    ) -> Result<Option<inkwell::values::IntValue<'ctx>>, String> {
        use crate::parser::ast::Pattern;
        match pattern {
            Pattern::Wildcard | Pattern::Ident(_) => Ok(None),
            Pattern::Literal(lit) => {
                let lit_val = self.compile_lit(lit)?;
                match (subject, lit_val) {
                    (Some(BasicValueEnum::IntValue(sv)), BasicValueEnum::IntValue(lv)) => {
                        let cmp = self.builder
                            .build_int_compare(IntPredicate::EQ, *sv, lv, "pat.eq")
                            .map_err(|e| e.to_string())?;
                        Ok(Some(cmp))
                    }
                    _ => Ok(None),
                }
            }
            _ => Ok(None),
        }
    }

    // ── List literal ──────────────────────────────────────────────────────

    fn compile_list_literal(&mut self, items: &[Expr]) -> Result<Option<BasicValueEnum<'ctx>>, String> {
        for item in items { self.compile_expr(item)?; }
        Ok(Some(self.context.ptr_type(AddressSpace::default()).const_null().into()))
    }

    // ── Runtime call stub ─────────────────────────────────────────────────

    fn compile_runtime_call(
        &mut self,
        name: &str,
        args: &[&Expr],
    ) -> Result<Option<BasicValueEnum<'ctx>>, String> {
        let ret_ty = self.context.ptr_type(AddressSpace::default());
        let param_tys: Vec<BasicMetadataTypeEnum<'ctx>> =
            args.iter().map(|_| ret_ty.into()).collect();
        let fn_ty = ret_ty.fn_type(&param_tys, false);
        let func = self.module.get_function(name)
            .unwrap_or_else(|| self.module.add_function(name, fn_ty, None));

        // Compile all arg exprs, cast non-pointer values to ptr via alloca
        let arg_exprs: Vec<&Expr> = args.to_vec();
        let mut compiled: Vec<BasicValueEnum<'ctx>> = Vec::new();
        for e in &arg_exprs {
            if let Some(v) = self.compile_expr(e)? {
                let pv = match v {
                    BasicValueEnum::PointerValue(p) => p,
                    other => {
                        let alloca = self.builder.build_alloca(other.get_type(), "tmp")
                            .map_err(|e| e.to_string())?;
                        self.builder.build_store(alloca, other).map_err(|e| e.to_string())?;
                        alloca
                    }
                };
                compiled.push(pv.into());
            }
        }
        let meta: Vec<BasicMetadataValueEnum<'ctx>> = compiled.iter().map(|v| (*v).into()).collect();

        let call = self.builder
            .build_call(func, &meta, name)
            .map_err(|e| e.to_string())?;
        Ok(call.try_as_basic_value().basic())
    }

    // ── main stub ─────────────────────────────────────────────────────────

    /// Emit a `main` function that calls all `__init_*` initializers.
    pub fn emit_main_stub(&mut self) {
        let i32_t = self.context.i32_type();
        let main_fn = self.module.add_function("main", i32_t.fn_type(&[], false), None);
        let entry = self.context.append_basic_block(main_fn, "entry");
        self.builder.position_at_end(entry);

        let mut inits: Vec<FunctionValue<'ctx>> = Vec::new();
        let mut it = self.module.get_first_function();
        while let Some(f) = it {
            if f.get_name().to_str().map(|n| n.starts_with("__init_")).unwrap_or(false) {
                inits.push(f);
            }
            it = f.get_next_function();
        }
        for f in inits {
            self.builder.build_call(f, &[], "").expect("call init");
        }
        self.builder.build_return(Some(&i32_t.const_zero())).expect("return");
    }
}
