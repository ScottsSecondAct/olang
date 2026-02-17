#pragma once

#include "olang/ast/Type.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <optional>

namespace olang::semantic {

  // ───────────────────────────────────────────────────────────────────────────
// Dimensional Analysis Checker (Biological Safety)
// ───────────────────────────────────────────────────────────────────────────
class DimensionalChecker {
public:
    explicit DimensionalChecker(ErrorReporter& reporter) 
        : errorReporter_(reporter) {}
    
    // Check if operation is dimensionally valid
    bool checkBinaryOp(const ast::Type& lhs, const ast::Type& rhs, 
                      const std::string& op);
    
    // Check if units match for comparison/addition/subtraction
    bool checkSameDimensions(const ast::Type& t1, const ast::Type& t2);
    
    // Compute result type for multiplication/division
    std::unique_ptr<ast::Type> computeResultType(
        const ast::Type& lhs, const ast::Type& rhs, const std::string& op);
    
private:
    ErrorReporter& errorReporter_;
    
    void reportDimensionalError(const std::string& message, 
                               size_t line = 0, size_t col = 0);
};

} // namespace olang::semantic