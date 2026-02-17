#pragma once

#include "olang/ast/Type.hpp"
#include <unordered_map>
#include <string>
#include <memory>
#include <vector>
#include <optional>

namespace olang::semantic {
  
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
} // namespace olang::semantic