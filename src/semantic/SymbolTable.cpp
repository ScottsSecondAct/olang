// ═══════════════════════════════════════════════════════════════════════════
// OLang Symbol Table Implementation
// Milestone 1.2: Type System Foundation
// ═══════════════════════════════════════════════════════════════════════════

#include "olang/semantic/SymbolTable.hpp"

namespace olang::semantic {

bool SymbolTable::declare(const std::string& name, 
                          std::unique_ptr<frontend::Type> type,
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
    // In full implementation, would push new scope
}

void SymbolTable::exitScope() {
    // In full implementation, would pop scope
}

} // namespace olang::semantic