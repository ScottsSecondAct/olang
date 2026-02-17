#pragma once
#include "OLangParserBaseVisitor.h"
#include "olang/frontend/ASTContext.h"
#include "olang/frontend/AST.h"

namespace olang {

class ASTBuilder : public OLangParserBaseVisitor {
public:
  explicit ASTBuilder(ast::ASTContext& ctx) : ctx_(ctx) {}

  // Start with just the program rule
  std::any visitProgram(OLangParser::ProgramContext* ctx) override;

private:
  ast::ASTContext& ctx_;
};

} // namespace olang
