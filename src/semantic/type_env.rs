use crate::parser::ast::{Type, PrimitiveKind};
use std::collections::HashMap;

/// Global type registry: maps type names to their definitions.
#[derive(Debug)]
pub struct TypeEnvironment {
    types: HashMap<String, Type>,
}

impl Default for TypeEnvironment {
    fn default() -> Self { Self::new() }
}

impl TypeEnvironment {
    pub fn new() -> Self {
        let mut env = Self { types: HashMap::new() };
        env.init_builtins();
        env
    }

    fn init_builtins(&mut self) {
        let builtins = [
            ("int",       PrimitiveKind::Int),
            ("long",      PrimitiveKind::Long),
            ("float",     PrimitiveKind::Float),
            ("double",    PrimitiveKind::Double),
            ("bool",      PrimitiveKind::Bool),
            ("char",      PrimitiveKind::Char),
            ("string",    PrimitiveKind::String),
            ("any_type",  PrimitiveKind::Any),
            ("never_type",PrimitiveKind::Never),
            ("null",      PrimitiveKind::Null),
        ];
        for (name, kind) in builtins {
            self.types.insert(name.to_owned(), Type::Primitive(kind));
        }
    }

    pub fn register(&mut self, name: impl Into<String>, ty: Type) -> bool {
        let name = name.into();
        if self.types.contains_key(&name) { return false; }
        self.types.insert(name, ty);
        true
    }

    pub fn lookup(&self, name: &str) -> Option<&Type> {
        self.types.get(name)
    }

    pub fn exists(&self, name: &str) -> bool {
        self.types.contains_key(name)
    }

    // ── Built-in type factories ────────────────────────────────────────────

    pub fn int_type()    -> Type { Type::Primitive(PrimitiveKind::Int) }
    pub fn long_type()   -> Type { Type::Primitive(PrimitiveKind::Long) }
    pub fn float_type()  -> Type { Type::Primitive(PrimitiveKind::Float) }
    pub fn double_type() -> Type { Type::Primitive(PrimitiveKind::Double) }
    pub fn bool_type()   -> Type { Type::Primitive(PrimitiveKind::Bool) }
    pub fn string_type() -> Type { Type::Primitive(PrimitiveKind::String) }
    pub fn any_type()    -> Type { Type::Primitive(PrimitiveKind::Any) }
    pub fn never_type()  -> Type { Type::Primitive(PrimitiveKind::Never) }
    pub fn null_type()   -> Type { Type::Primitive(PrimitiveKind::Null) }
}
