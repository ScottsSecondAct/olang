// ═══════════════════════════════════════════════════════════════════════════
// OLang Type Checker & Semantic Analyzer
// Milestone 1.2: Type System Foundation
// ═══════════════════════════════════════════════════════════════════════════

#pragma once

#include "olang/ast/Type.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <optional>

namespace olang::semantic {

// ───────────────────────────────────────────────────────────────────────────
// Type Checker Core
// ───────────────────────────────────────────────────────────────────────────
class TypeChecker : public ast::TypeVisitor {
public:
    TypeChecker(TypeEnvironment& env, ErrorReporter& reporter)
        : typeEnv_(env), errorReporter_(reporter), symbolTable_(nullptr) {}
    
    // Main type-checking entry point
    std::unique_ptr<ast::Type> checkExpression(/* Expression AST node */);
    
    // Type compatibility checking
    bool isAssignable(const ast::Type& target, const ast::Type& source);
    bool isSubtype(const ast::Type& sub, const ast::Type& super);
    
    // Type unification (for type inference)
    std::optional<std::unique_ptr<ast::Type>> unify(
        const ast::Type& t1, const ast::Type& t2);
    
    // Visitor implementations
    void visit(const ast::PrimitiveType& type) override;
    void visit(const ast::UserDefinedType& type) override;
    void visit(const ast::PipelineType& type) override;
    void visit(const ast::ListType& type) override;
    void visit(const ast::MapType& type) override;
    void visit(const ast::SetType& type) override;
    void visit(const ast::StreamType& type) override;
    void visit(const ast::FutureType& type) override;
    void visit(const ast::ResultType& type) override;
    void visit(const ast::OptionType& type) override;
    void visit(const ast::ProvenanceType& type) override;
    void visit(const ast::FunctionType& type) override;
    void visit(const ast::UnionType& type) override;
    void visit(const ast::OptionalType& type) override;
    
    // Scope management
    void enterScope();
    void exitScope();
    
private:
    TypeEnvironment& typeEnv_;
    ErrorReporter& errorReporter_;
    SymbolTable symbolTable_;
    
    // Helper methods
    void reportTypeMismatch(const ast::Type& expected, 
                           const ast::Type& actual,
                           size_t line = 0, size_t col = 0);
    
    bool checkDimensionalConsistency(const ast::Type& t1, const ast::Type& t2);
};

// ───────────────────────────────────────────────────────────────────────────
// Type Inference Engine
// ───────────────────────────────────────────────────────────────────────────
class TypeInferenceEngine {
public:
    TypeInferenceEngine(TypeEnvironment& env, ErrorReporter& reporter)
        : typeEnv_(env), errorReporter_(reporter) {}
    
    // Infer type from expression context
    std::unique_ptr<ast::Type> inferType(/* Expression AST node */);
    
    // Constraint solving (Hindley-Milner style)
    bool solveConstraints();
    
private:
    TypeEnvironment& typeEnv_;
    ErrorReporter& errorReporter_;
    
    struct TypeConstraint {
        std::unique_ptr<ast::Type> lhs;
        std::unique_ptr<ast::Type> rhs;
        std::string reason;
    };
    
    std::vector<TypeConstraint> constraints_;
};

} // namespace olang::semantic