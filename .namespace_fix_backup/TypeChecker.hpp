// ═══════════════════════════════════════════════════════════════════════════
// OLang Type Checker & Semantic Analyzer
// Milestone 1.2: Type System Foundation
// ═══════════════════════════════════════════════════════════════════════════

#pragma once

#include "olang/frontend/ASTType.hpp"  // ← FIXED: Use correct path
#include "olang/semantic/SymbolTable.hpp"
#include "olang/semantic/TypeEnvironment.hpp"
#include "olang/semantic/ErrorReporter.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <optional>

namespace olang::semantic {

// ───────────────────────────────────────────────────────────────────────────
// Type Checker Core
// ───────────────────────────────────────────────────────────────────────────
class TypeChecker : public frontend::TypeVisitor {  // ← FIXED: Use frontend namespace
public:
    TypeChecker(TypeEnvironment& env, ErrorReporter& reporter)
        : typeEnv_(env), errorReporter_(reporter), symbolTable_(nullptr) {}
    
    // Type compatibility checking
    bool isAssignable(const frontend::Type& target, const frontend::Type& source);
    bool isSubtype(const frontend::Type& sub, const frontend::Type& super);
    
    // Type unification (for type inference)
    std::optional<std::unique_ptr<frontend::Type>> unify(
        const frontend::Type& t1, const frontend::Type& t2);
    
    // Visitor implementations
    void visit(const frontend::PrimitiveType& type) override;
    void visit(const frontend::UserDefinedType& type) override;
    void visit(const frontend::PipelineType& type) override;
    void visit(const frontend::ListType& type) override;
    void visit(const frontend::MapType& type) override;
    void visit(const frontend::SetType& type) override;
    void visit(const frontend::StreamType& type) override;
    void visit(const frontend::FutureType& type) override;
    void visit(const frontend::ResultType& type) override;
    void visit(const frontend::OptionType& type) override;
    void visit(const frontend::ProvenanceType& type) override;
    void visit(const frontend::FunctionType& type) override;
    void visit(const frontend::UnionType& type) override;
    void visit(const frontend::OptionalType& type) override;
    
    // Scope management
    void enterScope();
    void exitScope();
    
private:
    TypeEnvironment& typeEnv_;
    ErrorReporter& errorReporter_;
    SymbolTable symbolTable_;
    
    // Helper methods
    void reportTypeMismatch(const frontend::Type& expected, 
                           const frontend::Type& actual,
                           size_t line = 0, size_t col = 0);
    
    bool checkDimensionalConsistency(const frontend::Type& t1, 
                                    const frontend::Type& t2);
};

// ───────────────────────────────────────────────────────────────────────────
// Type Inference Engine
// ───────────────────────────────────────────────────────────────────────────
class TypeInferenceEngine {
public:
    TypeInferenceEngine(TypeEnvironment& env, ErrorReporter& reporter)
        : typeEnv_(env), errorReporter_(reporter) {}
    
    // Infer type from expression context
    std::unique_ptr<frontend::Type> inferType(/* Expression AST node */);
    
    // Constraint solving (Hindley-Milner style)
    bool solveConstraints();
    
private:
    TypeEnvironment& typeEnv_;
    ErrorReporter& errorReporter_;
    
    struct TypeConstraint {
        std::unique_ptr<frontend::Type> lhs;
        std::unique_ptr<frontend::Type> rhs;
        std::string reason;
    };
    
    std::vector<TypeConstraint> constraints_;
};

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