# grammar/

ANTLR4 grammar source files for OLang.

| File             | Role                                            |
|------------------|-------------------------------------------------|
| OLangLexer.g4    | Tokenises raw UTF-8 source → token stream       |
| OLangParser.g4   | Full grammar; produces CST                      |

Generated C++ sources land in `${CMAKE_BINARY_DIR}/antlr4_generated/`.
Do **not** commit generated files.
