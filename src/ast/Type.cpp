// ═══════════════════════════════════════════════════════════════════════════
// OLang Type System Implementation
// Milestone 1.2: Type System Foundation
// ═══════════════════════════════════════════════════════════════════════════

#include "olang/ast/Type.hpp"
#include <sstream>
#include <algorithm>

namespace olang::ast {

// ───────────────────────────────────────────────────────────────────────────
// PrimitiveType Implementation
// ───────────────────────────────────────────────────────────────────────────
void PrimitiveType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool PrimitiveType::equals(const Type& other) const {
    if (auto* pt = dynamic_cast<const PrimitiveType*>(&other)) {
        return kind_ == pt->kind_;
    }
    return false;
}

std::string PrimitiveType::toString() const {
    switch (kind_) {
        case PrimitiveKind::Int:    return "int";
        case PrimitiveKind::Long:   return "long";
        case PrimitiveKind::Float:  return "float";
        case PrimitiveKind::Double: return "double";
        case PrimitiveKind::Bool:   return "bool";
        case PrimitiveKind::Char:   return "char";
        case PrimitiveKind::String: return "string";
        case PrimitiveKind::Any:    return "any_type";
        case PrimitiveKind::Never:  return "never_type";
        case PrimitiveKind::Null:   return "null";
    }
    return "unknown";
}

std::unique_ptr<Type> PrimitiveType::clone() const {
    return std::make_unique<PrimitiveType>(kind_);
}

// ───────────────────────────────────────────────────────────────────────────
// UserDefinedType Implementation
// ───────────────────────────────────────────────────────────────────────────
void UserDefinedType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool UserDefinedType::equals(const Type& other) const {
    if (auto* udt = dynamic_cast<const UserDefinedType*>(&other)) {
        if (name_ != udt->name_) return false;
        if (typeArguments_.size() != udt->typeArguments_.size()) return false;
        
        for (size_t i = 0; i < typeArguments_.size(); ++i) {
            if (!typeArguments_[i]->equals(*udt->typeArguments_[i])) {
                return false;
            }
        }
        return true;
    }
    return false;
}

std::string UserDefinedType::toString() const {
    std::ostringstream oss;
    oss << name_;
    if (!typeArguments_.empty()) {
        oss << "<";
        for (size_t i = 0; i < typeArguments_.size(); ++i) {
            if (i > 0) oss << ", ";
            oss << typeArguments_[i]->toString();
        }
        oss << ">";
    }
    return oss.str();
}

std::unique_ptr<Type> UserDefinedType::clone() const {
    std::vector<std::unique_ptr<Type>> clonedArgs;
    for (const auto& arg : typeArguments_) {
        clonedArgs.push_back(arg->clone());
    }
    return std::make_unique<UserDefinedType>(name_, std::move(clonedArgs));
}

// ───────────────────────────────────────────────────────────────────────────
// PipelineType Implementation
// ───────────────────────────────────────────────────────────────────────────
void PipelineType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool PipelineType::equals(const Type& other) const {
    if (auto* pt = dynamic_cast<const PipelineType*>(&other)) {
        return inputType_->equals(*pt->inputType_) && 
               outputType_->equals(*pt->outputType_);
    }
    return false;
}

std::string PipelineType::toString() const {
    return "Pipeline<" + inputType_->toString() + " -> " + 
           outputType_->toString() + ">";
}

std::unique_ptr<Type> PipelineType::clone() const {
    return std::make_unique<PipelineType>(inputType_->clone(), 
                                          outputType_->clone());
}

// ───────────────────────────────────────────────────────────────────────────
// ListType Implementation
// ───────────────────────────────────────────────────────────────────────────
void ListType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool ListType::equals(const Type& other) const {
    if (auto* lt = dynamic_cast<const ListType*>(&other)) {
        return elementType_->equals(*lt->elementType_);
    }
    return false;
}

std::string ListType::toString() const {
    return "List<" + elementType_->toString() + ">";
}

std::unique_ptr<Type> ListType::clone() const {
    return std::make_unique<ListType>(elementType_->clone());
}

// ───────────────────────────────────────────────────────────────────────────
// MapType Implementation
// ───────────────────────────────────────────────────────────────────────────
void MapType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool MapType::equals(const Type& other) const {
    if (auto* mt = dynamic_cast<const MapType*>(&other)) {
        return keyType_->equals(*mt->keyType_) && 
               valueType_->equals(*mt->valueType_);
    }
    return false;
}

std::string MapType::toString() const {
    return "Map<" + keyType_->toString() + ", " + 
           valueType_->toString() + ">";
}

std::unique_ptr<Type> MapType::clone() const {
    return std::make_unique<MapType>(keyType_->clone(), valueType_->clone());
}

// ───────────────────────────────────────────────────────────────────────────
// SetType Implementation
// ───────────────────────────────────────────────────────────────────────────
void SetType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool SetType::equals(const Type& other) const {
    if (auto* st = dynamic_cast<const SetType*>(&other)) {
        return elementType_->equals(*st->elementType_);
    }
    return false;
}

std::string SetType::toString() const {
    return "Set<" + elementType_->toString() + ">";
}

std::unique_ptr<Type> SetType::clone() const {
    return std::make_unique<SetType>(elementType_->clone());
}

// ───────────────────────────────────────────────────────────────────────────
// StreamType Implementation
// ───────────────────────────────────────────────────────────────────────────
void StreamType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool StreamType::equals(const Type& other) const {
    if (auto* st = dynamic_cast<const StreamType*>(&other)) {
        return elementType_->equals(*st->elementType_);
    }
    return false;
}

std::string StreamType::toString() const {
    return "Stream<" + elementType_->toString() + ">";
}

std::unique_ptr<Type> StreamType::clone() const {
    return std::make_unique<StreamType>(elementType_->clone());
}

// ───────────────────────────────────────────────────────────────────────────
// FutureType Implementation
// ───────────────────────────────────────────────────────────────────────────
void FutureType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool FutureType::equals(const Type& other) const {
    if (auto* ft = dynamic_cast<const FutureType*>(&other)) {
        return valueType_->equals(*ft->valueType_);
    }
    return false;
}

std::string FutureType::toString() const {
    return "Future<" + valueType_->toString() + ">";
}

std::unique_ptr<Type> FutureType::clone() const {
    return std::make_unique<FutureType>(valueType_->clone());
}

// ───────────────────────────────────────────────────────────────────────────
// ResultType Implementation
// ───────────────────────────────────────────────────────────────────────────
void ResultType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool ResultType::equals(const Type& other) const {
    if (auto* rt = dynamic_cast<const ResultType*>(&other)) {
        return okType_->equals(*rt->okType_) && 
               errType_->equals(*rt->errType_);
    }
    return false;
}

std::string ResultType::toString() const {
    return "Result<" + okType_->toString() + ", " + 
           errType_->toString() + ">";
}

std::unique_ptr<Type> ResultType::clone() const {
    return std::make_unique<ResultType>(okType_->clone(), errType_->clone());
}

// ───────────────────────────────────────────────────────────────────────────
// OptionType Implementation
// ───────────────────────────────────────────────────────────────────────────
void OptionType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool OptionType::equals(const Type& other) const {
    if (auto* ot = dynamic_cast<const OptionType*>(&other)) {
        return valueType_->equals(*ot->valueType_);
    }
    return false;
}

std::string OptionType::toString() const {
    return "Option<" + valueType_->toString() + ">";
}

std::unique_ptr<Type> OptionType::clone() const {
    return std::make_unique<OptionType>(valueType_->clone());
}

// ───────────────────────────────────────────────────────────────────────────
// ProvenanceType Implementation
// ───────────────────────────────────────────────────────────────────────────
void ProvenanceType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool ProvenanceType::equals(const Type& other) const {
    if (auto* pt = dynamic_cast<const ProvenanceType*>(&other)) {
        return dataType_->equals(*pt->dataType_);
    }
    return false;
}

std::string ProvenanceType::toString() const {
    return "Provenance<" + dataType_->toString() + ">";
}

std::unique_ptr<Type> ProvenanceType::clone() const {
    return std::make_unique<ProvenanceType>(dataType_->clone());
}

// ───────────────────────────────────────────────────────────────────────────
// FunctionType Implementation
// ───────────────────────────────────────────────────────────────────────────
void FunctionType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool FunctionType::equals(const Type& other) const {
    if (auto* ft = dynamic_cast<const FunctionType*>(&other)) {
        if (parameterTypes_.size() != ft->parameterTypes_.size()) {
            return false;
        }
        for (size_t i = 0; i < parameterTypes_.size(); ++i) {
            if (!parameterTypes_[i]->equals(*ft->parameterTypes_[i])) {
                return false;
            }
        }
        return returnType_->equals(*ft->returnType_);
    }
    return false;
}

std::string FunctionType::toString() const {
    std::ostringstream oss;
    oss << "(";
    for (size_t i = 0; i < parameterTypes_.size(); ++i) {
        if (i > 0) oss << ", ";
        oss << parameterTypes_[i]->toString();
    }
    oss << ") -> " << returnType_->toString();
    return oss.str();
}

std::unique_ptr<Type> FunctionType::clone() const {
    std::vector<std::unique_ptr<Type>> clonedParams;
    for (const auto& param : parameterTypes_) {
        clonedParams.push_back(param->clone());
    }
    return std::make_unique<FunctionType>(std::move(clonedParams), 
                                          returnType_->clone());
}

// ───────────────────────────────────────────────────────────────────────────
// UnionType Implementation
// ───────────────────────────────────────────────────────────────────────────
void UnionType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool UnionType::equals(const Type& other) const {
    if (auto* ut = dynamic_cast<const UnionType*>(&other)) {
        if (types_.size() != ut->types_.size()) return false;
        
        // Union equality requires all types to match (order-independent)
        for (const auto& t1 : types_) {
            bool found = false;
            for (const auto& t2 : ut->types_) {
                if (t1->equals(*t2)) {
                    found = true;
                    break;
                }
            }
            if (!found) return false;
        }
        return true;
    }
    return false;
}

std::string UnionType::toString() const {
    std::ostringstream oss;
    for (size_t i = 0; i < types_.size(); ++i) {
        if (i > 0) oss << " | ";
        oss << types_[i]->toString();
    }
    return oss.str();
}

std::unique_ptr<Type> UnionType::clone() const {
    std::vector<std::unique_ptr<Type>> clonedTypes;
    for (const auto& type : types_) {
        clonedTypes.push_back(type->clone());
    }
    return std::make_unique<UnionType>(std::move(clonedTypes));
}

// ───────────────────────────────────────────────────────────────────────────
// OptionalType Implementation
// ───────────────────────────────────────────────────────────────────────────
void OptionalType::accept(TypeVisitor& visitor) const {
    visitor.visit(*this);
}

bool OptionalType::equals(const Type& other) const {
    if (auto* ot = dynamic_cast<const OptionalType*>(&other)) {
        return baseType_->equals(*ot->baseType_);
    }
    return false;
}

std::string OptionalType::toString() const {
    return baseType_->toString() + "?";
}

std::unique_ptr<Type> OptionalType::clone() const {
    return std::make_unique<OptionalType>(baseType_->clone());
}

} // namespace olang::ast