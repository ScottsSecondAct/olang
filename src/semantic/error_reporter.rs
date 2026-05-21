use crate::parser::ast::Type;

#[derive(Debug, Clone, PartialEq)]
pub enum ErrorSeverity { Warning, Error, Fatal }

#[derive(Debug, Clone)]
pub struct TypeError {
    pub severity: ErrorSeverity,
    pub message: String,
    pub line: usize,
    pub col: usize,
}

impl TypeError {
    pub fn new(severity: ErrorSeverity, message: impl Into<String>) -> Self {
        Self { severity, message: message.into(), line: 0, col: 0 }
    }

    pub fn at(mut self, line: usize, col: usize) -> Self {
        self.line = line;
        self.col = col;
        self
    }
}

impl std::fmt::Display for TypeError {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        let sev = match self.severity {
            ErrorSeverity::Warning => "WARNING",
            ErrorSeverity::Error   => "ERROR",
            ErrorSeverity::Fatal   => "FATAL",
        };
        if self.line > 0 {
            write!(f, "[{sev}] {}:{}: {}", self.line, self.col, self.message)
        } else {
            write!(f, "[{sev}] {}", self.message)
        }
    }
}

#[derive(Debug, Default)]
pub struct ErrorReporter {
    errors: Vec<TypeError>,
    has_errors: bool,
}

impl ErrorReporter {
    pub fn report(&mut self, error: TypeError) {
        if matches!(error.severity, ErrorSeverity::Error | ErrorSeverity::Fatal) {
            self.has_errors = true;
        }
        eprintln!("{error}");
        self.errors.push(error);
    }

    pub fn warn(&mut self, message: impl Into<String>) {
        self.report(TypeError::new(ErrorSeverity::Warning, message));
    }

    pub fn error(&mut self, message: impl Into<String>) {
        self.report(TypeError::new(ErrorSeverity::Error, message));
    }

    pub fn type_mismatch(&mut self, expected: &Type, actual: &Type, line: usize, col: usize) {
        self.report(TypeError {
            severity: ErrorSeverity::Error,
            message: format!(
                "type mismatch: expected '{}', got '{}'",
                expected.to_display(), actual.to_display()
            ),
            line,
            col,
        });
    }

    pub fn has_errors(&self) -> bool { self.has_errors }
    pub fn errors(&self) -> &[TypeError] { &self.errors }

    pub fn clear(&mut self) {
        self.errors.clear();
        self.has_errors = false;
    }
}
