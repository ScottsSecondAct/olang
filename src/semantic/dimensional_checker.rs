use crate::parser::ast::Type;
use super::error_reporter::ErrorReporter;

pub struct DimensionalChecker<'a> {
    reporter: &'a mut ErrorReporter,
}

impl<'a> DimensionalChecker<'a> {
    pub fn new(reporter: &'a mut ErrorReporter) -> Self { Self { reporter } }

    /// Check whether a binary operation is dimensionally valid.
    pub fn check_binary_op(&mut self, lhs: &Type, rhs: &Type, op: &str) -> bool {
        if op == "+" || op == "-" {
            self.check_same_dimensions(lhs, rhs)
        } else {
            // Multiplication and division combine dimensions — always permitted.
            true
        }
    }

    /// Addition/subtraction requires identical types (simplified).
    pub fn check_same_dimensions(&mut self, t1: &Type, t2: &Type) -> bool {
        if t1 == t2 { return true; }
        self.reporter.error(format!(
            "dimensional mismatch: '{}' and '{}' have incompatible dimensions",
            t1.to_display(), t2.to_display()
        ));
        false
    }

    /// Compute the result type for a binary arithmetic operation (simplified).
    pub fn compute_result_type(&self, lhs: &Type, _rhs: &Type, _op: &str) -> Type {
        lhs.clone()
    }
}
