#include "olang/frontend/ASTBuilder.h"

namespace olang {

std::any ASTBuilder::visitProgram(OLangParser::ProgramContext* ctx) {
  // TODO: walk ctx->statementList() and build the AST
  // For now, just return nullptr
  return nullptr;
}

} // namespace olang
