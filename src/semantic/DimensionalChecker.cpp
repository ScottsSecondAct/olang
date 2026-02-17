#pragma once

#include "olang/frontend/ASTType.hpp"
#include "olang/semantic/DimensionalChecker.hpp"
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
    bool checkBinaryOp(const frontend::Type& lhs, const frontend::Type& rhs, 
                      const std::string& op);
    
    // Check if units match for comparison/addition/subtraction
    bool checkSameDimensions(const frontend::Type& t1, const frontend::Type& t2);
    
    // Compute result type for multiplication/division
    std::unique_ptr<frontend::Type> computeResultType(
        const frontend::Type& lhs, const frontend::Type& rhs, const std::string& op);
    
private:
    ErrorReporter& errorReporter_;
    
    void reportDimensionalError(const std::string& message, 
                               size_t line = 0, size_t col = 0);
};

} // namespace olang::semantic