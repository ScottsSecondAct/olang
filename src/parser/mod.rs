pub mod ast;

use ast::*;
use pest::iterators::{Pair, Pairs};
use pest::Parser as PestParser;
use pest_derive::Parser;
use thiserror::Error;

use crate::lexer::Span;

#[derive(Parser)]
#[grammar = "parser/olang.pest"]
struct OLangParser;

// ── Error type ────────────────────────────────────────────────────────────────

#[derive(Debug, Error, Clone)]
pub enum ParseError {
    #[error("{0}")]
    Pest(String),
}

pub type ParseResult<T> = Result<T, ParseError>;

// ── Public entry point ────────────────────────────────────────────────────────

pub fn parse(source: &str) -> ParseResult<Program> {
    let pairs = OLangParser::parse(Rule::program, source)
        .map_err(|e| ParseError::Pest(e.to_string()))?;
    let prog = pairs.into_iter().next().unwrap();
    Ok(build_program(prog))
}

// ── Span helper ───────────────────────────────────────────────────────────────

fn pair_span(p: &Pair<Rule>) -> Span {
    let s = p.as_span();
    s.start()..s.end()
}

// ── Program ───────────────────────────────────────────────────────────────────

fn build_program(pair: Pair<Rule>) -> Program {
    let stmts = pair.into_inner()
        .filter(|p| p.as_rule() != Rule::EOI)
        .map(build_stmt)
        .collect();
    Program { stmts }
}

// ── Statements ────────────────────────────────────────────────────────────────

fn build_stmt(pair: Pair<Rule>) -> Stmt {
    let span = pair_span(&pair);
    let kind = match pair.as_rule() {
        Rule::import_stmt        => StmtKind::Import(build_import(pair)),
        Rule::let_binding        => build_let_binding(pair),
        Rule::function_def       => build_function_def(pair),
        Rule::pipeline_decl      => build_pipeline_decl(pair),
        Rule::type_decl          => build_type_decl(pair),
        Rule::annotation_type_decl => build_annotation_type_decl(pair),
        Rule::annotated_stmt     => build_annotated_stmt(pair),
        Rule::agent_decl         => build_agent_decl(pair),
        Rule::solver_decl        => build_solver_decl(pair),
        Rule::proof_decl         => build_proof_decl(pair),
        Rule::emit_stmt          => { let e = build_expr(inner_first(pair)); StmtKind::Emit(e) }
        Rule::signal_stmt        => {
            let mut inner = pair.into_inner();
            let stream = build_expr(inner.next().unwrap());
            let value  = build_expr(inner.next().unwrap());
            StmtKind::Signal(stream, value)
        }
        Rule::assert_stmt        => { let e = build_expr(inner_first(pair)); StmtKind::Assert(e) }
        Rule::assign_stmt        => build_assign_stmt(pair),
        Rule::expr_stmt          => StmtKind::Expr(build_expr(inner_first(pair))),
        Rule::stmt               => return build_stmt(inner_first(pair)),
        r => panic!("unexpected stmt rule: {r:?}"),
    };
    Stmt { kind, span }
}

fn build_import(pair: Pair<Rule>) -> ImportDecl {
    let mut inner = pair.into_inner();
    let first = inner.next().unwrap();
    if first.as_rule() == Rule::qualified_name {
        // from <module> import <targets>
        let module = first.as_str().to_owned();
        let targets_pair = inner.next().unwrap();
        let targets = build_import_targets(targets_pair);
        ImportDecl::From { module, targets }
    } else {
        // import <dotted_as_name> (, <dotted_as_name>)*
        // first is the first dotted_as_name
        let mut items = vec![build_dotted_as_name(first)];
        for p in inner {
            items.push(build_dotted_as_name(p));
        }
        ImportDecl::Dotted(items)
    }
}

fn build_dotted_as_name(pair: Pair<Rule>) -> DottedAsName {
    let mut inner = pair.into_inner();
    let qn = inner.next().unwrap();
    let path = qn.into_inner().map(|p| p.as_str().to_owned()).collect();
    let alias = inner.next().map(|p| p.as_str().to_owned());
    DottedAsName { path, alias }
}

fn build_import_targets(pair: Pair<Rule>) -> ImportTargets {
    if pair.as_str() == "*" {
        return ImportTargets::Star;
    }
    let names = pair.into_inner().map(|p| {
        let mut inner = p.into_inner();
        let name  = inner.next().unwrap().as_str().to_owned();
        let alias = inner.next().map(|a| a.as_str().to_owned());
        ImportAsName { name, alias }
    }).collect();
    ImportTargets::Named(names)
}

fn build_let_binding(pair: Pair<Rule>) -> StmtKind {
    let mut inner = pair.into_inner();
    let name  = inner.next().unwrap().as_str().to_owned();
    let (ty, value) = extract_ty_and_expr(inner);
    StmtKind::Binding { name, ty, value }
}

fn build_function_def(pair: Pair<Rule>) -> StmtKind {
    let mut inner = pair.into_inner();
    let name = inner.next().unwrap().as_str().to_owned();
    let mut params = Vec::new();
    let mut ret_ty = None;
    let mut body_expr = None;
    for p in inner {
        match p.as_rule() {
            Rule::typed_param_list => params = build_typed_param_list(p),
            Rule::ty               => ret_ty = Some(build_type(p)),
            _                      => body_expr = Some(build_expr(p)),
        }
    }
    StmtKind::Function {
        name,
        params,
        ret: ret_ty.unwrap_or(Type::Primitive(PrimitiveKind::Any)),
        body: body_expr.unwrap(),
    }
}

fn build_pipeline_decl(pair: Pair<Rule>) -> StmtKind {
    let mut inner = pair.into_inner();
    let name   = inner.next().unwrap().as_str().to_owned();
    let input  = build_type(inner.next().unwrap());
    let output = build_type(inner.next().unwrap());
    let body   = build_expr(inner.next().unwrap());
    StmtKind::Pipeline { name, input, output, body }
}

fn build_type_decl(pair: Pair<Rule>) -> StmtKind {
    let mut inner = pair.into_inner();
    let name = inner.next().unwrap().as_str().to_owned();
    let mut generics = Vec::new();
    let mut fields   = Vec::new();
    let mut where_cl = Vec::new();
    for p in inner {
        match p.as_rule() {
            Rule::generic_params  => generics = build_generic_params(p),
            Rule::typed_field_list => fields  = build_typed_field_list(p),
            Rule::where_clause    => where_cl = build_where_clause(p),
            _ => {}
        }
    }
    StmtKind::TypeDecl { name, generics, fields, where_clause: where_cl }
}

fn build_annotation_type_decl(pair: Pair<Rule>) -> StmtKind {
    let mut inner = pair.into_inner();
    let name   = inner.next().unwrap().as_str().to_owned();
    let fields = build_typed_field_list(inner.next().unwrap());
    StmtKind::AnnotationType { name, fields }
}

fn build_annotated_stmt(pair: Pair<Rule>) -> StmtKind {
    let mut inner = pair.into_inner();
    let decl_pair = inner.next().unwrap();
    let decl = build_stmt(decl_pair);
    let annotations = inner.map(build_annotation_pair).collect();
    StmtKind::Annotation { decl: Box::new(decl), annotations }
}

fn build_annotation_pair(pair: Pair<Rule>) -> AnnotationPair {
    let mut inner = pair.into_inner();
    let key   = inner.next().unwrap().as_str().to_owned();
    let value = build_annotation_value(inner.next().unwrap());
    AnnotationPair { key, value }
}

fn build_annotation_value(pair: Pair<Rule>) -> AnnotationValue {
    match pair.as_rule() {
        Rule::annotation_value => build_annotation_value(inner_first(pair)),
        Rule::list_lit => {
            let items = pair.into_inner().map(build_annotation_value).collect();
            AnnotationValue::List(items)
        }
        Rule::literal => AnnotationValue::Lit(build_literal(pair)),
        _ => AnnotationValue::Lit(build_literal(pair)),
    }
}

fn build_agent_decl(pair: Pair<Rule>) -> StmtKind {
    let mut inner = pair.into_inner();
    let name = inner.next().unwrap().as_str().to_owned();
    let members = inner.map(build_agent_member).collect();
    StmtKind::Agent { name, members }
}

fn build_agent_member(pair: Pair<Rule>) -> AgentMember {
    // agent_member = { capability_member | stream_member | rule_member | stmt }
    let inner = inner_first(pair);
    match inner.as_rule() {
        Rule::capability_member => {
            let caps = inner.into_inner().map(|p| p.as_str().to_owned()).collect();
            AgentMember::Capability(caps)
        }
        Rule::stream_member => {
            let mut i = inner.into_inner();
            let name = i.next().unwrap().as_str().to_owned();
            let ty   = build_type(i.next().unwrap());
            AgentMember::Stream { name, ty }
        }
        Rule::rule_member => {
            let mut i = inner.into_inner();
            let name_raw = i.next().unwrap().as_str();
            let name = name_raw.trim_matches('"').to_owned();
            let when_expr  = build_expr(i.next().unwrap());
            let body_block = build_block_items(i.next().unwrap());
            AgentMember::Rule { name, when: when_expr, body: body_block }
        }
        _ => AgentMember::Decl(Box::new(build_stmt(inner))),
    }
}

fn build_solver_decl(pair: Pair<Rule>) -> StmtKind {
    let mut inner = pair.into_inner();
    let name = inner.next().unwrap().as_str().to_owned();
    let members = inner.map(build_solver_member).collect();
    StmtKind::Solver { name, members }
}

fn build_solver_member(pair: Pair<Rule>) -> SolverMember {
    // solver_member = { variable_member | satisfy_member | minimize_member | maximize_member }
    let inner = inner_first(pair);
    match inner.as_rule() {
        Rule::variable_member => {
            let mut i = inner.into_inner();
            let name   = i.next().unwrap().as_str().to_owned();
            let ty     = build_type(i.next().unwrap());
            let domain = i.next().map(build_expr);
            SolverMember::Variable { name, ty, domain }
        }
        Rule::satisfy_member => {
            let exprs = inner.into_inner().map(build_expr).collect();
            SolverMember::Satisfy(exprs)
        }
        Rule::minimize_member => SolverMember::Minimize(build_expr(inner_first(inner))),
        Rule::maximize_member => SolverMember::Maximize(build_expr(inner_first(inner))),
        r => panic!("unexpected solver member: {r:?}"),
    }
}

fn build_proof_decl(pair: Pair<Rule>) -> StmtKind {
    let mut inner = pair.into_inner();
    let name = inner.next().unwrap().as_str().to_owned();
    let invariants = inner.map(build_invariant_decl).collect();
    StmtKind::Proof { name, invariants }
}

fn build_invariant_decl(pair: Pair<Rule>) -> InvariantDecl {
    let mut inner = pair.into_inner();
    let name = inner.next().unwrap().as_str().to_owned();
    let body = inner.map(build_expr).collect();
    InvariantDecl { name, body }
}

fn build_assign_stmt(pair: Pair<Rule>) -> StmtKind {
    let mut inner = pair.into_inner();
    let qn    = inner.next().unwrap();
    let target = qn.into_inner().map(|p| p.as_str().to_owned()).collect();
    let value  = build_expr(inner.next().unwrap());
    StmtKind::Assign { target, value }
}

// ── Types ─────────────────────────────────────────────────────────────────────

fn build_type(pair: Pair<Rule>) -> Type {
    match pair.as_rule() {
        // ty = { optional_type ~ (union_op ~ optional_type)* }
        // union_op is silent, so inner yields a list of optional_type pairs
        Rule::ty => {
            let mut parts: Vec<Type> = pair.into_inner().map(build_type).collect();
            if parts.len() == 1 { parts.remove(0) } else { Type::Union(parts) }
        }
        Rule::optional_type => {
            let mut inner = pair.into_inner();
            let base = build_type(inner.next().unwrap());
            // opt_mark is present when "?" was written
            if inner.next().is_some() { Type::Optional(Box::new(base)) } else { base }
        }
        Rule::base_type    => build_type(inner_first(pair)),
        Rule::primitive_type => {
            let k = match pair.as_str() {
                "int"       => PrimitiveKind::Int,
                "long"      => PrimitiveKind::Long,
                "float"     => PrimitiveKind::Float,
                "double"    => PrimitiveKind::Double,
                "bool"      => PrimitiveKind::Bool,
                "char"      => PrimitiveKind::Char,
                "string"    => PrimitiveKind::String,
                "any_type"  => PrimitiveKind::Any,
                "never_type"=> PrimitiveKind::Never,
                _           => PrimitiveKind::Any,
            };
            Type::Primitive(k)
        }
        Rule::list_type      => Type::List(Box::new(build_type(inner_first(pair)))),
        Rule::set_type       => Type::Set(Box::new(build_type(inner_first(pair)))),
        Rule::stream_type    => Type::Stream(Box::new(build_type(inner_first(pair)))),
        Rule::future_type    => Type::Future(Box::new(build_type(inner_first(pair)))),
        Rule::option_type    => Type::Option(Box::new(build_type(inner_first(pair)))),
        Rule::provenance_type=> Type::Provenance(Box::new(build_type(inner_first(pair)))),
        Rule::map_type       => {
            let mut i = pair.into_inner();
            let key = build_type(i.next().unwrap());
            let val = build_type(i.next().unwrap());
            Type::Map { key: Box::new(key), value: Box::new(val) }
        }
        Rule::result_type    => {
            let mut i = pair.into_inner();
            let ok  = build_type(i.next().unwrap());
            let err = build_type(i.next().unwrap());
            Type::Result { ok: Box::new(ok), err: Box::new(err) }
        }
        Rule::pipeline_type  => {
            let mut i = pair.into_inner();
            let inp = build_type(i.next().unwrap());
            let out = build_type(i.next().unwrap());
            Type::Pipeline { input: Box::new(inp), output: Box::new(out) }
        }
        Rule::function_type  => {
            let mut i = pair.into_inner();
            let first = i.next().unwrap();
            let (params, ret) = if first.as_rule() == Rule::type_list {
                let ps = first.into_inner().map(build_type).collect();
                let r  = build_type(i.next().unwrap());
                (ps, r)
            } else {
                (Vec::new(), build_type(first))
            };
            Type::Function { params, ret: Box::new(ret) }
        }
        Rule::paren_type     => build_type(inner_first(pair)),
        Rule::user_type      => {
            let mut i = pair.into_inner();
            let name_pair = i.next().unwrap();
            let name = name_pair.as_str().to_owned();
            let type_args = if let Some(tl) = i.next() {
                tl.into_inner().map(build_type).collect()
            } else {
                Vec::new()
            };
            Type::UserDefined { name, type_args }
        }
        r => panic!("unexpected type rule: {r:?} — '{}'", pair.as_str()),
    }
}

fn build_typed_field_list(pair: Pair<Rule>) -> Vec<TypedField> {
    pair.into_inner().map(|p| {
        let mut i = p.into_inner();
        let name = i.next().unwrap().as_str().to_owned();
        let ty   = build_type(i.next().unwrap());
        TypedField { name, ty }
    }).collect()
}

fn build_typed_param_list(pair: Pair<Rule>) -> Vec<TypedParam> {
    pair.into_inner().map(|p| {
        let mut i = p.into_inner();
        let name = i.next().unwrap().as_str().to_owned();
        let ty   = build_type(i.next().unwrap());
        TypedParam { name, ty }
    }).collect()
}

fn build_generic_params(pair: Pair<Rule>) -> Vec<GenericParam> {
    pair.into_inner().map(|p| {
        let mut i = p.into_inner();
        let name = i.next().unwrap().as_str().to_owned();
        let constraints = i.map(build_generic_constraint).collect();
        GenericParam { name, constraints }
    }).collect()
}

fn build_generic_constraint(pair: Pair<Rule>) -> GenericConstraint {
    let text = pair.as_str();
    let ty   = build_type(inner_first(pair));
    if text.starts_with(':') { GenericConstraint::IsType(ty) }
    else if text.starts_with('=') { GenericConstraint::DefaultsTo(ty) }
    else { GenericConstraint::Extends(ty) }
}

fn build_where_clause(pair: Pair<Rule>) -> Vec<Constraint> {
    pair.into_inner().map(build_constraint).collect()
}

fn build_constraint(pair: Pair<Rule>) -> Constraint {
    let text = pair.as_str();
    let mut i = pair.into_inner();
    if let Some(first) = i.next() {
        if first.as_rule() == Rule::ident {
            let name = first.as_str().to_owned();
            if let Some(second) = i.next() {
                let ty = build_type(second);
                return if text.contains(':') { Constraint::IsType { name, ty } }
                else if text.contains("extends") { Constraint::Extends { name, ty } }
                else { Constraint::Equals { name, ty } };
            }
        }
        return Constraint::Expr(build_expr(first));
    }
    Constraint::Expr(Expr::new(ExprKind::Lit(Lit::Null), 0..0))
}

// ── Expressions ───────────────────────────────────────────────────────────────

fn build_expr(pair: Pair<Rule>) -> Expr {
    let span = pair_span(&pair);
    match pair.as_rule() {
        Rule::expr => build_expr(inner_first(pair)),

        // Combinators
        Rule::combinator_expr  => build_expr(inner_first(pair)),
        Rule::map_expr         => { let [f,c] = two_exprs(pair); Expr::new(ExprKind::Map { func: Box::new(f), collection: Box::new(c) }, span) }
        Rule::filter_expr      => { let [c,p] = two_exprs(pair); Expr::new(ExprKind::Filter { collection: Box::new(c), pred: Box::new(p) }, span) }
        Rule::reduce_expr      => { let (c,f,i) = three_exprs_opt(pair); Expr::new(ExprKind::Reduce { collection: Box::new(c), func: Box::new(f), init: i.map(Box::new) }, span) }
        Rule::foreach_expr     => { let [c,f] = two_exprs(pair); Expr::new(ExprKind::Foreach { collection: Box::new(c), func: Box::new(f) }, span) }
        Rule::group_by_expr    => { let [c,k] = two_exprs(pair); Expr::new(ExprKind::GroupBy { collection: Box::new(c), key_fn: Box::new(k) }, span) }
        Rule::flatmap_expr     => { let [c,f] = two_exprs(pair); Expr::new(ExprKind::FlatMap { collection: Box::new(c), func: Box::new(f) }, span) }
        Rule::zip_expr         => { let (l,r,cb) = three_exprs_opt(pair); Expr::new(ExprKind::Zip { left: Box::new(l), right: Box::new(r), combiner: cb.map(Box::new) }, span) }
        Rule::partition_expr   => { let [c,p] = two_exprs(pair); Expr::new(ExprKind::Partition { collection: Box::new(c), pred: Box::new(p) }, span) }
        Rule::take_expr        => { let [c,n] = two_exprs(pair); Expr::new(ExprKind::Take { collection: Box::new(c), n: Box::new(n) }, span) }
        Rule::drop_expr        => { let [c,n] = two_exprs(pair); Expr::new(ExprKind::Drop { collection: Box::new(c), n: Box::new(n) }, span) }
        Rule::take_while_expr  => { let [c,p] = two_exprs(pair); Expr::new(ExprKind::TakeWhile { collection: Box::new(c), pred: Box::new(p) }, span) }
        Rule::drop_while_expr  => { let [c,p] = two_exprs(pair); Expr::new(ExprKind::DropWhile { collection: Box::new(c), pred: Box::new(p) }, span) }
        Rule::sort_by_expr     => { let [c,k] = two_exprs(pair); Expr::new(ExprKind::SortBy { collection: Box::new(c), key_fn: Box::new(k) }, span) }
        Rule::distinct_expr    => { let (c,f) = two_exprs_second_opt(pair); Expr::new(ExprKind::Distinct { collection: Box::new(c), eq_fn: f.map(Box::new) }, span) }
        Rule::count_expr       => { let (c,f) = two_exprs_second_opt(pair); Expr::new(ExprKind::Count { collection: Box::new(c), pred: f.map(Box::new) }, span) }
        Rule::find_expr        => { let [c,p] = two_exprs(pair); Expr::new(ExprKind::Find { collection: Box::new(c), pred: Box::new(p) }, span) }
        Rule::any_expr         => { let [c,p] = two_exprs(pair); Expr::new(ExprKind::Any { collection: Box::new(c), pred: Box::new(p) }, span) }
        Rule::all_expr         => { let [c,p] = two_exprs(pair); Expr::new(ExprKind::All { collection: Box::new(c), pred: Box::new(p) }, span) }
        Rule::window_expr      => { let (c,s,st) = three_exprs_opt(pair); Expr::new(ExprKind::Window { collection: Box::new(c), size: Box::new(s), step: st.map(Box::new) }, span) }
        Rule::chunk_expr       => { let [c,s] = two_exprs(pair); Expr::new(ExprKind::Chunk { collection: Box::new(c), size: Box::new(s) }, span) }
        Rule::scan_expr        => { let (c,f,i) = three_exprs_opt(pair); Expr::new(ExprKind::Scan { collection: Box::new(c), func: Box::new(f), init: i.map(Box::new) }, span) }
        Rule::collect_expr     => {
            let mut es = pair.into_inner().map(build_expr).collect::<Vec<_>>();
            let init = es.remove(2); let func = es.remove(1); let coll = es.remove(0);
            Expr::new(ExprKind::Collect { collection: Box::new(coll), func: Box::new(func), init: Box::new(init) }, span)
        }
        Rule::join_expr        => {
            let mut es = pair.into_inner().map(build_expr).collect::<Vec<_>>();
            let select = if es.len() > 3 { Some(Box::new(es.remove(3))) } else { None };
            let on = es.remove(2); let right = es.remove(1); let left = es.remove(0);
            Expr::new(ExprKind::Join { left: Box::new(left), right: Box::new(right), on: Box::new(on), select }, span)
        }

        // Lambda
        Rule::lambda_expr => build_lambda(pair),

        // Pipeline chain
        Rule::pipeline_expr => {
            let mut inner = pair.into_inner();
            let mut lhs = build_expr(inner.next().unwrap());
            while let Some(op_pair) = inner.next() {
                let rhs = build_expr(inner.next().unwrap());
                let op  = match op_pair.as_str() {
                    "|||" => BinOp::Parallel,
                    _     => BinOp::Pipeline,
                };
                let s = lhs.span.start..rhs.span.end;
                lhs = Expr::new(ExprKind::Binary { op, lhs: Box::new(lhs), rhs: Box::new(rhs) }, s);
            }
            lhs
        }

        // Binary ops (left-associative chains)
        Rule::null_coalesce_expr => build_left_chain(pair, |_| BinOp::NullCoalesce),
        Rule::logical_or_expr    => build_left_chain(pair, |_| BinOp::Or),
        Rule::logical_and_expr   => build_left_chain(pair, |_| BinOp::And),
        Rule::equality_expr      => build_left_chain(pair, |op| match op { "==" => BinOp::Eq, _ => BinOp::Neq }),
        Rule::relational_expr    => build_relational(pair),
        Rule::additive_expr      => build_left_chain(pair, |op| match op { "+" => BinOp::Add, _ => BinOp::Sub }),
        Rule::multiplicative_expr => build_left_chain(pair, |op| match op { "*" => BinOp::Mul, "/" => BinOp::Div, _ => BinOp::Mod }),

        Rule::range_expr => {
            let mut inner = pair.into_inner();
            let lhs = build_expr(inner.next().unwrap());
            if let Some(op_p) = inner.next() {
                let rhs = build_expr(inner.next().unwrap());
                let inclusive = op_p.as_str() == "..=";
                let s = lhs.span.start..rhs.span.end;
                Expr::new(ExprKind::Range { lo: Box::new(lhs), hi: Box::new(rhs), inclusive }, s)
            } else {
                lhs
            }
        }

        Rule::ternary_expr => {
            let mut inner = pair.into_inner();
            let cond = build_expr(inner.next().unwrap());
            if let Some(then_p) = inner.next() {
                let then  = build_expr(then_p);
                let else_ = build_expr(inner.next().unwrap());
                let s = cond.span.start..else_.span.end;
                Expr::new(ExprKind::Ternary { cond: Box::new(cond), then: Box::new(then), else_: Box::new(else_) }, s)
            } else {
                cond
            }
        }

        Rule::unary_expr => {
            let mut inner = pair.into_inner();
            let first = inner.next().unwrap();
            match first.as_str() {
                "!"           => { let e = build_expr(inner.next().unwrap()); Expr::new(ExprKind::Unary { op: UnOp::Not, operand: Box::new(e) }, span) }
                "-"           => { let e = build_expr(inner.next().unwrap()); Expr::new(ExprKind::Unary { op: UnOp::Neg, operand: Box::new(e) }, span) }
                "always"      => { let e = build_expr(inner.next().unwrap()); Expr::new(ExprKind::Always(Box::new(e)), span) }
                "eventually"  => { let e = build_expr(inner.next().unwrap()); Expr::new(ExprKind::Eventually(Box::new(e)), span) }
                _             => build_expr(first),
            }
        }

        Rule::postfix_expr => build_postfix(pair),

        // Primary
        Rule::primary_expr     => build_expr(inner_first(pair)),
        Rule::literal          => Expr::new(ExprKind::Lit(build_literal(pair)), span),
        Rule::when_expr        => {
            let mut i = pair.into_inner();
            let cond = build_expr(i.next().unwrap());
            let body = build_expr(i.next().unwrap());
            Expr::new(ExprKind::When { cond: Box::new(cond), body: Box::new(body) }, span)
        }
        Rule::match_expr       => build_match(pair),
        Rule::list_expr        => {
            let items = pair.into_inner().map(build_expr).collect();
            Expr::new(ExprKind::List(items), span)
        }
        Rule::object_or_block  => build_object_or_block(pair),
        Rule::block_expr | Rule::block_expr => {
            let items = build_block_items(pair);
            Expr::new(ExprKind::Block(items), span)
        }
        Rule::combinator_ident | Rule::type_name_ident => {
            Expr::new(ExprKind::Ident(pair.as_str().to_owned()), span)
        }
        Rule::qualified_name => {
            let parts: Vec<String> = pair.into_inner().map(|p| p.as_str().to_owned()).collect();
            if parts.len() == 1 {
                Expr::new(ExprKind::Ident(parts.into_iter().next().unwrap()), span)
            } else {
                Expr::new(ExprKind::Qualified(parts), span)
            }
        }
        r => panic!("unexpected expr rule: {r:?} — '{}'", pair.as_str()),
    }
}

// ── Postfix ───────────────────────────────────────────────────────────────────

fn build_postfix(pair: Pair<Rule>) -> Expr {
    let span = pair_span(&pair);
    let mut inner = pair.into_inner();
    let mut base = build_expr(inner.next().unwrap());
    for suffix in inner {
        let s = base.span.start..pair_span(&suffix).end;
        match suffix.as_rule() {
            Rule::postfix_suffix => {
                let child = inner_first(suffix);
                match child.as_rule() {
                    Rule::call_args => {
                        let args = build_call_args(child);
                        base = Expr::new(ExprKind::Call { callee: Box::new(base), args }, s);
                    }
                    Rule::expr => {
                        // index: [ expr ]
                        let idx = build_expr(child);
                        base = Expr::new(ExprKind::Index { object: Box::new(base), index: Box::new(idx) }, s);
                    }
                    Rule::ident => {
                        let member = child.as_str().to_owned();
                        // check for trailing call_args
                        base = Expr::new(ExprKind::Member { object: Box::new(base), member }, s);
                    }
                    _ if child.as_str() == "?" => {
                        base = Expr::new(ExprKind::Try(Box::new(base)), span.clone());
                    }
                    _ => {}
                }
            }
            _ => {}
        }
    }
    base
}

fn build_call_args(pair: Pair<Rule>) -> Vec<Argument> {
    match pair.as_rule() {
        Rule::call_args => {
            if let Some(al) = pair.into_inner().next() {
                build_arg_list(al)
            } else {
                Vec::new()
            }
        }
        Rule::arg_list => build_arg_list(pair),
        _ => Vec::new(),
    }
}

fn build_arg_list(pair: Pair<Rule>) -> Vec<Argument> {
    pair.into_inner().map(|p| {
        let text = p.as_str();
        let mut inner = p.into_inner().peekable();
        // Named arg: ident = expr  (but not =>)
        if let Some(first) = inner.peek() {
            if first.as_rule() == Rule::ident {
                // peek further — if next after ident is not => then it's named
                let ident_str = first.as_str().to_owned();
                if text.contains('=') && !text.contains("=>") && text.trim_start().starts_with(&ident_str) {
                    inner.next(); // consume ident
                    let value = build_expr(inner.next().unwrap());
                    return Argument { label: Some(ident_str), value };
                }
            }
        }
        Argument { label: None, value: build_expr(inner.next().unwrap()) }
    }).collect()
}

// ── Lambda ────────────────────────────────────────────────────────────────────

fn build_lambda(pair: Pair<Rule>) -> Expr {
    let span = pair_span(&pair);
    let mut inner = pair.into_inner();
    let params_pair = inner.next().unwrap();
    let params = build_lambda_params(params_pair);
    let body_pair = inner.next().unwrap();
    let body = if body_pair.as_rule() == Rule::block_expr || body_pair.as_rule() == Rule::block_expr {
        let items = build_block_items(body_pair.clone());
        Expr::new(ExprKind::Block(items), pair_span(&body_pair))
    } else {
        build_expr(body_pair)
    };
    Expr::new(ExprKind::Lambda { params, body: Box::new(body) }, span)
}

fn build_lambda_params(pair: Pair<Rule>) -> Vec<LambdaParam> {
    match pair.as_rule() {
        Rule::lambda_params => build_lambda_params(inner_first(pair)),
        Rule::lambda_param_list => pair.into_inner().map(|p| {
            let mut i = p.into_inner();
            let name = i.next().unwrap().as_str().to_owned();
            let ty   = i.next().map(build_type);
            LambdaParam { name, ty }
        }).collect(),
        Rule::ident => vec![LambdaParam { name: pair.as_str().to_owned(), ty: None }],
        Rule::simple_destruct_fields => pair.into_inner().map(|p| {
            let mut i = p.into_inner();
            let first = i.next().unwrap().as_str().to_owned();
            let alias = i.next().map(|a| a.as_str().to_owned());
            LambdaParam { name: alias.unwrap_or(first), ty: None }
        }).collect(),
        Rule::simple_destruct_list => pair.into_inner().map(|p| {
            LambdaParam { name: p.as_str().to_owned(), ty: None }
        }).collect(),
        _ => vec![],
    }
}

// ── Block ─────────────────────────────────────────────────────────────────────

fn build_block_items(pair: Pair<Rule>) -> Vec<Transformation> {
    pair.into_inner().filter_map(|p| match p.as_rule() {
        Rule::block_item => Some(build_block_item(p)),
        _ => None,
    }).collect()
}

fn build_block_item(pair: Pair<Rule>) -> Transformation {
    // block_item = { let_item | emit_item | signal_item | expr ~ ";"? }
    let inner = inner_first(pair);
    match inner.as_rule() {
        Rule::let_item => {
            let mut i = inner.into_inner();
            let name = i.next().unwrap().as_str().to_owned();
            let (ty, value) = extract_ty_and_expr(i);
            Transformation::Let { name, ty, value }
        }
        Rule::emit_item | Rule::signal_item => {
            Transformation::Expr(build_expr(inner_first(inner)))
        }
        _ => Transformation::Expr(build_expr(inner)),
    }
}

// ── Object or block ───────────────────────────────────────────────────────────

fn build_object_or_block(pair: Pair<Rule>) -> Expr {
    let span = pair_span(&pair);
    // If first inner rule is object_field, it's an object; otherwise block.
    let inner_peek = pair.clone().into_inner().next();
    match inner_peek {
        Some(p) if p.as_rule() == Rule::object_field => {
            let fields = pair.into_inner().map(|f| {
                let mut i = f.into_inner();
                let key_p = i.next().unwrap();
                let key = key_p.as_str().trim_matches('"').to_owned();
                let val = build_expr(i.next().unwrap());
                ObjectField { key, value: val }
            }).collect();
            Expr::new(ExprKind::Object(fields), span)
        }
        _ => {
            let items = build_block_items(pair);
            Expr::new(ExprKind::Block(items), span)
        }
    }
}

// ── Match ─────────────────────────────────────────────────────────────────────

fn build_match(pair: Pair<Rule>) -> Expr {
    let span = pair_span(&pair);
    let mut inner = pair.into_inner();
    let subject = build_expr(inner.next().unwrap());
    let arms = inner.map(|arm| {
        let mut i = arm.into_inner();
        let pat  = build_pattern(i.next().unwrap());
        let body = build_expr(i.next().unwrap());
        MatchArm { pattern: pat, body }
    }).collect();
    Expr::new(ExprKind::Match { subject: Box::new(subject), arms }, span)
}

fn build_pattern(pair: Pair<Rule>) -> Pattern {
    match pair.as_rule() {
        // pattern = { primary_pattern ~ (or_op ~ primary_pattern)* }
        // or_op is silent — inner yields only primary_pattern pairs
        Rule::pattern => {
            let parts: Vec<Pattern> = pair.into_inner().map(build_pattern).collect();
            if parts.len() == 1 { parts.into_iter().next().unwrap() } else { Pattern::Or(parts) }
        }
        Rule::primary_pattern  => build_pattern(inner_first(pair)),
        Rule::wildcard_pattern => Pattern::Wildcard,
        Rule::lit_pattern      => Pattern::Literal(build_literal(inner_first(pair))),
        Rule::ident_pattern    => Pattern::Ident(pair.as_str().to_owned()),
        Rule::range_pattern    => {
            let mut i = pair.into_inner();
            let lo = build_literal(i.next().unwrap());
            let op = i.next().unwrap().as_str();
            let hi = build_literal(i.next().unwrap());
            Pattern::Range { lo: Box::new(lo), hi: Box::new(hi), inclusive: op == "..=" }
        }
        Rule::type_pattern => {
            let mut i = pair.into_inner();
            let inner_pat = build_pattern(i.next().unwrap());
            let ty = build_type(i.next().unwrap());
            Pattern::Type { inner: Box::new(inner_pat), ty: Box::new(ty) }
        }
        Rule::guard_pattern => {
            let mut i = pair.into_inner();
            let inner_pat = build_pattern(i.next().unwrap());
            let cond = build_expr(i.next().unwrap());
            Pattern::Guard { inner: Box::new(inner_pat), cond: Box::new(cond) }
        }
        Rule::obj_destruct => {
            let fields = pair.into_inner().map(build_pattern_field).collect();
            Pattern::ObjectDestruct(fields)
        }
        Rule::list_destruct => {
            let items = pair.into_inner().map(build_pattern).collect();
            Pattern::ListDestruct(items)
        }
        Rule::tuple_destruct => {
            let items = pair.into_inner().map(build_pattern).collect();
            Pattern::Tuple(items)
        }
        Rule::named_destruct => {
            let mut i = pair.into_inner();
            let name = i.next().unwrap().as_str().to_owned();
            let fields = i.map(build_pattern_field).collect();
            Pattern::Named { constructor: name, fields }
        }
        _ => Pattern::Wildcard,
    }
}

fn build_pattern_field(pair: Pair<Rule>) -> PatternField {
    let mut i = pair.into_inner();
    let name = i.next().unwrap().as_str().to_owned();
    let pattern = i.next().map(|p| Box::new(build_pattern(p)));
    PatternField { name, pattern }
}

// ── Left-associative binary chain ─────────────────────────────────────────────

fn build_left_chain<F: Fn(&str) -> BinOp>(pair: Pair<Rule>, op_fn: F) -> Expr {
    let mut inner = pair.into_inner();
    let mut lhs = build_expr(inner.next().unwrap());
    while let Some(op_p) = inner.next() {
        let rhs = build_expr(inner.next().unwrap());
        let op = op_fn(op_p.as_str().trim());
        let s = lhs.span.start..rhs.span.end;
        lhs = Expr::new(ExprKind::Binary { op, lhs: Box::new(lhs), rhs: Box::new(rhs) }, s);
    }
    lhs
}

fn build_relational(pair: Pair<Rule>) -> Expr {
    let span = pair_span(&pair);
    let mut inner = pair.into_inner();
    let mut lhs = build_expr(inner.next().unwrap());
    while let Some(op_p) = inner.next() {
        let rhs = build_expr(inner.next().unwrap());
        let op = match op_p.as_str().trim() {
            "<=" => BinOp::Le, ">=" => BinOp::Ge, "<" => BinOp::Lt, ">" => BinOp::Gt,
            "within" | "during" | "until" => BinOp::Range,
            "in" => BinOp::In,
            _ => BinOp::Lt,
        };
        let s = lhs.span.start..rhs.span.end;
        lhs = Expr::new(ExprKind::Binary { op, lhs: Box::new(lhs), rhs: Box::new(rhs) }, s);
    }
    lhs
}

// ── Literals ──────────────────────────────────────────────────────────────────

fn build_literal(pair: Pair<Rule>) -> Lit {
    let pair = if pair.as_rule() == Rule::literal { inner_first(pair) } else { pair };
    match pair.as_rule() {
        Rule::bool_lit   => Lit::Bool(pair.as_str() == "true"),
        Rule::null_lit   => Lit::Null,
        Rule::int_lit    => {
            let s = pair.as_str().trim_end_matches(['l','L']).replace('_', "");
            Lit::Int(s.parse().unwrap_or(0))
        }
        Rule::float_lit  => {
            let s = pair.as_str().trim_end_matches(['f','F','d','D']).replace('_', "");
            Lit::Float(s.parse().unwrap_or(0.0))
        }
        Rule::string_lit => {
            let s = pair.as_str();
            Lit::Str(s[1..s.len()-1].to_owned())
        }
        Rule::raw_string => {
            let s = pair.as_str();
            Lit::Str(s[2..s.len()-1].to_owned())
        }
        Rule::multiline_string => {
            let s = pair.as_str();
            Lit::Str(s[3..s.len()-3].to_owned())
        }
        _ => Lit::Null,
    }
}

// ── Helpers ───────────────────────────────────────────────────────────────────

fn inner_first(pair: Pair<Rule>) -> Pair<Rule> {
    pair.into_inner().next().expect("expected inner pair")
}

/// Extract an optional type annotation followed by a required expression from a Pairs iterator.
fn extract_ty_and_expr(mut inner: Pairs<Rule>) -> (Option<Type>, Expr) {
    let first = inner.next().unwrap();
    if first.as_rule() == Rule::ty {
        let ty    = build_type(first);
        let value = build_expr(inner.next().unwrap());
        (Some(ty), value)
    } else {
        (None, build_expr(first))
    }
}

fn two_exprs(pair: Pair<Rule>) -> [Expr; 2] {
    let mut v: Vec<Expr> = pair.into_inner().map(build_expr).collect();
    let b = v.remove(1);
    let a = v.remove(0);
    [a, b]
}

fn three_exprs_opt(pair: Pair<Rule>) -> (Expr, Expr, Option<Expr>) {
    let mut v: Vec<Expr> = pair.into_inner().map(build_expr).collect();
    let c = if v.len() > 2 { Some(v.remove(2)) } else { None };
    let b = v.remove(1);
    let a = v.remove(0);
    (a, b, c)
}

fn two_exprs_second_opt(pair: Pair<Rule>) -> (Expr, Option<Expr>) {
    let mut v: Vec<Expr> = pair.into_inner().map(build_expr).collect();
    let b = if v.len() > 1 { Some(v.remove(1)) } else { None };
    let a = v.remove(0);
    (a, b)
}
