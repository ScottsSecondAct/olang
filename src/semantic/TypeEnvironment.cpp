// ═══════════════════════════════════════════════════════════════════════════
// OLang Type Environment Implementation
// Milestone 1.2: Type System Foundation
// ═══════════════════════════════════════════════════════════════════════════

#include "olang/semantic/TypeEnvironment.hpp"

namespace olang::semantic {

TypeEnvironment::TypeEnvironment() {
    initializeBuiltinTypes();
}

void TypeEnvironment::initializeBuiltinTypes() {
    using namespace frontend;
    
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
                                   std::unique_ptr<frontend::Type> type) {
    if (typeExists(name)) {
        return false;
    }
    types_[name] = std::move(type);
    return true;
}

const frontend::Type* TypeEnvironment::lookupType(const std::string& name) const {
    auto it = types_.find(name);
    return (it != types_.end()) ? it->second.get() : nullptr;
}

bool TypeEnvironment::typeExists(const std::string& name) const {
    return types_.find(name) != types_.end();
}

std::unique_ptr<frontend::Type> TypeEnvironment::getIntType() const {
    return std::make_unique<frontend::PrimitiveType>(frontend::PrimitiveKind::Int);
}

std::unique_ptr<frontend::Type> TypeEnvironment::getLongType() const {
    return std::make_unique<frontend::PrimitiveType>(frontend::PrimitiveKind::Long);
}

std::unique_ptr<frontend::Type> TypeEnvironment::getFloatType() const {
    return std::make_unique<frontend::PrimitiveType>(frontend::PrimitiveKind::Float);
}

std::unique_ptr<frontend::Type> TypeEnvironment::getDoubleType() const {
    return std::make_unique<frontend::PrimitiveType>(frontend::PrimitiveKind::Double);
}

std::unique_ptr<frontend::Type> TypeEnvironment::getBoolType() const {
    return std::make_unique<frontend::PrimitiveType>(frontend::PrimitiveKind::Bool);
}

std::unique_ptr<frontend::Type> TypeEnvironment::getStringType() const {
    return std::make_unique<frontend::PrimitiveType>(frontend::PrimitiveKind::String);
}

std::unique_ptr<frontend::Type> TypeEnvironment::getAnyType() const {
    return std::make_unique<frontend::PrimitiveType>(frontend::PrimitiveKind::Any);
}

std::unique_ptr<frontend::Type> TypeEnvironment::getNeverType() const {
    return std::make_unique<frontend::PrimitiveType>(frontend::PrimitiveKind::Never);
}

std::unique_ptr<frontend::Type> TypeEnvironment::getNullType() const {
    return std::make_unique<frontend::PrimitiveType>(frontend::PrimitiveKind::Null);
}

} // namespace olang::semantic