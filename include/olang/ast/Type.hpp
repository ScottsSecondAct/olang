// ═══════════════════════════════════════════════════════════════════════════
// OLang Type System AST Nodes
// Milestone 1.2: Type System Foundation
// ═══════════════════════════════════════════════════════════════════════════

#pragma once

#include <memory>
#include <string>
#include <vector>
#include <optional>
#include <variant>

namespace olang::ast {

// ───────────────────────────────────────────────────────────────────────────
// Forward Declarations
// ───────────────────────────────────────────────────────────────────────────
class Type;
class PrimitiveType;
class UserDefinedType;
class PipelineType;
class ListType;
class MapType;
class SetType;
class StreamType;
class FutureType;
class ResultType;
class OptionType;
class ProvenanceType;
class FunctionType;
class UnionType;
class OptionalType;

// ───────────────────────────────────────────────────────────────────────────
// Type Base Class (Visitor Pattern for Semantic Analysis)
// ───────────────────────────────────────────────────────────────────────────
class Type {
public:
    virtual ~Type() = default;
    
    // Visitor pattern for type checking
    virtual void accept(class TypeVisitor& visitor) const = 0;
    
    // Type equality (structural)
    virtual bool equals(const Type& other) const = 0;
    
    // Type string representation (for diagnostics)
    virtual std::string toString() const = 0;
    
    // Clone for AST transformations
    virtual std::unique_ptr<Type> clone() const = 0;
    
    // Type categorization
    virtual bool isPrimitive() const { return false; }
    virtual bool isUserDefined() const { return false; }
    virtual bool isParametric() const { return false; }
    virtual bool isOptional() const { return false; }
    virtual bool isUnion() const { return false; }
};

// ───────────────────────────────────────────────────────────────────────────
// Primitive Types (Zero-Cost Abstraction Layer)
// ───────────────────────────────────────────────────────────────────────────
enum class PrimitiveKind {
    Int,
    Long,
    Float,
    Double,
    Bool,
    Char,
    String,
    Any,
    Never,
    Null
};

class PrimitiveType : public Type {
public:
    explicit PrimitiveType(PrimitiveKind kind) : kind_(kind) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    bool isPrimitive() const override { return true; }
    
    PrimitiveKind getKind() const { return kind_; }
    
private:
    PrimitiveKind kind_;
};

// ───────────────────────────────────────────────────────────────────────────
// User-Defined Types (Nominal Typing)
// ───────────────────────────────────────────────────────────────────────────
class UserDefinedType : public Type {
public:
    UserDefinedType(std::string name, std::vector<std::unique_ptr<Type>> typeArgs = {})
        : name_(std::move(name)), typeArguments_(std::move(typeArgs)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    bool isUserDefined() const override { return true; }
    bool isParametric() const override { return !typeArguments_.empty(); }
    
    const std::string& getName() const { return name_; }
    const std::vector<std::unique_ptr<Type>>& getTypeArguments() const { 
        return typeArguments_; 
    }
    
private:
    std::string name_;
    std::vector<std::unique_ptr<Type>> typeArguments_;
};

// ───────────────────────────────────────────────────────────────────────────
// Pipeline Type: Pipeline<InputType -> OutputType>
// ───────────────────────────────────────────────────────────────────────────
class PipelineType : public Type {
public:
    PipelineType(std::unique_ptr<Type> input, std::unique_ptr<Type> output)
        : inputType_(std::move(input)), outputType_(std::move(output)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    
    const Type& getInputType() const { return *inputType_; }
    const Type& getOutputType() const { return *outputType_; }
    
private:
    std::unique_ptr<Type> inputType_;
    std::unique_ptr<Type> outputType_;
};

// ───────────────────────────────────────────────────────────────────────────
// Parametric Container Types
// ───────────────────────────────────────────────────────────────────────────
class ListType : public Type {
public:
    explicit ListType(std::unique_ptr<Type> elementType)
        : elementType_(std::move(elementType)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    
    const Type& getElementType() const { return *elementType_; }
    
private:
    std::unique_ptr<Type> elementType_;
};

class MapType : public Type {
public:
    MapType(std::unique_ptr<Type> keyType, std::unique_ptr<Type> valueType)
        : keyType_(std::move(keyType)), valueType_(std::move(valueType)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    
    const Type& getKeyType() const { return *keyType_; }
    const Type& getValueType() const { return *valueType_; }
    
private:
    std::unique_ptr<Type> keyType_;
    std::unique_ptr<Type> valueType_;
};

class SetType : public Type {
public:
    explicit SetType(std::unique_ptr<Type> elementType)
        : elementType_(std::move(elementType)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    
    const Type& getElementType() const { return *elementType_; }
    
private:
    std::unique_ptr<Type> elementType_;
};

// ───────────────────────────────────────────────────────────────────────────
// Reactive & Async Types
// ───────────────────────────────────────────────────────────────────────────
class StreamType : public Type {
public:
    explicit StreamType(std::unique_ptr<Type> elementType)
        : elementType_(std::move(elementType)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    
    const Type& getElementType() const { return *elementType_; }
    
private:
    std::unique_ptr<Type> elementType_;
};

class FutureType : public Type {
public:
    explicit FutureType(std::unique_ptr<Type> valueType)
        : valueType_(std::move(valueType)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    
    const Type& getValueType() const { return *valueType_; }
    
private:
    std::unique_ptr<Type> valueType_;
};

// ───────────────────────────────────────────────────────────────────────────
// Error-Handling Types
// ───────────────────────────────────────────────────────────────────────────
class ResultType : public Type {
public:
    ResultType(std::unique_ptr<Type> okType, std::unique_ptr<Type> errType)
        : okType_(std::move(okType)), errType_(std::move(errType)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    
    const Type& getOkType() const { return *okType_; }
    const Type& getErrorType() const { return *errType_; }
    
private:
    std::unique_ptr<Type> okType_;
    std::unique_ptr<Type> errType_;
};

class OptionType : public Type {
public:
    explicit OptionType(std::unique_ptr<Type> valueType)
        : valueType_(std::move(valueType)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    
    const Type& getValueType() const { return *valueType_; }
    
private:
    std::unique_ptr<Type> valueType_;
};

// ───────────────────────────────────────────────────────────────────────────
// Provenance Type (Research Lineage Tracking)
// ───────────────────────────────────────────────────────────────────────────
class ProvenanceType : public Type {
public:
    explicit ProvenanceType(std::unique_ptr<Type> dataType)
        : dataType_(std::move(dataType)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    
    const Type& getDataType() const { return *dataType_; }
    
private:
    std::unique_ptr<Type> dataType_;
};

// ───────────────────────────────────────────────────────────────────────────
// Function Type: (T1, T2, ..., Tn) -> R
// ───────────────────────────────────────────────────────────────────────────
class FunctionType : public Type {
public:
    FunctionType(std::vector<std::unique_ptr<Type>> paramTypes, 
                 std::unique_ptr<Type> returnType)
        : parameterTypes_(std::move(paramTypes)), 
          returnType_(std::move(returnType)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    
    const std::vector<std::unique_ptr<Type>>& getParameterTypes() const { 
        return parameterTypes_; 
    }
    const Type& getReturnType() const { return *returnType_; }
    
private:
    std::vector<std::unique_ptr<Type>> parameterTypes_;
    std::unique_ptr<Type> returnType_;
};

// ───────────────────────────────────────────────────────────────────────────
// Union Type: T1 | T2 | ... | Tn
// ───────────────────────────────────────────────────────────────────────────
class UnionType : public Type {
public:
    explicit UnionType(std::vector<std::unique_ptr<Type>> types)
        : types_(std::move(types)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    bool isUnion() const override { return true; }
    
    const std::vector<std::unique_ptr<Type>>& getTypes() const { 
        return types_; 
    }
    
private:
    std::vector<std::unique_ptr<Type>> types_;
};

// ───────────────────────────────────────────────────────────────────────────
// Optional Type Wrapper: T?
// ───────────────────────────────────────────────────────────────────────────
class OptionalType : public Type {
public:
    explicit OptionalType(std::unique_ptr<Type> baseType)
        : baseType_(std::move(baseType)) {}
    
    void accept(TypeVisitor& visitor) const override;
    bool equals(const Type& other) const override;
    std::string toString() const override;
    std::unique_ptr<Type> clone() const override;
    bool isOptional() const override { return true; }
    
    const Type& getBaseType() const { return *baseType_; }
    
private:
    std::unique_ptr<Type> baseType_;
};

// ───────────────────────────────────────────────────────────────────────────
// Type Visitor (Double-Dispatch Pattern for Semantic Analysis)
// ───────────────────────────────────────────────────────────────────────────
class TypeVisitor {
public:
    virtual ~TypeVisitor() = default;
    
    virtual void visit(const PrimitiveType& type) = 0;
    virtual void visit(const UserDefinedType& type) = 0;
    virtual void visit(const PipelineType& type) = 0;
    virtual void visit(const ListType& type) = 0;
    virtual void visit(const MapType& type) = 0;
    virtual void visit(const SetType& type) = 0;
    virtual void visit(const StreamType& type) = 0;
    virtual void visit(const FutureType& type) = 0;
    virtual void visit(const ResultType& type) = 0;
    virtual void visit(const OptionType& type) = 0;
    virtual void visit(const ProvenanceType& type) = 0;
    virtual void visit(const FunctionType& type) = 0;
    virtual void visit(const UnionType& type) = 0;
    virtual void visit(const OptionalType& type) = 0;
};

} // namespace olang::ast