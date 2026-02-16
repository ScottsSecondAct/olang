#!/usr/bin/env bash
# scripts/generate_grammar.sh
# Run manually if you need to regenerate the ANTLR4 C++ sources from scratch.
# CMake runs this automatically when tools/antlr4-complete.jar is present.
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
ROOT="$SCRIPT_DIR/.."
JAR="$ROOT/tools/antlr4-complete.jar"
OUT="$ROOT/src/frontend/generated"

if [[ ! -f "$JAR" ]]; then
  echo "ERROR: $JAR not found."
  echo "Download from https://www.antlr.org/download.html and place as tools/antlr4-complete.jar"
  exit 1
fi

echo "==> Generating ANTLR4 C++ sources..."
mkdir -p "$OUT"
java -jar "$JAR" \
  -Dlanguage=Cpp \
  -visitor \
  -listener \
  -o "$OUT" \
  "$ROOT/grammar/OLangLexer.g4" \
  "$ROOT/grammar/OLangParser.g4"

echo "==> Applying 4.10 runtime compatibility patch..."
cmake -P "$SCRIPT_DIR/patch_antlr4_generated.cmake" "$OUT"

echo "==> Done. Generated files in: $OUT"
ls -lh "$OUT/"*.cpp "$OUT/"*.h