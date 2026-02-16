// olangc — OLang compiler driver
// Pipeline: source → ANTLR4 → AST → Sema → LTL → IRGen → NVPTX → binary
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

#include "antlr4-runtime.h"
#include "OLangLexer.h"
#include "OLangParser.h"
#include "olang/frontend/ASTContext.h"
#include "olang/frontend/Diagnostic.h"

namespace fs = std::filesystem;

static void usage(const char* argv0) {
  std::cerr << "Usage: " << argv0 << " [--emit-ast|--emit-ir|--emit-ptx|--verify-only] "
            << "[--opt 0-3] <source.olang> -o <output>\n";
}

int main(int argc, char** argv) {
  std::string inputPath, outputPath = "a.out";
  bool emitAst=false, emitIr=false, emitPtx=false, verifyOnly=false;
  int  optLevel=2;

  for (int i=1; i<argc; ++i) {
    std::string a = argv[i];
    if      (a == "--emit-ast")    emitAst    = true;
    else if (a == "--emit-ir")     emitIr     = true;
    else if (a == "--emit-ptx")    emitPtx    = true;
    else if (a == "--verify-only") verifyOnly = true;
    else if (a == "--opt" && i+1<argc) optLevel = std::atoi(argv[++i]);
    else if (a == "-o"   && i+1<argc) outputPath = argv[++i];
    else if (a[0] != '-') inputPath = a;
    else { std::cerr << "Unknown flag: " << a << '\n'; return 1; }
  }

  if (inputPath.empty()) { usage(argv[0]); return 1; }
  if (!fs::exists(inputPath)) {
    std::cerr << "olangc: file not found: " << inputPath << '\n'; return 1;
  }

  std::ifstream src(inputPath);
  antlr4::ANTLRInputStream input(src);
  OLangLexer  lexer(&input);
  antlr4::CommonTokenStream tokens(&lexer);
  OLangParser parser(&tokens);
  auto* tree = parser.program();

  olang::DiagnosticEngine diags;
  if (parser.getNumberOfSyntaxErrors() > 0) {
    diags.error({}, "Syntax errors.");
    diags.printAll(inputPath);
    return 1;
  }

  olang::ast::ASTContext ctx;
  // TODO Phase 1: ASTBuilder(ctx, tree)
  if (emitAst)    { std::cout << "[AST] Phase 1 TODO\n";  return 0; }
  // TODO Phase 1: SemanticAnalyser
  if (verifyOnly) { diags.printAll(inputPath); return diags.hasErrors() ? 1 : 0; }
  // TODO Phase 2: IRGen
  if (emitIr)     { std::cout << "[IR]  Phase 2 TODO\n";  return 0; }
  // TODO Phase 2: NVPTX
  if (emitPtx)    { std::cout << "[PTX] Phase 2 TODO\n";  return 0; }

  std::cout << "olangc: '" << inputPath << "' parsed OK. Codegen staged for Phase 2.\n";
  return 0;
}
