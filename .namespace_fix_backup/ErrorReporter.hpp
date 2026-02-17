#pragma once

#include "olang/ast/Type.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <optional>

namespace olang::semantic {
  
// ───────────────────────────────────────────────────────────────────────────
// Type Checker Error Reporting
// ───────────────────────────────────────────────────────────────────────────
enum class ErrorSeverity {
    Warning,
    Error,
    Fatal
};

struct TypeError {
    ErrorSeverity severity;
    std::string message;
    size_t line;
    size_t column;
    
    TypeError(ErrorSeverity sev, std::string msg, size_t l = 0, size_t c = 0)
        : severity(sev), message(std::move(msg)), line(l), column(c) {}
};

class ErrorReporter {
public:
    void reportError(TypeError error);
    void reportWarning(const std::string& message, size_t line = 0, size_t col = 0);
    
    bool hasErrors() const { return hasErrors_; }
    const std::vector<TypeError>& getErrors() const { return errors_; }
    
    void clear();
    
private:
    std::vector<TypeError> errors_;
    bool hasErrors_ = false;
};
} // namespace olang::semantic