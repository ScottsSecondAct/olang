lexer grammar OLangLexer;

IMPORT:'import'; FROM:'from'; LET:'let'; AS:'as'; WITH:'with';
TYPE:'type'; EXTENDS:'extends'; ANNOTATION:'annotation';
ANNOTATED:'annotated'; DEF:'def'; MATCH:'match'; WHEN:'when';
WHERE:'where'; IN:'in';

AGENT:'agent'; CAPABILITY:'capability';
PHYSICAL:'PHYSICAL'; VIRTUAL:'VIRTUAL'; ATOMIC:'ATOMIC';

PROOF:'proof'; INVARIANT:'invariant'; ASSERT:'assert';
ALWAYS:'always'; EVENTUALLY:'eventually'; DURING:'during'; UNTIL:'until';

SOLVER:'solver'; SATISFY:'satisfy'; MINIMIZE:'minimize';
MAXIMIZE:'maximize'; VARIABLE:'variable';

STREAM:'stream'; RULE:'rule'; EMIT:'emit'; SIGNAL:'signal'; WITHIN:'within';

MAP:'map'; FILTER:'filter'; REDUCE:'reduce'; FOREACH:'foreach';
GROUP_BY:'group_by'; FLATMAP:'flatmap'; ZIP:'zip'; PARTITION:'partition';
TAKE:'take'; DROP:'drop'; TAKE_WHILE:'take_while'; DROP_WHILE:'drop_while';
SORT_BY:'sort_by'; DISTINCT:'distinct'; COUNT:'count'; FIND:'find';
ANY:'any'; ALL:'all'; JOIN:'join'; ON:'on'; WINDOW:'window'; CHUNK:'chunk';
SCAN:'scan'; COLLECT:'collect';

INT_TYPE:'int'; LONG_TYPE:'long'; FLOAT_TYPE:'float'; DOUBLE_TYPE:'double';
BOOL_TYPE:'bool'; CHAR_TYPE:'char'; STRING_TYPE:'string'; ANY_TYPE:'any_type';
NEVER_TYPE:  'never_type'; NULL_LIT:    'null';
LIST_TYPE:'List'; MAP_TYPE:'Map'; SET_TYPE:'Set'; PIPELINE_TYPE:'Pipeline';
STREAM_TYPE:'Stream'; FUTURE_TYPE:'Future'; RESULT_TYPE:'Result';
OPTION_TYPE:'Option'; PROVENANCE_TYPE:'Provenance';

ADD:'+'; SUB:'-'; MUL:'*'; DIV:'/'; MOD:'%';
EQ:'=='; NEQ:'!='; LE:'<='; LT:'<'; GE:'>='; GT:'>';
AND_OP:'&&'; OR_OP:'||'; NOT:'!'; AND:'and'; OR:'or';

PIPELINE_OP:'↦'|'~>'; PARALLEL_OP:'|||'; LAMBDA_ARROW:'=>'; ARROW:'->';
UNION_PIPE:'|'; NULL_COALESCE:'??';

MUTATE_AT:'@'; BIO_TRANSFORM:'→'|'-->'; RANGE_OP:'..';
INCLUSIVE_RANGE:'..='; EXCLUSIVE_RANGE:'..<';
POSITION_START:'^'; POSITION_END:'$'; COMPLEMENT:'~'; WILDCARD:'_';

BOOLEAN:'true'|'false';
INT_LITERAL: DIGIT+ [lL]?;
DECIMAL_LITERAL: DIGIT+ ('.' DIGIT+)? ([eE][+-]? DIGIT+)? [fFdD]?;
STRING: '"' STR_CONTENT* '"';
RAW_STRING: 'r"' (~["])* '"';
MULTILINE_STRING: '"""' .*? '"""';

LPAREN:'('; RPAREN:')'; LBRACK:'['; RBRACK:']';
LCURLY:'{'; RCURLY:'}'; DOT:'.'; COMMA:',';
COLON:':'; SEMI:';'; EQUALS:'=';

ID: ID_START ID_CONTINUE*;
COMMENT: '//' ~[\r\n]* -> skip;
BLOCK_COMMENT: '/*' .*? '*/' -> skip;
WS: [ \t\r\n]+ -> skip;

fragment DIGIT: [0-9];
fragment ID_START: [\p{L}_];
fragment ID_CONTINUE: [\p{L}\p{N}_];
fragment STR_CONTENT: EscapeSequence | ~["\\\r\n];
fragment EscapeSequence: '\\' ([btnfr"'\\] | UnicodeEscape);
fragment UnicodeEscape:
    'u' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
  | 'U' HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
        HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT;
fragment HEX_DIGIT: [0-9a-fA-F];
