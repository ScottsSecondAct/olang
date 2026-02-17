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
} // namespace olang::semantic