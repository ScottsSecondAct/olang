use crate::parser::ast::{Type, PrimitiveKind};
use super::{ErrorReporter, SymbolTable, TypeEnvironment};

pub struct TypeChecker<'a> {
    pub env: &'a mut TypeEnvironment,
    pub reporter: &'a mut ErrorReporter,
    pub symbols: SymbolTable,
}

impl<'a> TypeChecker<'a> {
    pub fn new(env: &'a mut TypeEnvironment, reporter: &'a mut ErrorReporter) -> Self {
        Self { env, reporter, symbols: SymbolTable::new() }
    }

    pub fn enter_scope(&mut self) { self.symbols.enter_scope(); }
    pub fn exit_scope(&mut self)  { self.symbols.exit_scope();  }

    // ── Type compatibility ─────────────────────────────────────────────────

    pub fn is_assignable(&mut self, target: &Type, source: &Type) -> bool {
        if target == source { return true; }

        // any_type accepts everything
        if matches!(target, Type::Primitive(PrimitiveKind::Any)) { return true; }

        // never_type is a bottom type — assignable to anything
        if matches!(source, Type::Primitive(PrimitiveKind::Never)) { return true; }

        // T? accepts T
        if let Type::Optional(base) = target {
            return self.is_assignable(base, source);
        }

        // T1 | T2 | ... accepts any Ti
        if let Type::Union(variants) = target {
            return variants.iter().any(|v| self.is_assignable(v, source));
        }

        // Numeric widening
        if let (Type::Primitive(tk), Type::Primitive(sk)) = (target, source) {
            use PrimitiveKind::*;
            return matches!(
                (sk, tk),
                (Int,   Long)   | (Int,   Float)  | (Int,   Double)
                | (Long,  Float)  | (Long,  Double)
                | (Float, Double)
            );
        }

        false
    }

    pub fn is_subtype(&mut self, sub: &Type, sup: &Type) -> bool {
        self.is_assignable(sup, sub)
    }

    // ── Type unification (Hindley-Milner-style) ────────────────────────────

    pub fn unify(&mut self, t1: &Type, t2: &Type) -> Option<Type> {
        if t1 == t2 { return Some(t1.clone()); }

        // any_type wins
        if matches!(t1, Type::Primitive(PrimitiveKind::Any))
            || matches!(t2, Type::Primitive(PrimitiveKind::Any)) {
            return Some(TypeEnvironment::any_type());
        }

        // Merge unions
        if matches!(t1, Type::Union(_)) || matches!(t2, Type::Union(_)) {
            let mut merged: Vec<Type> = Vec::new();
            for t in [t1, t2] {
                if let Type::Union(vs) = t { merged.extend(vs.iter().cloned()); }
                else { merged.push(t.clone()); }
            }
            return Some(Type::Union(merged));
        }

        // Numeric widening
        if let (Type::Primitive(k1), Type::Primitive(k2)) = (t1, t2) {
            use PrimitiveKind::*;
            let widened = match (k1, k2) {
                (Int, Int)     => Some(Int),
                (Int, Long)  | (Long, Int)   => Some(Long),
                (Float, Float) => Some(Float),
                (Int,  Float)  | (Float, Int)
                | (Long, Float) | (Float, Long)  => Some(Float),
                (_, Double) | (Double, _)      => Some(Double),
                _ => None,
            };
            return widened.map(Type::Primitive);
        }

        None
    }

    // ── Type validation (visitor-style dispatch) ───────────────────────────

    pub fn check_type(&mut self, ty: &Type) {
        match ty {
            Type::Primitive(_) => {}
            Type::UserDefined { name, type_args } => {
                if !self.env.exists(name) {
                    self.reporter.error(format!("undefined type '{name}'"));
                }
                for arg in type_args { self.check_type(arg); }
            }
            Type::Pipeline { input, output } => {
                self.check_type(input);
                self.check_type(output);
            }
            Type::List(e) | Type::Set(e) | Type::Stream(e)
            | Type::Future(e) | Type::Option(e)
            | Type::Provenance(e) | Type::Optional(e) => {
                self.check_type(e);
            }
            Type::Map { key, value } => {
                self.check_type(key);
                self.check_type(value);
            }
            Type::Result { ok, err } => {
                self.check_type(ok);
                self.check_type(err);
            }
            Type::Function { params, ret } => {
                for p in params { self.check_type(p); }
                self.check_type(ret);
            }
            Type::Union(ts) => {
                for t in ts { self.check_type(t); }
            }
        }
    }
}

// ── Type inference engine ─────────────────────────────────────────────────────

pub struct TypeInferenceEngine<'a> {
    pub env: &'a mut TypeEnvironment,
    pub reporter: &'a mut ErrorReporter,
    constraints: Vec<TypeConstraint>,
}

struct TypeConstraint {
    lhs: Type,
    rhs: Type,
    reason: String,
}

impl<'a> TypeInferenceEngine<'a> {
    pub fn new(env: &'a mut TypeEnvironment, reporter: &'a mut ErrorReporter) -> Self {
        Self { env, reporter, constraints: Vec::new() }
    }

    pub fn add_constraint(&mut self, lhs: Type, rhs: Type, reason: impl Into<String>) {
        self.constraints.push(TypeConstraint { lhs, rhs, reason: reason.into() });
    }

    pub fn solve_constraints(&mut self) -> bool {
        let mut checker = TypeChecker::new(self.env, self.reporter);
        for c in &self.constraints {
            if checker.unify(&c.lhs, &c.rhs).is_none() {
                self.reporter.error(format!(
                    "cannot unify '{}' with '{}' ({})",
                    c.lhs.to_display(), c.rhs.to_display(), c.reason
                ));
                return false;
            }
        }
        true
    }
}
