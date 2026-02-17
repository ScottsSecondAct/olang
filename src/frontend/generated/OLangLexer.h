
// Generated from /home/scott/Projects/olang/grammar/OLangLexer.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"




class  OLangLexer : public antlr4::Lexer {
public:
  enum {
    IMPORT = 1, FROM = 2, LET = 3, AS = 4, WITH = 5, TYPE = 6, EXTENDS = 7, 
    ANNOTATION = 8, ANNOTATED = 9, DEF = 10, MATCH = 11, WHEN = 12, WHERE = 13, 
    IN = 14, AGENT = 15, CAPABILITY = 16, PHYSICAL = 17, VIRTUAL = 18, ATOMIC = 19, 
    PROOF = 20, INVARIANT = 21, ASSERT = 22, ALWAYS = 23, EVENTUALLY = 24, 
    DURING = 25, UNTIL = 26, SOLVER = 27, SATISFY = 28, MINIMIZE = 29, MAXIMIZE = 30, 
    VARIABLE = 31, STREAM = 32, RULE = 33, EMIT = 34, SIGNAL = 35, WITHIN = 36, 
    MAP = 37, FILTER = 38, REDUCE = 39, FOREACH = 40, GROUP_BY = 41, FLATMAP = 42, 
    ZIP = 43, PARTITION = 44, TAKE = 45, DROP = 46, TAKE_WHILE = 47, DROP_WHILE = 48, 
    SORT_BY = 49, DISTINCT = 50, COUNT = 51, FIND = 52, ANY = 53, ALL = 54, 
    JOIN = 55, ON = 56, WINDOW = 57, CHUNK = 58, SCAN = 59, COLLECT = 60, 
    INT_TYPE = 61, LONG_TYPE = 62, FLOAT_TYPE = 63, DOUBLE_TYPE = 64, BOOL_TYPE = 65, 
    CHAR_TYPE = 66, STRING_TYPE = 67, ANY_TYPE = 68, NEVER_TYPE = 69, NULL_LIT = 70, 
    LIST_TYPE = 71, MAP_TYPE = 72, SET_TYPE = 73, PIPELINE_TYPE = 74, STREAM_TYPE = 75, 
    FUTURE_TYPE = 76, RESULT_TYPE = 77, OPTION_TYPE = 78, PROVENANCE_TYPE = 79, 
    ADD = 80, SUB = 81, MUL = 82, DIV = 83, MOD = 84, EQ = 85, NEQ = 86, 
    LE = 87, LT = 88, GE = 89, GT = 90, AND_OP = 91, OR_OP = 92, NOT = 93, 
    AND = 94, OR = 95, PIPELINE_OP = 96, PARALLEL_OP = 97, LAMBDA_ARROW = 98, 
    ARROW = 99, UNION_PIPE = 100, NULL_COALESCE = 101, MUTATE_AT = 102, 
    BIO_TRANSFORM = 103, RANGE_OP = 104, INCLUSIVE_RANGE = 105, EXCLUSIVE_RANGE = 106, 
    POSITION_START = 107, POSITION_END = 108, COMPLEMENT = 109, WILDCARD = 110, 
    BOOLEAN = 111, INT_LITERAL = 112, DECIMAL_LITERAL = 113, STRING = 114, 
    RAW_STRING = 115, MULTILINE_STRING = 116, LPAREN = 117, RPAREN = 118, 
    LBRACK = 119, RBRACK = 120, LCURLY = 121, RCURLY = 122, DOT = 123, COMMA = 124, 
    COLON = 125, SEMI = 126, EQUALS = 127, ID = 128, COMMENT = 129, BLOCK_COMMENT = 130, 
    WS = 131
  };

  explicit OLangLexer(antlr4::CharStream *input);

  ~OLangLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};

