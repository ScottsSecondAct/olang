parser grammar OLangParser;
options {tokenVocab = OLangLexer;}

program : statementList EOF ;
statementList : statement (SEMI? statement)* SEMI? ;

statement
  : declaration | assignmentStatement | annotationStatement
  | expressionStatement | emitStatement | signalStatement | assertStatement
  ;

expressionStatement : expression SEMI ;
emitStatement       : EMIT expression SEMI ;
signalStatement     : SIGNAL expression SEMI ;
assertStatement     : ASSERT LPAREN expression RPAREN SEMI ;

declaration
  : importDeclaration | bindingDeclaration | functionDeclaration
  | pipelineDeclaration | annotationTypeDeclaration | typeDeclaration
  | agentDeclaration | solverDeclaration | proofDeclaration
  ;

agentDeclaration : AGENT ID LCURLY agentMember* RCURLY ;
agentMember
  : CAPABILITY idList SEMI
  | STREAM ID COLON type SEMI
  | RULE (ID|STRING) LCURLY WHEN expression ARROW blockExpression RCURLY
  | declaration
  ;

solverDeclaration : SOLVER ID LCURLY solverMember* RCURLY ;
solverMember
  : VARIABLE ID COLON type (IN expression)? SEMI
  | SATISFY LCURLY expressionStatement* RCURLY
  | (MINIMIZE | MAXIMIZE) expression SEMI
  ;

proofDeclaration : PROOF ID LCURLY invariantDeclaration* RCURLY ;
invariantDeclaration : INVARIANT ID LCURLY expressionStatement* RCURLY ;

importDeclaration : IMPORT dottedAsNamesList SEMI | FROM relativeModule IMPORT importTargets SEMI ;
bindingDeclaration : LET ID (COLON type)? EQUALS expression ;
functionDeclaration : DEF ID LPAREN typedParameterList? RPAREN ARROW type EQUALS expression ;
pipelineDeclaration : ID COLON PIPELINE_TYPE LT type ARROW type GT EQUALS pipelineBody ;
typeDeclaration : TYPE ID genericParameters? LCURLY typedFieldList RCURLY whereClause? ;
annotationTypeDeclaration : ANNOTATION ID LCURLY typedFieldList RCURLY ;
annotationStatement : ANNOTATED declaration WITH LCURLY annotationPairList RCURLY ;

expression : lambdaExpression | functionalExpression | pipelineExpression ;

pipelineExpression : nullCoalesceExpression ((PIPELINE_OP | PARALLEL_OP) nullCoalesceExpression)* ;
pipelineBody : expression ((PIPELINE_OP | PARALLEL_OP) expression)* ;
nullCoalesceExpression : ternaryExpression (NULL_COALESCE ternaryExpression)* ;
ternaryExpression : logicalOrExpression (OPTIONAL expression COLON ternaryExpression)? ;
logicalOrExpression : logicalAndExpression ((OR_OP | OR) logicalAndExpression)* ;
logicalAndExpression : equalityExpression (AND_OP equalityExpression)* ;
equalityExpression : relationalExpression ((EQ | NEQ) relationalExpression)* ;
relationalExpression : additiveExpression ((LE | LT | GE | GT | WITHIN | DURING | UNTIL) additiveExpression)* ;
additiveExpression : multiplicativeExpression ((ADD | SUB) multiplicativeExpression)* ;
multiplicativeExpression : unaryExpression ((MUL | DIV | MOD) unaryExpression)* ;
unaryExpression
  : (NOT | SUB | ADD | ALWAYS | EVENTUALLY) unaryExpression
  | errorPropagationExpression
  ;
errorPropagationExpression : postfixExpression OPTIONAL? ;
postfixExpression : primaryExpression callSuffix* ;
callSuffix : callArguments | DOT ID callArguments? | LBRACK expression RBRACK ;
callArguments : LPAREN argumentList? RPAREN ;
primaryExpression
  : literalValue | lambdaExpression | matchExpression
  | listExpression | objectExpression | qualifiedName
  | LPAREN expression RPAREN
  ;

type : optionalType (UNION_PIPE optionalType)* ;
optionalType : baseType OPTIONAL? ;
baseType
  : primitiveType | userDefinedType | pipelineType | listType | mapType
  | setType | streamType | futureType | resultType | optionType
  | provenanceType | functionType | parenthesisType
  ;
primitiveType : INT_TYPE | LONG_TYPE | FLOAT_TYPE | DOUBLE_TYPE | BOOL_TYPE
              | CHAR_TYPE | STRING_TYPE | ANY_TYPE | NEVER_TYPE ;
userDefinedType : qualifiedName genericArguments? ;
pipelineType  : PIPELINE_TYPE LT type ARROW type GT ;
listType      : LIST_TYPE LT type GT ;
mapType       : MAP_TYPE LT type COMMA type GT ;
setType       : SET_TYPE LT type GT ;
streamType    : STREAM_TYPE LT type GT ;
futureType    : FUTURE_TYPE LT type GT ;
resultType    : RESULT_TYPE LT type COMMA type GT ;
optionType    : OPTION_TYPE LT type GT ;
provenanceType: PROVENANCE_TYPE LT type GT ;
functionType  : LPAREN typeList? RPAREN ARROW type ;
parenthesisType: LPAREN type RPAREN ;

genericArguments : LT typeList GT ;
typeList : type (COMMA type)* ;
genericParameters : LT genericParameterList GT ;
genericParameterList : genericParameter (COMMA genericParameter)* ;
genericParameter : ID genericParameterConstraint* ;
genericParameterConstraint : COLON type | EQUALS type | EXTENDS type ;
whereClause : WHERE constraintList ;
constraintList : constraint (COMMA constraint)* ;
constraint : ID COLON type | ID EQUALS type | ID EXTENDS type | expression ;
typedField : ID COLON type ;
typedFieldList : typedField (COMMA typedField)* ;
typedParameter : ID COLON type ;
typedParameterList : typedParameter (COMMA typedParameter)* ;

functionalExpression
  : mapExpression | filterExpression | reduceExpression | foreachExpression
  | groupByExpression | flatMapExpression | zipExpression | partitionExpression
  | takeExpression | dropExpression | takeWhileExpression | dropWhileExpression
  | sortByExpression | distinctExpression | countExpression | findExpression
  | anyExpression | allExpression | joinExpression | windowExpression
  | chunkExpression | scanExpression | collectExpression
  ;
mapExpression       : MAP       LPAREN (lambdaExpression|expression) COMMA expression RPAREN ;
filterExpression    : FILTER    LPAREN expression COMMA (lambdaExpression|expression) RPAREN ;
reduceExpression    : REDUCE    LPAREN expression COMMA (lambdaExpression|expression) (COMMA expression)? RPAREN ;
foreachExpression   : FOREACH   LPAREN expression COMMA (lambdaExpression|expression) RPAREN ;
groupByExpression   : GROUP_BY  LPAREN expression COMMA (lambdaExpression|expression) RPAREN ;
flatMapExpression   : FLATMAP   LPAREN expression COMMA (lambdaExpression|expression) RPAREN ;
zipExpression       : ZIP       LPAREN expression COMMA expression (COMMA lambdaExpression)? RPAREN ;
partitionExpression : PARTITION LPAREN expression COMMA (lambdaExpression|expression) RPAREN ;
takeExpression      : TAKE      LPAREN expression COMMA expression RPAREN ;
dropExpression      : DROP      LPAREN expression COMMA expression RPAREN ;
takeWhileExpression : TAKE_WHILE LPAREN expression COMMA (lambdaExpression|expression) RPAREN ;
dropWhileExpression : DROP_WHILE LPAREN expression COMMA (lambdaExpression|expression) RPAREN ;
sortByExpression    : SORT_BY   LPAREN expression COMMA (lambdaExpression|expression) RPAREN ;
distinctExpression  : DISTINCT  LPAREN expression (COMMA (lambdaExpression|expression))? RPAREN ;
countExpression     : COUNT     LPAREN expression (COMMA (lambdaExpression|expression))? RPAREN ;
findExpression      : FIND      LPAREN expression COMMA (lambdaExpression|expression) RPAREN ;
anyExpression       : ANY       LPAREN expression COMMA (lambdaExpression|expression) RPAREN ;
allExpression       : ALL       LPAREN expression COMMA (lambdaExpression|expression) RPAREN ;
joinExpression      : JOIN      LPAREN expression COMMA expression COMMA joinClause (COMMA expression)? RPAREN ;
joinClause          : ON EQUALS (lambdaExpression|expression) ;
windowExpression    : WINDOW    LPAREN expression COMMA expression (COMMA expression)? RPAREN ;
chunkExpression     : CHUNK     LPAREN expression COMMA expression RPAREN ;
scanExpression      : SCAN      LPAREN expression COMMA (lambdaExpression|expression) (COMMA expression)? RPAREN ;
collectExpression   : COLLECT   LPAREN expression COMMA (lambdaExpression|expression) COMMA expression RPAREN ;

lambdaExpression : multipleParameterLambda | simplePatternLambda | simpleLambda ;
multipleParameterLambda : LPAREN parameterList RPAREN LAMBDA_ARROW (expression|blockExpression) ;
parameterList : parameter (COMMA parameter)* ;
parameter : ID (COLON type)? ;
simplePatternLambda : simpleDestructure LAMBDA_ARROW (expression|blockExpression) ;
simpleDestructure : LCURLY simplePatternFieldList RCURLY | LBRACK simplePatternList RBRACK ;
simpleLambda : ID LAMBDA_ARROW (expression|blockExpression) ;
simplePatternList : simplePatternElement (COMMA simplePatternElement)* ;
simplePatternFieldList : simplePatternField (COMMA simplePatternField)* ;
simplePatternElement : ID | WILDCARD ;
simplePatternField : ID | ID COLON ID | WILDCARD ;
blockExpression : LCURLY transformationList RCURLY ;
transformationList : transformation (SEMI transformation)* SEMI? ;
transformation : LET ID (COLON type)? EQUALS expression | expression ;

matchExpression : MATCH expression LCURLY matchArmList RCURLY ;
matchArm : pattern ARROW (expression|blockExpression) ;
matchArmList : matchArm (COMMA matchArm)* COMMA? ;
pattern : orPattern ;
orPattern : andPattern (UNION_PIPE andPattern)* ;
andPattern : primaryPattern ;
primaryPattern
  : wildcardPattern | literalPattern | identifierPattern | destructurePattern
  | rangePattern | typePattern | guardPattern | parenthesisPattern
  ;
wildcardPattern    : WILDCARD ;
literalPattern     : literalValue ;
identifierPattern  : ID ;
destructurePattern : objectDestructure | listDestructure | tupleDestructure | namedDestructure ;
objectDestructure  : LCURLY patternFieldList? RCURLY ;
listDestructure    : LBRACK patternList? RBRACK ;
tupleDestructure   : LPAREN patternList RPAREN ;
namedDestructure   : qualifiedName LCURLY patternFieldList? RCURLY ;
rangePattern       : simpleRangeValue (RANGE_OP|INCLUSIVE_RANGE) simpleRangeValue ;
simpleRangeValue   : literalValue | ID | qualifiedName ;
typePattern        : simplePattern COLON type ;
simplePattern      : wildcardPattern | literalPattern | identifierPattern | parenthesisPattern ;
guardPattern       : simplePattern WHEN simpleCondition ;
simpleCondition    : ID (EQ|NEQ|LT|GT|LE|GE) literalValue | literalValue ;
parenthesisPattern : LPAREN pattern RPAREN ;
patternField       : ID COLON pattern | ID | WILDCARD ;
patternFieldList   : patternField (COMMA patternField)* COMMA? ;
patternList        : pattern (COMMA pattern)* COMMA? ;

mutationExpression : postfixExpression MUTATE_AT mutationSite mutationChange ;
mutationSite : INT_LITERAL | ID LPAREN INT_LITERAL RPAREN | rangeExpression ;
mutationChange : ID BIO_TRANSFORM ID | expression BIO_TRANSFORM expression ;
rangeExpression : expression RANGE_OP expression | expression INCLUSIVE_RANGE expression | expression EXCLUSIVE_RANGE expression ;

listExpression : LBRACK expressionList? RBRACK ;
objectExpression : LCURLY objectFieldList? RCURLY ;
objectField : (ID|STRING) COLON expression ;
objectFieldList : objectField (COMMA objectField)* COMMA? ;

assignmentStatement : qualifiedName EQUALS expression SEMI ;
annotationPairList : annotationPair (COMMA annotationPair)* ;
annotationPair : ID COLON annotationValue ;
annotationValue : literalValue | listLiteral ;
listLiteral : LBRACK annotationValueList? RBRACK ;
annotationValueList : annotationValue (COMMA annotationValue)* ;

qualifiedName : ID (DOT ID)* ;
literalValue : BOOLEAN | INT_LITERAL | DECIMAL_LITERAL | STRING | RAW_STRING | MULTILINE_STRING | NULL ;
expressionList : expression (COMMA expression)* ;
idList : ID (COMMA ID)* ;
argument : ID EQUALS expression | lambdaArgumentRule | expression ;
lambdaArgumentRule
  : ID LAMBDA_ARROW (expression|blockExpression)
  | LPAREN parameterList RPAREN LAMBDA_ARROW (expression|blockExpression)
  | simpleDestructure LAMBDA_ARROW (expression|blockExpression)
  ;
argumentList : argument (COMMA argument)* ;
