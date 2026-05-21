pub mod error_reporter;
pub mod symbol_table;
pub mod type_env;
pub mod type_checker;
pub mod dimensional_checker;

pub use error_reporter::{ErrorReporter, TypeError, ErrorSeverity};
pub use symbol_table::{Symbol, SymbolTable};
pub use type_env::TypeEnvironment;
pub use type_checker::TypeChecker;
pub use dimensional_checker::DimensionalChecker;
