// ═══════════════════════════════════════════════════════════════════════════
// OLang Type Checker Implementation
// Milestone 1.2: Type System Foundation
// ═══════════════════════════════════════════════════════════════════════════

#include "olang/semantic/TypeChecker.hpp"
#include <iostream>
#include <sstream>

namespace olang::semantic {

// ───────────────────────────────────────────────────────────────────────────
// SymbolTable Implementation
// ───────────────────────────────────────────────────────────────────────────
bool SymbolTable::declare(const std::string& name, 
                          std::unique_ptr<ast::Type> type,
                          bool isConst, bool isFunction) {
    if (existsInCurrentScope(name)) {
        return false; // Symbol already exists
    }
    
    symbols_[name] = std::make_unique<Symbol>(
        name, std::move(type), isConst, isFunction);
    return true;
}

Symbol* SymbolTable::lookup(const std::string& name) {
    auto it = symbols_.find(name);
    if (it != symbols_.end()) {
        return it->second.get();
    }
    
    // Search parent scope
    if (parent_) {
        return parent_->lookup(name);
    }
    
    return nullptr;
}

const Symbol* SymbolTable::lookup(const std::string& name) const {
    auto it = symbols_.find(name);
    if (it != symbols_.end()) {
        return it->second.get();
    }
    
    if (parent_) {
        return parent_->lookup(name);
    }
    
    return nullptr;
}

bool SymbolTable::existsInCurrentScope(const std::string& name) const {
    return symbols_.find(name) != symbols_.end();
}

void SymbolTable::enterScope() {
    // Create new child scope (not used in this simplified impl)
}

void SymbolTable::exitScope() {
    // Return to parent (not used in this simplified impl)
}

// ───────────────────────────────────────────────────────────────────────────
// TypeEnvironment Implementation
// ───────────────────────────────────────────────────────────────────────────
TypeEnvironment::TypeEnvironment() {
    initializeBuiltinTypes();
}

void TypeEnvironment::initializeBuiltinTypes() {
    using namespace ast;
    
    types_["int"] = std::make_unique<PrimitiveType>(PrimitiveKind::Int);
    types_["long"] = std::make_unique<PrimitiveType>(PrimitiveKind::Long);
    types_["float"] = std::make_unique<PrimitiveType>(PrimitiveKind::Float);
    types_["double"] = std::make_unique<PrimitiveType>(PrimitiveKind::Double);
    types_["bool"] = std::make_unique<PrimitiveType>(PrimitiveKind::Bool);
    types_["char"] = std::make_unique<PrimitiveType>(PrimitiveKind::Char);
    types_["string"] = std::make_unique<PrimitiveType>(PrimitiveKind::String);
    types_["any_type"] = std::make_unique<PrimitiveType>(PrimitiveKind::Any);
    types_["never_type"] = std::make_unique<PrimitiveType>(PrimitiveKind::Never);
    types_["null"] = std::make_unique<PrimitiveType>(PrimitiveKind::Null);
}

bool TypeEnvironment::registerType(const std::string& name, 
                                   std::unique_ptr<ast::Type> type) {
    if (typeExists(name)) {
        return false;
    }
    types_[name] = std::move(type);
    return true;
}

const ast::Type* TypeEnvironment::lookupType(const std::string& name) const {
    auto it = types_.find(name);
    return (it != types_.end()) ? it->second.get() : nullptr;
}

bool TypeEnvironment::typeExists(const std::string& name) const {
    return types_.find(name) != types_.end();
}

std::unique_ptr<ast::Type> TypeEnvironment::getIntType() const {
    return std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Int);
}

std::unique_ptr<ast::Type> TypeEnvironment::getLongType() const {
    return std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Long);
}

std::unique_ptr<ast::Type> TypeEnvironment::getFloatType() const {
    return std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Float);
}

std::unique_ptr<ast::Type> TypeEnvironment::getDoubleType() const {
    return std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Double);
}

std::unique_ptr<ast::Type> TypeEnvironment::getBoolType() const {
    return std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Bool);
}

std::unique_ptr<ast::Type> TypeEnvironment::getStringType() const {
    return std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::String);
}

std::unique_ptr<ast::Type> TypeEnvironment::getAnyType() const {
    return std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Any);
}

std::unique_ptr<ast::Type> TypeEnvironment::getNeverType() const {
    return std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Never);
}

std::unique_ptr<ast::Type> TypeEnvironment::getNullType() const {
    return std::make_unique<ast::PrimitiveType>(ast::PrimitiveKind::Null);
}

// ───────────────────────────────────────────────────────────────────────────
// ErrorReporter Implementation
// ───────────────────────────────────────────────────────────────────────────
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

// ───────────────────────────────────────────────────────────────────────────
// TypeChecker Implementation
// ───────────────────────────────────────────────────────────────────────────

bool TypeChecker::isAssignable(const ast::Type& target, 
                               const ast::Type& source) {
    // Any type is assignable to itself
    if (target.equals(source)) {
        return true;
    }
    
    // 'any_type' accepts everything
    if (auto* primTarget = dynamic_cast<const ast::PrimitiveType*>(&target)) {
        if (primTarget->getKind() == ast::PrimitiveKind::Any) {
            return true;
        }
    }
    
    // 'never_type' can be assigned to anything (bottom type)
    if (auto* primSource = dynamic_cast<const ast::PrimitiveType*>(&source)) {
        if (primSource->getKind() == ast::PrimitiveKind::Never) {
            return true;
        }
    }
    
    // Optional type handling: T? can accept T
    if (auto* optTarget = dynamic_cast<const ast::OptionalType*>(&target)) {
        return isAssignable(optTarget->getBaseType(), source);
    }
    
    // Union type handling: T1 | T2 | ... can accept any Ti
    if (auto* unionTarget = dynamic_cast<const ast::UnionType*>(&target)) {
        for (const auto& type : unionTarget->getTypes()) {
            if (isAssignable(*type, source)) {
                return true;
            }
        }
    }
    
    // Numeric widening conversions
    if (auto* primTarget = dynamic_cast<const ast::PrimitiveType*>(&target)) {
        if (auto* primSource = dynamic_cast<const ast::PrimitiveType*>(&source)) {
            using PK = ast::PrimitiveKind;
            auto tk = primTarget->getKind();
            auto sk = primSource->getKind();
            
            // int -> long, float, double
            if (sk == PK::Int && (tk == PK::Long || tk == PK::Float || tk == PK::Double)) {
                return true;
            }
            // long -> float, double
            if (sk == PK::Long && (tk == PK::Float || tk == PK::Double)) {
                return true;
            }
            // float -> double
            if (sk == PK::Float && tk == PK::Double) {
                return true;
            }
        }
    }
    
    return false;
}

bool TypeChecker::isSubtype(const ast::Type& sub, const ast::Type& super) {
    // For now, subtyping is same as assignability
    // In full impl, would handle structural subtyping for records/tuples
    return isAssignable(super, sub);
}

std::optional<std::unique_ptr<ast::Type>> TypeChecker::unify(
    const ast::Type& t1, const ast::Type& t2) {
    
    // If types are equal, unification succeeds
    if (t1.equals(t2)) {
        return t1.clone();
    }
    
    // 'any_type' unifies with everything to 'any_type'
    if (auto* prim1 = dynamic_cast<const ast::PrimitiveType*>(&t1)) {
        if (prim1->getKind() == ast::PrimitiveKind::Any) {
            return typeEnv_.getAnyType();
        }
    }
    if (auto* prim2 = dynamic_cast<const ast::PrimitiveType*>(&t2)) {
        if (prim2->getKind() == ast::PrimitiveKind::Any) {
            return typeEnv_.getAnyType();
        }
    }
    
    // Union types: create union of both
    if (t1.isUnion() || t2.isUnion()) {
        std::vector<std::unique_ptr<ast::Type>> types;
        
        if (auto* u1 = dynamic_cast<const ast::UnionType*>(&t1)) {
            for (const auto& type : u1->getTypes()) {
                types.push_back(type->clone());
            }
        } else {
            types.push_back(t1.clone());
        }
        
        if (auto* u2 = dynamic_cast<const ast::UnionType*>(&t2)) {
            for (const auto& type : u2->getTypes()) {
                types.push_back(type->clone());
            }
        } else {
            types.push_back(t2.clone());
        }
        
        return std::make_unique<ast::UnionType>(std::move(types));
    }
    
    // Numeric widening during unification
    if (auto* prim1 = dynamic_cast<const ast::PrimitiveType*>(&t1)) {
        if (auto* prim2 = dynamic_cast<const ast::PrimitiveType*>(&t2)) {
            using PK = ast::PrimitiveKind;
            auto k1 = prim1->getKind();
            auto k2 = prim2->getKind();
            
            // Widen to larger type
            if ((k1 == PK::Int || k1 == PK::Long) && 
                (k2 == PK::Int || k2 == PK::Long)) {
                return typeEnv_.getLongType();
            }
            if ((k1 == PK::Float || k1 == PK::Double) && 
                (k2 == PK::Float || k2 == PK::Double)) {
                return typeEnv_.getDoubleType();
            }
            if ((k1 == PK::Int || k1 == PK::Long || k1 == PK::Float || k1 == PK::Double) &&
                (k2 == PK::Int || k2 == PK::Long || k2 == PK::Float || k2 == PK::Double)) {
                return typeEnv_.getDoubleType();
            }
        }
    }
    
    // Unification failed
    return std::nullopt;
}

void TypeChecker::reportTypeMismatch(const ast::Type& expected, 
                                    const ast::Type& actual,
                                    size_t line, size_t col) {
    std::ostringstream oss;
    oss << "Type mismatch: expected '" << expected.toString() 
        << "', got '" << actual.toString() << "'";
    errorReporter_.reportError(
        TypeError(ErrorSeverity::Error, oss.str(), line, col));
}

void TypeChecker::enterScope() {
    // In full implementation, would push new scope
}

void TypeChecker::exitScope() {
    // In full implementation, would pop scope
}

// ───────────────────────────────────────────────────────────────────────────
// Visitor Implementations (Placeholder for Full Semantic Analysis)
// ───────────────────────────────────────────────────────────────────────────
void TypeChecker::visit(const ast::PrimitiveType& type) {
    // Validation logic for primitive types
}

void TypeChecker::visit(const ast::UserDefinedType& type) {
    // Check if type is registered in environment
    if (!typeEnv_.typeExists(type.getName())) {
        std::ostringstream oss;
        oss << "Undefined type '" << type.getName() << "'";
        errorReporter_.reportError(
            TypeError(ErrorSeverity::Error, oss.str()));
    }
}

void TypeChecker::visit(const ast::PipelineType& type) {
    // Recursively check input and output types
    type.getInputType().accept(*this);
    type.getOutputType().accept(*this);
}

void TypeChecker::visit(const ast::ListType& type) {
    type.getElementType().accept(*this);
}

void TypeChecker::visit(const ast::MapType& type) {
    type.getKeyType().accept(*this);
    type.getValueType().accept(*this);
}

void TypeChecker::visit(const ast::SetType& type) {
    type.getElementType().accept(*this);
}

void TypeChecker::visit(const ast::StreamType& type) {
    type.getElementType().accept(*this);
}

void TypeChecker::visit(const ast::FutureType& type) {
    type.getValueType().accept(*this);
}

void TypeChecker::visit(const ast::ResultType& type) {
    type.getOkType().accept(*this);
    type.getErrorType().accept(*this);
}

void TypeChecker::visit(const ast::OptionType& type) {
    type.getValueType().accept(*this);
}

void TypeChecker::visit(const ast::ProvenanceType& type) {
    type.getDataType().accept(*this);
}

void TypeChecker::visit(const ast::FunctionType& type) {
    for (const auto& param : type.getParameterTypes()) {
        param->accept(*this);
    }
    type.getReturnType().accept(*this);
}

void TypeChecker::visit(const ast::UnionType& type) {
    for (const auto& t : type.getTypes()) {
        t->accept(*this);
    }
}

void TypeChecker::visit(const ast::OptionalType& type) {
    type.getBaseType().accept(*this);
}

// ───────────────────────────────────────────────────────────────────────────
// DimensionalChecker Implementation
// ───────────────────────────────────────────────────────────────────────────
bool DimensionalChecker::checkBinaryOp(const ast::Type& lhs, 
                                       const ast::Type& rhs,
                                       const std::string& op) {
    // For Milestone 1.2, this is a placeholder
    // Full implementation would extract dimensional metadata from types
    // and verify operations like:
    // - Addition/Subtraction: requires same dimensions
    // - Multiplication: adds dimensions
    // - Division: subtracts dimensions
    
    if (op == "+" || op == "-") {
        return checkSameDimensions(lhs, rhs);
    }
    
    // Multiplication and division always allowed (dimensions combine)
    return true;
}

bool DimensionalChecker::checkSameDimensions(const ast::Type& t1, 
                                            const ast::Type& t2) {
    // Simplified: just check type equality
    // Full impl would extract and compare dimensional exponents
    return t1.equals(t2);
}

std::unique_ptr<ast::Type> DimensionalChecker::computeResultType(
    const ast::Type& lhs, const ast::Type& rhs, const std::string& op) {
    
    // For now, return lhs type
    // Full implementation would compute dimensional algebra
    return lhs.clone();
}

void DimensionalChecker::reportDimensionalError(const std::string& message,
                                               size_t line, size_t col) {
    errorReporter_.reportError(
        TypeError(ErrorSeverity::Error, "Dimensional error: " + message, 
                 line, col));
}

} // namespace olang::semantic