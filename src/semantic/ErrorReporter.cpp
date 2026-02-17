// ═══════════════════════════════════════════════════════════════════════════
// OLang Error Reporter Implementation
// Milestone 1.2: Type System Foundation
// ═══════════════════════════════════════════════════════════════════════════

#include "olang/semantic/ErrorReporter.hpp"
#include <iostream>

namespace olang::semantic {

void ErrorReporter::reportError(TypeError error) {
    if (error.severity == ErrorSeverity::Error || 
        error.severity == ErrorSeverity::Fatal) {
        hasErrors_ = true;
    }
    errors_.push_back(std::move(error));
    
    // Print to stderr for immediate feedback
    std::cerr << "[";
    switch (error.severity) {
        case ErrorSeverity::Warning: std::cerr << "WARNING"; break;
        case ErrorSeverity::Error: std::cerr << "ERROR"; break;
        case ErrorSeverity::Fatal: std::cerr << "FATAL"; break;
    }
    std::cerr << "] ";
    if (error.line > 0) {
        std::cerr << "Line " << error.line;
        if (error.column > 0) {
            std::cerr << ":" << error.column;
        }
        std::cerr << ": ";
    }
    std::cerr << error.message << std::endl;
}

void ErrorReporter::reportWarning(const std::string& message, 
                                  size_t line, size_t col) {
    reportError(TypeError(ErrorSeverity::Warning, message, line, col));
}

void ErrorReporter::clear() {
    errors_.clear();
    hasErrors_ = false;
}

} // namespace olang::semantic