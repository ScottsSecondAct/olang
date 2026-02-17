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
// Symbol Table Entry
// ───────────────────────────────────────────────────────────────────────────
struct Symbol {
    std::string name;
    std::unique_ptr<ast::Type> type;
    bool isConst;
    bool isFunction;
    
    Symbol(std::string n, std::unique_ptr<ast::Type> t, 
           bool isConst = false, bool isFunc = false)
        : name(std::move(n)), type(std::move(t)), 
          isConst(isConst), isFunction(isFunc) {}
};

// ───────────────────────────────────────────────────────────────────────────
// Symbol Table (Scoped)
// ───────────────────────────────────────────────────────────────────────────
class SymbolTable {
public:
    SymbolTable() = default;
    explicit SymbolTable(SymbolTable* parent) : parent_(parent) {}
    
    // Symbol registration
    bool declare(const std::string& name, std::unique_ptr<ast::Type> type,
                 bool isConst = false, bool isFunction = false);
    
    // Symbol lookup (searches up scope chain)
    Symbol* lookup(const std::string& name);
    const Symbol* lookup(const std::string& name) const;
    
    // Check if symbol exists in current scope only
    bool existsInCurrentScope(const std::string& name) const;
    
    // Scope management
    void enterScope();
    void exitScope();
    SymbolTable* getParent() { return parent_; }
    
private:
    std::unordered_map<std::string, std::unique_ptr<Symbol>> symbols_;
    SymbolTable* parent_ = nullptr;
};

// ───────────────────────────────────────────────────────────────────────────
// Type Environment (Global Type Registry)
// ───────────────────────────────────────────────────────────────────────────
class TypeEnvironment {
public:
    TypeEnvironment();
    
    // Register user-defined types
    bool registerType(const std::string& name, std::unique_ptr<ast::Type> type);
    
    // Lookup type by name
    const ast::Type* lookupType(const std::string& name) const;
    
    // Check if type exists
    bool typeExists(const std::string& name) const;
    
    // Built-in type factories
    std::unique_ptr<ast::Type> getIntType() const;
    std::unique_ptr<ast::Type> getLongType() const;
    std::unique_ptr<ast::Type> getFloatType() const;
    std::unique_ptr<ast::Type> getDoubleType() const;
    std::unique_ptr<ast::Type> getBoolType() const;
    std::unique_ptr<ast::Type> getStringType() const;
    std::unique_ptr<ast::Type> getAnyType() const;
    std::unique_ptr<ast::Type> getNeverType() const;
    std::unique_ptr<ast::Type> getNullType() const;
    
private:
    std::unordered_map<std::string, std::unique_ptr<ast::Type>> types_;
    
    void initializeBuiltinTypes();
};

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