use crate::parser::ast::Type;
use std::collections::HashMap;

#[derive(Debug, Clone)]
pub struct Symbol {
    pub name: String,
    pub ty: Type,
    pub is_const: bool,
    pub is_function: bool,
}

impl Symbol {
    pub fn new(name: impl Into<String>, ty: Type, is_const: bool, is_function: bool) -> Self {
        Self { name: name.into(), ty, is_const, is_function }
    }
}

/// Scoped symbol table using a stack of hash maps.
#[derive(Debug, Default)]
pub struct SymbolTable {
    scopes: Vec<HashMap<String, Symbol>>,
}

impl SymbolTable {
    pub fn new() -> Self {
        Self { scopes: vec![HashMap::new()] }
    }

    /// Push a new lexical scope.
    pub fn enter_scope(&mut self) {
        self.scopes.push(HashMap::new());
    }

    /// Pop the innermost scope.
    pub fn exit_scope(&mut self) {
        if self.scopes.len() > 1 {
            self.scopes.pop();
        }
    }

    /// Declare a symbol in the current scope. Returns `false` if already declared.
    pub fn declare(&mut self, name: impl Into<String>, ty: Type, is_const: bool, is_function: bool) -> bool {
        let name = name.into();
        let scope = self.scopes.last_mut().expect("at least one scope");
        if scope.contains_key(&name) {
            return false;
        }
        scope.insert(name.clone(), Symbol::new(name, ty, is_const, is_function));
        true
    }

    /// Look up a symbol walking out through parent scopes.
    pub fn lookup(&self, name: &str) -> Option<&Symbol> {
        for scope in self.scopes.iter().rev() {
            if let Some(sym) = scope.get(name) {
                return Some(sym);
            }
        }
        None
    }

    /// Check current scope only.
    pub fn exists_in_current_scope(&self, name: &str) -> bool {
        self.scopes.last().map(|s| s.contains_key(name)).unwrap_or(false)
    }
}
