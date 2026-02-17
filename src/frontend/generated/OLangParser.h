
// Generated from /home/scott/Projects/olang/grammar/OLangParser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"




class  OLangParser : public antlr4::Parser {
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
    WS = 131, OPTIONAL = 132
  };

  enum {
    RuleProgram = 0, RuleStatementList = 1, RuleStatement = 2, RuleExpressionStatement = 3, 
    RuleEmitStatement = 4, RuleSignalStatement = 5, RuleAssertStatement = 6, 
    RuleDeclaration = 7, RuleAgentDeclaration = 8, RuleAgentMember = 9, 
    RuleSolverDeclaration = 10, RuleSolverMember = 11, RuleProofDeclaration = 12, 
    RuleInvariantDeclaration = 13, RuleImportDeclaration = 14, RuleDottedAsNamesList = 15, 
    RuleDottedAsNames = 16, RuleRelativeModule = 17, RuleImportTargets = 18, 
    RuleImportAsNames = 19, RuleBindingDeclaration = 20, RuleFunctionDeclaration = 21, 
    RulePipelineDeclaration = 22, RuleTypeDeclaration = 23, RuleAnnotationTypeDeclaration = 24, 
    RuleAnnotationStatement = 25, RuleExpression = 26, RulePipelineExpression = 27, 
    RulePipelineBody = 28, RuleNullCoalesceExpression = 29, RuleTernaryExpression = 30, 
    RuleLogicalOrExpression = 31, RuleLogicalAndExpression = 32, RuleEqualityExpression = 33, 
    RuleRelationalExpression = 34, RuleAdditiveExpression = 35, RuleMultiplicativeExpression = 36, 
    RuleUnaryExpression = 37, RuleErrorPropagationExpression = 38, RulePostfixExpression = 39, 
    RuleCallSuffix = 40, RuleCallArguments = 41, RulePrimaryExpression = 42, 
    RuleType = 43, RuleOptionalType = 44, RuleBaseType = 45, RulePrimitiveType = 46, 
    RuleUserDefinedType = 47, RulePipelineType = 48, RuleListType = 49, 
    RuleMapType = 50, RuleSetType = 51, RuleStreamType = 52, RuleFutureType = 53, 
    RuleResultType = 54, RuleOptionType = 55, RuleProvenanceType = 56, RuleFunctionType = 57, 
    RuleParenthesisType = 58, RuleGenericArguments = 59, RuleTypeList = 60, 
    RuleGenericParameters = 61, RuleGenericParameterList = 62, RuleGenericParameter = 63, 
    RuleGenericParameterConstraint = 64, RuleWhereClause = 65, RuleConstraintList = 66, 
    RuleConstraint = 67, RuleTypedField = 68, RuleTypedFieldList = 69, RuleTypedParameter = 70, 
    RuleTypedParameterList = 71, RuleFunctionalExpression = 72, RuleMapExpression = 73, 
    RuleFilterExpression = 74, RuleReduceExpression = 75, RuleForeachExpression = 76, 
    RuleGroupByExpression = 77, RuleFlatMapExpression = 78, RuleZipExpression = 79, 
    RulePartitionExpression = 80, RuleTakeExpression = 81, RuleDropExpression = 82, 
    RuleTakeWhileExpression = 83, RuleDropWhileExpression = 84, RuleSortByExpression = 85, 
    RuleDistinctExpression = 86, RuleCountExpression = 87, RuleFindExpression = 88, 
    RuleAnyExpression = 89, RuleAllExpression = 90, RuleJoinExpression = 91, 
    RuleJoinClause = 92, RuleWindowExpression = 93, RuleChunkExpression = 94, 
    RuleScanExpression = 95, RuleCollectExpression = 96, RuleLambdaExpression = 97, 
    RuleMultipleParameterLambda = 98, RuleParameterList = 99, RuleParameter = 100, 
    RuleSimplePatternLambda = 101, RuleSimpleDestructure = 102, RuleSimpleLambda = 103, 
    RuleSimplePatternList = 104, RuleSimplePatternFieldList = 105, RuleSimplePatternElement = 106, 
    RuleSimplePatternField = 107, RuleBlockExpression = 108, RuleTransformationList = 109, 
    RuleTransformation = 110, RuleMatchExpression = 111, RuleMatchArm = 112, 
    RuleMatchArmList = 113, RulePattern = 114, RuleOrPattern = 115, RuleAndPattern = 116, 
    RulePrimaryPattern = 117, RuleWildcardPattern = 118, RuleLiteralPattern = 119, 
    RuleIdentifierPattern = 120, RuleDestructurePattern = 121, RuleObjectDestructure = 122, 
    RuleListDestructure = 123, RuleTupleDestructure = 124, RuleNamedDestructure = 125, 
    RuleRangePattern = 126, RuleSimpleRangeValue = 127, RuleTypePattern = 128, 
    RuleSimplePattern = 129, RuleGuardPattern = 130, RuleSimpleCondition = 131, 
    RuleParenthesisPattern = 132, RulePatternField = 133, RulePatternFieldList = 134, 
    RulePatternList = 135, RuleMutationExpression = 136, RuleMutationSite = 137, 
    RuleMutationChange = 138, RuleRangeExpression = 139, RuleListExpression = 140, 
    RuleObjectExpression = 141, RuleObjectField = 142, RuleObjectFieldList = 143, 
    RuleAssignmentStatement = 144, RuleAnnotationPairList = 145, RuleAnnotationPair = 146, 
    RuleAnnotationValue = 147, RuleListLiteral = 148, RuleAnnotationValueList = 149, 
    RuleQualifiedName = 150, RuleLiteralValue = 151, RuleExpressionList = 152, 
    RuleIdList = 153, RuleArgument = 154, RuleLambdaArgumentRule = 155, 
    RuleArgumentList = 156
  };

  explicit OLangParser(antlr4::TokenStream *input);

  OLangParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~OLangParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ProgramContext;
  class StatementListContext;
  class StatementContext;
  class ExpressionStatementContext;
  class EmitStatementContext;
  class SignalStatementContext;
  class AssertStatementContext;
  class DeclarationContext;
  class AgentDeclarationContext;
  class AgentMemberContext;
  class SolverDeclarationContext;
  class SolverMemberContext;
  class ProofDeclarationContext;
  class InvariantDeclarationContext;
  class ImportDeclarationContext;
  class DottedAsNamesListContext;
  class DottedAsNamesContext;
  class RelativeModuleContext;
  class ImportTargetsContext;
  class ImportAsNamesContext;
  class BindingDeclarationContext;
  class FunctionDeclarationContext;
  class PipelineDeclarationContext;
  class TypeDeclarationContext;
  class AnnotationTypeDeclarationContext;
  class AnnotationStatementContext;
  class ExpressionContext;
  class PipelineExpressionContext;
  class PipelineBodyContext;
  class NullCoalesceExpressionContext;
  class TernaryExpressionContext;
  class LogicalOrExpressionContext;
  class LogicalAndExpressionContext;
  class EqualityExpressionContext;
  class RelationalExpressionContext;
  class AdditiveExpressionContext;
  class MultiplicativeExpressionContext;
  class UnaryExpressionContext;
  class ErrorPropagationExpressionContext;
  class PostfixExpressionContext;
  class CallSuffixContext;
  class CallArgumentsContext;
  class PrimaryExpressionContext;
  class TypeContext;
  class OptionalTypeContext;
  class BaseTypeContext;
  class PrimitiveTypeContext;
  class UserDefinedTypeContext;
  class PipelineTypeContext;
  class ListTypeContext;
  class MapTypeContext;
  class SetTypeContext;
  class StreamTypeContext;
  class FutureTypeContext;
  class ResultTypeContext;
  class OptionTypeContext;
  class ProvenanceTypeContext;
  class FunctionTypeContext;
  class ParenthesisTypeContext;
  class GenericArgumentsContext;
  class TypeListContext;
  class GenericParametersContext;
  class GenericParameterListContext;
  class GenericParameterContext;
  class GenericParameterConstraintContext;
  class WhereClauseContext;
  class ConstraintListContext;
  class ConstraintContext;
  class TypedFieldContext;
  class TypedFieldListContext;
  class TypedParameterContext;
  class TypedParameterListContext;
  class FunctionalExpressionContext;
  class MapExpressionContext;
  class FilterExpressionContext;
  class ReduceExpressionContext;
  class ForeachExpressionContext;
  class GroupByExpressionContext;
  class FlatMapExpressionContext;
  class ZipExpressionContext;
  class PartitionExpressionContext;
  class TakeExpressionContext;
  class DropExpressionContext;
  class TakeWhileExpressionContext;
  class DropWhileExpressionContext;
  class SortByExpressionContext;
  class DistinctExpressionContext;
  class CountExpressionContext;
  class FindExpressionContext;
  class AnyExpressionContext;
  class AllExpressionContext;
  class JoinExpressionContext;
  class JoinClauseContext;
  class WindowExpressionContext;
  class ChunkExpressionContext;
  class ScanExpressionContext;
  class CollectExpressionContext;
  class LambdaExpressionContext;
  class MultipleParameterLambdaContext;
  class ParameterListContext;
  class ParameterContext;
  class SimplePatternLambdaContext;
  class SimpleDestructureContext;
  class SimpleLambdaContext;
  class SimplePatternListContext;
  class SimplePatternFieldListContext;
  class SimplePatternElementContext;
  class SimplePatternFieldContext;
  class BlockExpressionContext;
  class TransformationListContext;
  class TransformationContext;
  class MatchExpressionContext;
  class MatchArmContext;
  class MatchArmListContext;
  class PatternContext;
  class OrPatternContext;
  class AndPatternContext;
  class PrimaryPatternContext;
  class WildcardPatternContext;
  class LiteralPatternContext;
  class IdentifierPatternContext;
  class DestructurePatternContext;
  class ObjectDestructureContext;
  class ListDestructureContext;
  class TupleDestructureContext;
  class NamedDestructureContext;
  class RangePatternContext;
  class SimpleRangeValueContext;
  class TypePatternContext;
  class SimplePatternContext;
  class GuardPatternContext;
  class SimpleConditionContext;
  class ParenthesisPatternContext;
  class PatternFieldContext;
  class PatternFieldListContext;
  class PatternListContext;
  class MutationExpressionContext;
  class MutationSiteContext;
  class MutationChangeContext;
  class RangeExpressionContext;
  class ListExpressionContext;
  class ObjectExpressionContext;
  class ObjectFieldContext;
  class ObjectFieldListContext;
  class AssignmentStatementContext;
  class AnnotationPairListContext;
  class AnnotationPairContext;
  class AnnotationValueContext;
  class ListLiteralContext;
  class AnnotationValueListContext;
  class QualifiedNameContext;
  class LiteralValueContext;
  class ExpressionListContext;
  class IdListContext;
  class ArgumentContext;
  class LambdaArgumentRuleContext;
  class ArgumentListContext; 

  class  ProgramContext : public antlr4::ParserRuleContext {
  public:
    ProgramContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatementListContext *statementList();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProgramContext* program();

  class  StatementListContext : public antlr4::ParserRuleContext {
  public:
    StatementListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<StatementContext *> statement();
    StatementContext* statement(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMI();
    antlr4::tree::TerminalNode* SEMI(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementListContext* statementList();

  class  StatementContext : public antlr4::ParserRuleContext {
  public:
    StatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    DeclarationContext *declaration();
    AssignmentStatementContext *assignmentStatement();
    AnnotationStatementContext *annotationStatement();
    ExpressionStatementContext *expressionStatement();
    EmitStatementContext *emitStatement();
    SignalStatementContext *signalStatement();
    AssertStatementContext *assertStatement();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatementContext* statement();

  class  ExpressionStatementContext : public antlr4::ParserRuleContext {
  public:
    ExpressionStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMI();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionStatementContext* expressionStatement();

  class  EmitStatementContext : public antlr4::ParserRuleContext {
  public:
    EmitStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *EMIT();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMI();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EmitStatementContext* emitStatement();

  class  SignalStatementContext : public antlr4::ParserRuleContext {
  public:
    SignalStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SIGNAL();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMI();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SignalStatementContext* signalStatement();

  class  AssertStatementContext : public antlr4::ParserRuleContext {
  public:
    AssertStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ASSERT();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *SEMI();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssertStatementContext* assertStatement();

  class  DeclarationContext : public antlr4::ParserRuleContext {
  public:
    DeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ImportDeclarationContext *importDeclaration();
    BindingDeclarationContext *bindingDeclaration();
    FunctionDeclarationContext *functionDeclaration();
    PipelineDeclarationContext *pipelineDeclaration();
    AnnotationTypeDeclarationContext *annotationTypeDeclaration();
    TypeDeclarationContext *typeDeclaration();
    AgentDeclarationContext *agentDeclaration();
    SolverDeclarationContext *solverDeclaration();
    ProofDeclarationContext *proofDeclaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DeclarationContext* declaration();

  class  AgentDeclarationContext : public antlr4::ParserRuleContext {
  public:
    AgentDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AGENT();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    std::vector<AgentMemberContext *> agentMember();
    AgentMemberContext* agentMember(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AgentDeclarationContext* agentDeclaration();

  class  AgentMemberContext : public antlr4::ParserRuleContext {
  public:
    AgentMemberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CAPABILITY();
    IdListContext *idList();
    antlr4::tree::TerminalNode *SEMI();
    antlr4::tree::TerminalNode *STREAM();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    antlr4::tree::TerminalNode *RULE();
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *WHEN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ARROW();
    BlockExpressionContext *blockExpression();
    antlr4::tree::TerminalNode *RCURLY();
    antlr4::tree::TerminalNode *STRING();
    DeclarationContext *declaration();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AgentMemberContext* agentMember();

  class  SolverDeclarationContext : public antlr4::ParserRuleContext {
  public:
    SolverDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SOLVER();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    std::vector<SolverMemberContext *> solverMember();
    SolverMemberContext* solverMember(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SolverDeclarationContext* solverDeclaration();

  class  SolverMemberContext : public antlr4::ParserRuleContext {
  public:
    SolverMemberContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *VARIABLE();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    antlr4::tree::TerminalNode *SEMI();
    antlr4::tree::TerminalNode *IN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SATISFY();
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    std::vector<ExpressionStatementContext *> expressionStatement();
    ExpressionStatementContext* expressionStatement(size_t i);
    antlr4::tree::TerminalNode *MINIMIZE();
    antlr4::tree::TerminalNode *MAXIMIZE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SolverMemberContext* solverMember();

  class  ProofDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ProofDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PROOF();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    std::vector<InvariantDeclarationContext *> invariantDeclaration();
    InvariantDeclarationContext* invariantDeclaration(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProofDeclarationContext* proofDeclaration();

  class  InvariantDeclarationContext : public antlr4::ParserRuleContext {
  public:
    InvariantDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INVARIANT();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    std::vector<ExpressionStatementContext *> expressionStatement();
    ExpressionStatementContext* expressionStatement(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  InvariantDeclarationContext* invariantDeclaration();

  class  ImportDeclarationContext : public antlr4::ParserRuleContext {
  public:
    ImportDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IMPORT();
    DottedAsNamesListContext *dottedAsNamesList();
    antlr4::tree::TerminalNode *SEMI();
    antlr4::tree::TerminalNode *FROM();
    RelativeModuleContext *relativeModule();
    ImportTargetsContext *importTargets();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportDeclarationContext* importDeclaration();

  class  DottedAsNamesListContext : public antlr4::ParserRuleContext {
  public:
    DottedAsNamesListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<DottedAsNamesContext *> dottedAsNames();
    DottedAsNamesContext* dottedAsNames(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DottedAsNamesListContext* dottedAsNamesList();

  class  DottedAsNamesContext : public antlr4::ParserRuleContext {
  public:
    DottedAsNamesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QualifiedNameContext *qualifiedName();
    antlr4::tree::TerminalNode *AS();
    antlr4::tree::TerminalNode *ID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DottedAsNamesContext* dottedAsNames();

  class  RelativeModuleContext : public antlr4::ParserRuleContext {
  public:
    RelativeModuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QualifiedNameContext *qualifiedName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RelativeModuleContext* relativeModule();

  class  ImportTargetsContext : public antlr4::ParserRuleContext {
  public:
    ImportTargetsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ImportAsNamesContext *> importAsNames();
    ImportAsNamesContext* importAsNames(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *MUL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportTargetsContext* importTargets();

  class  ImportAsNamesContext : public antlr4::ParserRuleContext {
  public:
    ImportAsNamesContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *AS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ImportAsNamesContext* importAsNames();

  class  BindingDeclarationContext : public antlr4::ParserRuleContext {
  public:
    BindingDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *EQUALS();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BindingDeclarationContext* bindingDeclaration();

  class  FunctionDeclarationContext : public antlr4::ParserRuleContext {
  public:
    FunctionDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DEF();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *ARROW();
    TypeContext *type();
    antlr4::tree::TerminalNode *EQUALS();
    ExpressionContext *expression();
    TypedParameterListContext *typedParameterList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionDeclarationContext* functionDeclaration();

  class  PipelineDeclarationContext : public antlr4::ParserRuleContext {
  public:
    PipelineDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *PIPELINE_TYPE();
    antlr4::tree::TerminalNode *LT();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    antlr4::tree::TerminalNode *ARROW();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *EQUALS();
    PipelineBodyContext *pipelineBody();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PipelineDeclarationContext* pipelineDeclaration();

  class  TypeDeclarationContext : public antlr4::ParserRuleContext {
  public:
    TypeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TYPE();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LCURLY();
    TypedFieldListContext *typedFieldList();
    antlr4::tree::TerminalNode *RCURLY();
    GenericParametersContext *genericParameters();
    WhereClauseContext *whereClause();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeDeclarationContext* typeDeclaration();

  class  AnnotationTypeDeclarationContext : public antlr4::ParserRuleContext {
  public:
    AnnotationTypeDeclarationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATION();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LCURLY();
    TypedFieldListContext *typedFieldList();
    antlr4::tree::TerminalNode *RCURLY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationTypeDeclarationContext* annotationTypeDeclaration();

  class  AnnotationStatementContext : public antlr4::ParserRuleContext {
  public:
    AnnotationStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANNOTATED();
    DeclarationContext *declaration();
    antlr4::tree::TerminalNode *WITH();
    antlr4::tree::TerminalNode *LCURLY();
    AnnotationPairListContext *annotationPairList();
    antlr4::tree::TerminalNode *RCURLY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationStatementContext* annotationStatement();

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LambdaExpressionContext *lambdaExpression();
    FunctionalExpressionContext *functionalExpression();
    PipelineExpressionContext *pipelineExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  PipelineExpressionContext : public antlr4::ParserRuleContext {
  public:
    PipelineExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<NullCoalesceExpressionContext *> nullCoalesceExpression();
    NullCoalesceExpressionContext* nullCoalesceExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PIPELINE_OP();
    antlr4::tree::TerminalNode* PIPELINE_OP(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PARALLEL_OP();
    antlr4::tree::TerminalNode* PARALLEL_OP(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PipelineExpressionContext* pipelineExpression();

  class  PipelineBodyContext : public antlr4::ParserRuleContext {
  public:
    PipelineBodyContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PIPELINE_OP();
    antlr4::tree::TerminalNode* PIPELINE_OP(size_t i);
    std::vector<antlr4::tree::TerminalNode *> PARALLEL_OP();
    antlr4::tree::TerminalNode* PARALLEL_OP(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PipelineBodyContext* pipelineBody();

  class  NullCoalesceExpressionContext : public antlr4::ParserRuleContext {
  public:
    NullCoalesceExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TernaryExpressionContext *> ternaryExpression();
    TernaryExpressionContext* ternaryExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NULL_COALESCE();
    antlr4::tree::TerminalNode* NULL_COALESCE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NullCoalesceExpressionContext* nullCoalesceExpression();

  class  TernaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    TernaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LogicalOrExpressionContext *logicalOrExpression();
    antlr4::tree::TerminalNode *OPTIONAL();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *COLON();
    TernaryExpressionContext *ternaryExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TernaryExpressionContext* ternaryExpression();

  class  LogicalOrExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalOrExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<LogicalAndExpressionContext *> logicalAndExpression();
    LogicalAndExpressionContext* logicalAndExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR_OP();
    antlr4::tree::TerminalNode* OR_OP(size_t i);
    std::vector<antlr4::tree::TerminalNode *> OR();
    antlr4::tree::TerminalNode* OR(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicalOrExpressionContext* logicalOrExpression();

  class  LogicalAndExpressionContext : public antlr4::ParserRuleContext {
  public:
    LogicalAndExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<EqualityExpressionContext *> equalityExpression();
    EqualityExpressionContext* equalityExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> AND_OP();
    antlr4::tree::TerminalNode* AND_OP(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LogicalAndExpressionContext* logicalAndExpression();

  class  EqualityExpressionContext : public antlr4::ParserRuleContext {
  public:
    EqualityExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<RelationalExpressionContext *> relationalExpression();
    RelationalExpressionContext* relationalExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> EQ();
    antlr4::tree::TerminalNode* EQ(size_t i);
    std::vector<antlr4::tree::TerminalNode *> NEQ();
    antlr4::tree::TerminalNode* NEQ(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  EqualityExpressionContext* equalityExpression();

  class  RelationalExpressionContext : public antlr4::ParserRuleContext {
  public:
    RelationalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AdditiveExpressionContext *> additiveExpression();
    AdditiveExpressionContext* additiveExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LE();
    antlr4::tree::TerminalNode* LE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> LT();
    antlr4::tree::TerminalNode* LT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GE();
    antlr4::tree::TerminalNode* GE(size_t i);
    std::vector<antlr4::tree::TerminalNode *> GT();
    antlr4::tree::TerminalNode* GT(size_t i);
    std::vector<antlr4::tree::TerminalNode *> WITHIN();
    antlr4::tree::TerminalNode* WITHIN(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DURING();
    antlr4::tree::TerminalNode* DURING(size_t i);
    std::vector<antlr4::tree::TerminalNode *> UNTIL();
    antlr4::tree::TerminalNode* UNTIL(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RelationalExpressionContext* relationalExpression();

  class  AdditiveExpressionContext : public antlr4::ParserRuleContext {
  public:
    AdditiveExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MultiplicativeExpressionContext *> multiplicativeExpression();
    MultiplicativeExpressionContext* multiplicativeExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> ADD();
    antlr4::tree::TerminalNode* ADD(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SUB();
    antlr4::tree::TerminalNode* SUB(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AdditiveExpressionContext* additiveExpression();

  class  MultiplicativeExpressionContext : public antlr4::ParserRuleContext {
  public:
    MultiplicativeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<UnaryExpressionContext *> unaryExpression();
    UnaryExpressionContext* unaryExpression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MUL();
    antlr4::tree::TerminalNode* MUL(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DIV();
    antlr4::tree::TerminalNode* DIV(size_t i);
    std::vector<antlr4::tree::TerminalNode *> MOD();
    antlr4::tree::TerminalNode* MOD(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultiplicativeExpressionContext* multiplicativeExpression();

  class  UnaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    UnaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    UnaryExpressionContext *unaryExpression();
    antlr4::tree::TerminalNode *NOT();
    antlr4::tree::TerminalNode *SUB();
    antlr4::tree::TerminalNode *ADD();
    antlr4::tree::TerminalNode *ALWAYS();
    antlr4::tree::TerminalNode *EVENTUALLY();
    ErrorPropagationExpressionContext *errorPropagationExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UnaryExpressionContext* unaryExpression();

  class  ErrorPropagationExpressionContext : public antlr4::ParserRuleContext {
  public:
    ErrorPropagationExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PostfixExpressionContext *postfixExpression();
    antlr4::tree::TerminalNode *OPTIONAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ErrorPropagationExpressionContext* errorPropagationExpression();

  class  PostfixExpressionContext : public antlr4::ParserRuleContext {
  public:
    PostfixExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryExpressionContext *primaryExpression();
    std::vector<CallSuffixContext *> callSuffix();
    CallSuffixContext* callSuffix(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PostfixExpressionContext* postfixExpression();

  class  CallSuffixContext : public antlr4::ParserRuleContext {
  public:
    CallSuffixContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    CallArgumentsContext *callArguments();
    antlr4::tree::TerminalNode *DOT();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LBRACK();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RBRACK();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CallSuffixContext* callSuffix();

  class  CallArgumentsContext : public antlr4::ParserRuleContext {
  public:
    CallArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    ArgumentListContext *argumentList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CallArgumentsContext* callArguments();

  class  PrimaryExpressionContext : public antlr4::ParserRuleContext {
  public:
    PrimaryExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralValueContext *literalValue();
    LambdaExpressionContext *lambdaExpression();
    MatchExpressionContext *matchExpression();
    ListExpressionContext *listExpression();
    ObjectExpressionContext *objectExpression();
    QualifiedNameContext *qualifiedName();
    antlr4::tree::TerminalNode *LPAREN();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryExpressionContext* primaryExpression();

  class  TypeContext : public antlr4::ParserRuleContext {
  public:
    TypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<OptionalTypeContext *> optionalType();
    OptionalTypeContext* optionalType(size_t i);
    std::vector<antlr4::tree::TerminalNode *> UNION_PIPE();
    antlr4::tree::TerminalNode* UNION_PIPE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeContext* type();

  class  OptionalTypeContext : public antlr4::ParserRuleContext {
  public:
    OptionalTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    BaseTypeContext *baseType();
    antlr4::tree::TerminalNode *OPTIONAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptionalTypeContext* optionalType();

  class  BaseTypeContext : public antlr4::ParserRuleContext {
  public:
    BaseTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimitiveTypeContext *primitiveType();
    UserDefinedTypeContext *userDefinedType();
    PipelineTypeContext *pipelineType();
    ListTypeContext *listType();
    MapTypeContext *mapType();
    SetTypeContext *setType();
    StreamTypeContext *streamType();
    FutureTypeContext *futureType();
    ResultTypeContext *resultType();
    OptionTypeContext *optionType();
    ProvenanceTypeContext *provenanceType();
    FunctionTypeContext *functionType();
    ParenthesisTypeContext *parenthesisType();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BaseTypeContext* baseType();

  class  PrimitiveTypeContext : public antlr4::ParserRuleContext {
  public:
    PrimitiveTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT_TYPE();
    antlr4::tree::TerminalNode *LONG_TYPE();
    antlr4::tree::TerminalNode *FLOAT_TYPE();
    antlr4::tree::TerminalNode *DOUBLE_TYPE();
    antlr4::tree::TerminalNode *BOOL_TYPE();
    antlr4::tree::TerminalNode *CHAR_TYPE();
    antlr4::tree::TerminalNode *STRING_TYPE();
    antlr4::tree::TerminalNode *ANY_TYPE();
    antlr4::tree::TerminalNode *NEVER_TYPE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimitiveTypeContext* primitiveType();

  class  UserDefinedTypeContext : public antlr4::ParserRuleContext {
  public:
    UserDefinedTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QualifiedNameContext *qualifiedName();
    GenericArgumentsContext *genericArguments();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  UserDefinedTypeContext* userDefinedType();

  class  PipelineTypeContext : public antlr4::ParserRuleContext {
  public:
    PipelineTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PIPELINE_TYPE();
    antlr4::tree::TerminalNode *LT();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    antlr4::tree::TerminalNode *ARROW();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PipelineTypeContext* pipelineType();

  class  ListTypeContext : public antlr4::ParserRuleContext {
  public:
    ListTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LIST_TYPE();
    antlr4::tree::TerminalNode *LT();
    TypeContext *type();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ListTypeContext* listType();

  class  MapTypeContext : public antlr4::ParserRuleContext {
  public:
    MapTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MAP_TYPE();
    antlr4::tree::TerminalNode *LT();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MapTypeContext* mapType();

  class  SetTypeContext : public antlr4::ParserRuleContext {
  public:
    SetTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SET_TYPE();
    antlr4::tree::TerminalNode *LT();
    TypeContext *type();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SetTypeContext* setType();

  class  StreamTypeContext : public antlr4::ParserRuleContext {
  public:
    StreamTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STREAM_TYPE();
    antlr4::tree::TerminalNode *LT();
    TypeContext *type();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StreamTypeContext* streamType();

  class  FutureTypeContext : public antlr4::ParserRuleContext {
  public:
    FutureTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FUTURE_TYPE();
    antlr4::tree::TerminalNode *LT();
    TypeContext *type();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FutureTypeContext* futureType();

  class  ResultTypeContext : public antlr4::ParserRuleContext {
  public:
    ResultTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *RESULT_TYPE();
    antlr4::tree::TerminalNode *LT();
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ResultTypeContext* resultType();

  class  OptionTypeContext : public antlr4::ParserRuleContext {
  public:
    OptionTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *OPTION_TYPE();
    antlr4::tree::TerminalNode *LT();
    TypeContext *type();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OptionTypeContext* optionType();

  class  ProvenanceTypeContext : public antlr4::ParserRuleContext {
  public:
    ProvenanceTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PROVENANCE_TYPE();
    antlr4::tree::TerminalNode *LT();
    TypeContext *type();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ProvenanceTypeContext* provenanceType();

  class  FunctionTypeContext : public antlr4::ParserRuleContext {
  public:
    FunctionTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *ARROW();
    TypeContext *type();
    TypeListContext *typeList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionTypeContext* functionType();

  class  ParenthesisTypeContext : public antlr4::ParserRuleContext {
  public:
    ParenthesisTypeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    TypeContext *type();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParenthesisTypeContext* parenthesisType();

  class  GenericArgumentsContext : public antlr4::ParserRuleContext {
  public:
    GenericArgumentsContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LT();
    TypeListContext *typeList();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericArgumentsContext* genericArguments();

  class  TypeListContext : public antlr4::ParserRuleContext {
  public:
    TypeListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypeContext *> type();
    TypeContext* type(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypeListContext* typeList();

  class  GenericParametersContext : public antlr4::ParserRuleContext {
  public:
    GenericParametersContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LT();
    GenericParameterListContext *genericParameterList();
    antlr4::tree::TerminalNode *GT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericParametersContext* genericParameters();

  class  GenericParameterListContext : public antlr4::ParserRuleContext {
  public:
    GenericParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<GenericParameterContext *> genericParameter();
    GenericParameterContext* genericParameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericParameterListContext* genericParameterList();

  class  GenericParameterContext : public antlr4::ParserRuleContext {
  public:
    GenericParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    std::vector<GenericParameterConstraintContext *> genericParameterConstraint();
    GenericParameterConstraintContext* genericParameterConstraint(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericParameterContext* genericParameter();

  class  GenericParameterConstraintContext : public antlr4::ParserRuleContext {
  public:
    GenericParameterConstraintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    antlr4::tree::TerminalNode *EQUALS();
    antlr4::tree::TerminalNode *EXTENDS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GenericParameterConstraintContext* genericParameterConstraint();

  class  WhereClauseContext : public antlr4::ParserRuleContext {
  public:
    WhereClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WHERE();
    ConstraintListContext *constraintList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WhereClauseContext* whereClause();

  class  ConstraintListContext : public antlr4::ParserRuleContext {
  public:
    ConstraintListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ConstraintContext *> constraint();
    ConstraintContext* constraint(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstraintListContext* constraintList();

  class  ConstraintContext : public antlr4::ParserRuleContext {
  public:
    ConstraintContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();
    antlr4::tree::TerminalNode *EQUALS();
    antlr4::tree::TerminalNode *EXTENDS();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ConstraintContext* constraint();

  class  TypedFieldContext : public antlr4::ParserRuleContext {
  public:
    TypedFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypedFieldContext* typedField();

  class  TypedFieldListContext : public antlr4::ParserRuleContext {
  public:
    TypedFieldListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypedFieldContext *> typedField();
    TypedFieldContext* typedField(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypedFieldListContext* typedFieldList();

  class  TypedParameterContext : public antlr4::ParserRuleContext {
  public:
    TypedParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypedParameterContext* typedParameter();

  class  TypedParameterListContext : public antlr4::ParserRuleContext {
  public:
    TypedParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TypedParameterContext *> typedParameter();
    TypedParameterContext* typedParameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypedParameterListContext* typedParameterList();

  class  FunctionalExpressionContext : public antlr4::ParserRuleContext {
  public:
    FunctionalExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MapExpressionContext *mapExpression();
    FilterExpressionContext *filterExpression();
    ReduceExpressionContext *reduceExpression();
    ForeachExpressionContext *foreachExpression();
    GroupByExpressionContext *groupByExpression();
    FlatMapExpressionContext *flatMapExpression();
    ZipExpressionContext *zipExpression();
    PartitionExpressionContext *partitionExpression();
    TakeExpressionContext *takeExpression();
    DropExpressionContext *dropExpression();
    TakeWhileExpressionContext *takeWhileExpression();
    DropWhileExpressionContext *dropWhileExpression();
    SortByExpressionContext *sortByExpression();
    DistinctExpressionContext *distinctExpression();
    CountExpressionContext *countExpression();
    FindExpressionContext *findExpression();
    AnyExpressionContext *anyExpression();
    AllExpressionContext *allExpression();
    JoinExpressionContext *joinExpression();
    WindowExpressionContext *windowExpression();
    ChunkExpressionContext *chunkExpression();
    ScanExpressionContext *scanExpression();
    CollectExpressionContext *collectExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionalExpressionContext* functionalExpression();

  class  MapExpressionContext : public antlr4::ParserRuleContext {
  public:
    MapExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MAP();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *COMMA();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MapExpressionContext* mapExpression();

  class  FilterExpressionContext : public antlr4::ParserRuleContext {
  public:
    FilterExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FILTER();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FilterExpressionContext* filterExpression();

  class  ReduceExpressionContext : public antlr4::ParserRuleContext {
  public:
    ReduceExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REDUCE();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ReduceExpressionContext* reduceExpression();

  class  ForeachExpressionContext : public antlr4::ParserRuleContext {
  public:
    ForeachExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FOREACH();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ForeachExpressionContext* foreachExpression();

  class  GroupByExpressionContext : public antlr4::ParserRuleContext {
  public:
    GroupByExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *GROUP_BY();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GroupByExpressionContext* groupByExpression();

  class  FlatMapExpressionContext : public antlr4::ParserRuleContext {
  public:
    FlatMapExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FLATMAP();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FlatMapExpressionContext* flatMapExpression();

  class  ZipExpressionContext : public antlr4::ParserRuleContext {
  public:
    ZipExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ZIP();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ZipExpressionContext* zipExpression();

  class  PartitionExpressionContext : public antlr4::ParserRuleContext {
  public:
    PartitionExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *PARTITION();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PartitionExpressionContext* partitionExpression();

  class  TakeExpressionContext : public antlr4::ParserRuleContext {
  public:
    TakeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TAKE();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TakeExpressionContext* takeExpression();

  class  DropExpressionContext : public antlr4::ParserRuleContext {
  public:
    DropExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DROP();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DropExpressionContext* dropExpression();

  class  TakeWhileExpressionContext : public antlr4::ParserRuleContext {
  public:
    TakeWhileExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TAKE_WHILE();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TakeWhileExpressionContext* takeWhileExpression();

  class  DropWhileExpressionContext : public antlr4::ParserRuleContext {
  public:
    DropWhileExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DROP_WHILE();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DropWhileExpressionContext* dropWhileExpression();

  class  SortByExpressionContext : public antlr4::ParserRuleContext {
  public:
    SortByExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SORT_BY();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SortByExpressionContext* sortByExpression();

  class  DistinctExpressionContext : public antlr4::ParserRuleContext {
  public:
    DistinctExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *DISTINCT();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *COMMA();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DistinctExpressionContext* distinctExpression();

  class  CountExpressionContext : public antlr4::ParserRuleContext {
  public:
    CountExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COUNT();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *COMMA();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CountExpressionContext* countExpression();

  class  FindExpressionContext : public antlr4::ParserRuleContext {
  public:
    FindExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *FIND();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FindExpressionContext* findExpression();

  class  AnyExpressionContext : public antlr4::ParserRuleContext {
  public:
    AnyExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ANY();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnyExpressionContext* anyExpression();

  class  AllExpressionContext : public antlr4::ParserRuleContext {
  public:
    AllExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ALL();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AllExpressionContext* allExpression();

  class  JoinExpressionContext : public antlr4::ParserRuleContext {
  public:
    JoinExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *JOIN();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    JoinClauseContext *joinClause();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  JoinExpressionContext* joinExpression();

  class  JoinClauseContext : public antlr4::ParserRuleContext {
  public:
    JoinClauseContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ON();
    antlr4::tree::TerminalNode *EQUALS();
    LambdaExpressionContext *lambdaExpression();
    ExpressionContext *expression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  JoinClauseContext* joinClause();

  class  WindowExpressionContext : public antlr4::ParserRuleContext {
  public:
    WindowExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WINDOW();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WindowExpressionContext* windowExpression();

  class  ChunkExpressionContext : public antlr4::ParserRuleContext {
  public:
    ChunkExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *CHUNK();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ChunkExpressionContext* chunkExpression();

  class  ScanExpressionContext : public antlr4::ParserRuleContext {
  public:
    ScanExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *SCAN();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ScanExpressionContext* scanExpression();

  class  CollectExpressionContext : public antlr4::ParserRuleContext {
  public:
    CollectExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLLECT();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    LambdaExpressionContext *lambdaExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  CollectExpressionContext* collectExpression();

  class  LambdaExpressionContext : public antlr4::ParserRuleContext {
  public:
    LambdaExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MultipleParameterLambdaContext *multipleParameterLambda();
    SimplePatternLambdaContext *simplePatternLambda();
    SimpleLambdaContext *simpleLambda();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LambdaExpressionContext* lambdaExpression();

  class  MultipleParameterLambdaContext : public antlr4::ParserRuleContext {
  public:
    MultipleParameterLambdaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *RPAREN();
    antlr4::tree::TerminalNode *LAMBDA_ARROW();
    ExpressionContext *expression();
    BlockExpressionContext *blockExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MultipleParameterLambdaContext* multipleParameterLambda();

  class  ParameterListContext : public antlr4::ParserRuleContext {
  public:
    ParameterListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ParameterContext *> parameter();
    ParameterContext* parameter(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterListContext* parameterList();

  class  ParameterContext : public antlr4::ParserRuleContext {
  public:
    ParameterContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParameterContext* parameter();

  class  SimplePatternLambdaContext : public antlr4::ParserRuleContext {
  public:
    SimplePatternLambdaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SimpleDestructureContext *simpleDestructure();
    antlr4::tree::TerminalNode *LAMBDA_ARROW();
    ExpressionContext *expression();
    BlockExpressionContext *blockExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimplePatternLambdaContext* simplePatternLambda();

  class  SimpleDestructureContext : public antlr4::ParserRuleContext {
  public:
    SimpleDestructureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LCURLY();
    SimplePatternFieldListContext *simplePatternFieldList();
    antlr4::tree::TerminalNode *RCURLY();
    antlr4::tree::TerminalNode *LBRACK();
    SimplePatternListContext *simplePatternList();
    antlr4::tree::TerminalNode *RBRACK();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleDestructureContext* simpleDestructure();

  class  SimpleLambdaContext : public antlr4::ParserRuleContext {
  public:
    SimpleLambdaContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LAMBDA_ARROW();
    ExpressionContext *expression();
    BlockExpressionContext *blockExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleLambdaContext* simpleLambda();

  class  SimplePatternListContext : public antlr4::ParserRuleContext {
  public:
    SimplePatternListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SimplePatternElementContext *> simplePatternElement();
    SimplePatternElementContext* simplePatternElement(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimplePatternListContext* simplePatternList();

  class  SimplePatternFieldListContext : public antlr4::ParserRuleContext {
  public:
    SimplePatternFieldListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SimplePatternFieldContext *> simplePatternField();
    SimplePatternFieldContext* simplePatternField(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimplePatternFieldListContext* simplePatternFieldList();

  class  SimplePatternElementContext : public antlr4::ParserRuleContext {
  public:
    SimplePatternElementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *WILDCARD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimplePatternElementContext* simplePatternElement();

  class  SimplePatternFieldContext : public antlr4::ParserRuleContext {
  public:
    SimplePatternFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *COLON();
    antlr4::tree::TerminalNode *WILDCARD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimplePatternFieldContext* simplePatternField();

  class  BlockExpressionContext : public antlr4::ParserRuleContext {
  public:
    BlockExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LCURLY();
    TransformationListContext *transformationList();
    antlr4::tree::TerminalNode *RCURLY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BlockExpressionContext* blockExpression();

  class  TransformationListContext : public antlr4::ParserRuleContext {
  public:
    TransformationListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<TransformationContext *> transformation();
    TransformationContext* transformation(size_t i);
    std::vector<antlr4::tree::TerminalNode *> SEMI();
    antlr4::tree::TerminalNode* SEMI(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TransformationListContext* transformationList();

  class  TransformationContext : public antlr4::ParserRuleContext {
  public:
    TransformationContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LET();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *EQUALS();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TransformationContext* transformation();

  class  MatchExpressionContext : public antlr4::ParserRuleContext {
  public:
    MatchExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *MATCH();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *LCURLY();
    MatchArmListContext *matchArmList();
    antlr4::tree::TerminalNode *RCURLY();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchExpressionContext* matchExpression();

  class  MatchArmContext : public antlr4::ParserRuleContext {
  public:
    MatchArmContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PatternContext *pattern();
    antlr4::tree::TerminalNode *ARROW();
    ExpressionContext *expression();
    BlockExpressionContext *blockExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchArmContext* matchArm();

  class  MatchArmListContext : public antlr4::ParserRuleContext {
  public:
    MatchArmListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<MatchArmContext *> matchArm();
    MatchArmContext* matchArm(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MatchArmListContext* matchArmList();

  class  PatternContext : public antlr4::ParserRuleContext {
  public:
    PatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    OrPatternContext *orPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PatternContext* pattern();

  class  OrPatternContext : public antlr4::ParserRuleContext {
  public:
    OrPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AndPatternContext *> andPattern();
    AndPatternContext* andPattern(size_t i);
    std::vector<antlr4::tree::TerminalNode *> UNION_PIPE();
    antlr4::tree::TerminalNode* UNION_PIPE(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  OrPatternContext* orPattern();

  class  AndPatternContext : public antlr4::ParserRuleContext {
  public:
    AndPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PrimaryPatternContext *primaryPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AndPatternContext* andPattern();

  class  PrimaryPatternContext : public antlr4::ParserRuleContext {
  public:
    PrimaryPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    WildcardPatternContext *wildcardPattern();
    LiteralPatternContext *literalPattern();
    IdentifierPatternContext *identifierPattern();
    DestructurePatternContext *destructurePattern();
    RangePatternContext *rangePattern();
    TypePatternContext *typePattern();
    GuardPatternContext *guardPattern();
    ParenthesisPatternContext *parenthesisPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PrimaryPatternContext* primaryPattern();

  class  WildcardPatternContext : public antlr4::ParserRuleContext {
  public:
    WildcardPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *WILDCARD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  WildcardPatternContext* wildcardPattern();

  class  LiteralPatternContext : public antlr4::ParserRuleContext {
  public:
    LiteralPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralValueContext *literalValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralPatternContext* literalPattern();

  class  IdentifierPatternContext : public antlr4::ParserRuleContext {
  public:
    IdentifierPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierPatternContext* identifierPattern();

  class  DestructurePatternContext : public antlr4::ParserRuleContext {
  public:
    DestructurePatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ObjectDestructureContext *objectDestructure();
    ListDestructureContext *listDestructure();
    TupleDestructureContext *tupleDestructure();
    NamedDestructureContext *namedDestructure();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  DestructurePatternContext* destructurePattern();

  class  ObjectDestructureContext : public antlr4::ParserRuleContext {
  public:
    ObjectDestructureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    PatternFieldListContext *patternFieldList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ObjectDestructureContext* objectDestructure();

  class  ListDestructureContext : public antlr4::ParserRuleContext {
  public:
    ListDestructureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACK();
    antlr4::tree::TerminalNode *RBRACK();
    PatternListContext *patternList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ListDestructureContext* listDestructure();

  class  TupleDestructureContext : public antlr4::ParserRuleContext {
  public:
    TupleDestructureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    PatternListContext *patternList();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TupleDestructureContext* tupleDestructure();

  class  NamedDestructureContext : public antlr4::ParserRuleContext {
  public:
    NamedDestructureContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QualifiedNameContext *qualifiedName();
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    PatternFieldListContext *patternFieldList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NamedDestructureContext* namedDestructure();

  class  RangePatternContext : public antlr4::ParserRuleContext {
  public:
    RangePatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<SimpleRangeValueContext *> simpleRangeValue();
    SimpleRangeValueContext* simpleRangeValue(size_t i);
    antlr4::tree::TerminalNode *RANGE_OP();
    antlr4::tree::TerminalNode *INCLUSIVE_RANGE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RangePatternContext* rangePattern();

  class  SimpleRangeValueContext : public antlr4::ParserRuleContext {
  public:
    SimpleRangeValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralValueContext *literalValue();
    antlr4::tree::TerminalNode *ID();
    QualifiedNameContext *qualifiedName();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleRangeValueContext* simpleRangeValue();

  class  TypePatternContext : public antlr4::ParserRuleContext {
  public:
    TypePatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SimplePatternContext *simplePattern();
    antlr4::tree::TerminalNode *COLON();
    TypeContext *type();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TypePatternContext* typePattern();

  class  SimplePatternContext : public antlr4::ParserRuleContext {
  public:
    SimplePatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    WildcardPatternContext *wildcardPattern();
    LiteralPatternContext *literalPattern();
    IdentifierPatternContext *identifierPattern();
    ParenthesisPatternContext *parenthesisPattern();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimplePatternContext* simplePattern();

  class  GuardPatternContext : public antlr4::ParserRuleContext {
  public:
    GuardPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    SimplePatternContext *simplePattern();
    antlr4::tree::TerminalNode *WHEN();
    SimpleConditionContext *simpleCondition();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  GuardPatternContext* guardPattern();

  class  SimpleConditionContext : public antlr4::ParserRuleContext {
  public:
    SimpleConditionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    LiteralValueContext *literalValue();
    antlr4::tree::TerminalNode *EQ();
    antlr4::tree::TerminalNode *NEQ();
    antlr4::tree::TerminalNode *LT();
    antlr4::tree::TerminalNode *GT();
    antlr4::tree::TerminalNode *LE();
    antlr4::tree::TerminalNode *GE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  SimpleConditionContext* simpleCondition();

  class  ParenthesisPatternContext : public antlr4::ParserRuleContext {
  public:
    ParenthesisPatternContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LPAREN();
    PatternContext *pattern();
    antlr4::tree::TerminalNode *RPAREN();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ParenthesisPatternContext* parenthesisPattern();

  class  PatternFieldContext : public antlr4::ParserRuleContext {
  public:
    PatternFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    PatternContext *pattern();
    antlr4::tree::TerminalNode *WILDCARD();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PatternFieldContext* patternField();

  class  PatternFieldListContext : public antlr4::ParserRuleContext {
  public:
    PatternFieldListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PatternFieldContext *> patternField();
    PatternFieldContext* patternField(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PatternFieldListContext* patternFieldList();

  class  PatternListContext : public antlr4::ParserRuleContext {
  public:
    PatternListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<PatternContext *> pattern();
    PatternContext* pattern(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  PatternListContext* patternList();

  class  MutationExpressionContext : public antlr4::ParserRuleContext {
  public:
    MutationExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    PostfixExpressionContext *postfixExpression();
    antlr4::tree::TerminalNode *MUTATE_AT();
    MutationSiteContext *mutationSite();
    MutationChangeContext *mutationChange();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MutationExpressionContext* mutationExpression();

  class  MutationSiteContext : public antlr4::ParserRuleContext {
  public:
    MutationSiteContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT_LITERAL();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *RPAREN();
    RangeExpressionContext *rangeExpression();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MutationSiteContext* mutationSite();

  class  MutationChangeContext : public antlr4::ParserRuleContext {
  public:
    MutationChangeContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    antlr4::tree::TerminalNode *BIO_TRANSFORM();
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  MutationChangeContext* mutationChange();

  class  RangeExpressionContext : public antlr4::ParserRuleContext {
  public:
    RangeExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    antlr4::tree::TerminalNode *RANGE_OP();
    antlr4::tree::TerminalNode *INCLUSIVE_RANGE();
    antlr4::tree::TerminalNode *EXCLUSIVE_RANGE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RangeExpressionContext* rangeExpression();

  class  ListExpressionContext : public antlr4::ParserRuleContext {
  public:
    ListExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACK();
    antlr4::tree::TerminalNode *RBRACK();
    ExpressionListContext *expressionList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ListExpressionContext* listExpression();

  class  ObjectExpressionContext : public antlr4::ParserRuleContext {
  public:
    ObjectExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LCURLY();
    antlr4::tree::TerminalNode *RCURLY();
    ObjectFieldListContext *objectFieldList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ObjectExpressionContext* objectExpression();

  class  ObjectFieldContext : public antlr4::ParserRuleContext {
  public:
    ObjectFieldContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *COLON();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *STRING();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ObjectFieldContext* objectField();

  class  ObjectFieldListContext : public antlr4::ParserRuleContext {
  public:
    ObjectFieldListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ObjectFieldContext *> objectField();
    ObjectFieldContext* objectField(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ObjectFieldListContext* objectFieldList();

  class  AssignmentStatementContext : public antlr4::ParserRuleContext {
  public:
    AssignmentStatementContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    QualifiedNameContext *qualifiedName();
    antlr4::tree::TerminalNode *EQUALS();
    ExpressionContext *expression();
    antlr4::tree::TerminalNode *SEMI();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AssignmentStatementContext* assignmentStatement();

  class  AnnotationPairListContext : public antlr4::ParserRuleContext {
  public:
    AnnotationPairListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AnnotationPairContext *> annotationPair();
    AnnotationPairContext* annotationPair(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationPairListContext* annotationPairList();

  class  AnnotationPairContext : public antlr4::ParserRuleContext {
  public:
    AnnotationPairContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *COLON();
    AnnotationValueContext *annotationValue();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationPairContext* annotationPair();

  class  AnnotationValueContext : public antlr4::ParserRuleContext {
  public:
    AnnotationValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    LiteralValueContext *literalValue();
    ListLiteralContext *listLiteral();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationValueContext* annotationValue();

  class  ListLiteralContext : public antlr4::ParserRuleContext {
  public:
    ListLiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *LBRACK();
    antlr4::tree::TerminalNode *RBRACK();
    AnnotationValueListContext *annotationValueList();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ListLiteralContext* listLiteral();

  class  AnnotationValueListContext : public antlr4::ParserRuleContext {
  public:
    AnnotationValueListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<AnnotationValueContext *> annotationValue();
    AnnotationValueContext* annotationValue(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AnnotationValueListContext* annotationValueList();

  class  QualifiedNameContext : public antlr4::ParserRuleContext {
  public:
    QualifiedNameContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    std::vector<antlr4::tree::TerminalNode *> DOT();
    antlr4::tree::TerminalNode* DOT(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  QualifiedNameContext* qualifiedName();

  class  LiteralValueContext : public antlr4::ParserRuleContext {
  public:
    LiteralValueContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *BOOLEAN();
    antlr4::tree::TerminalNode *INT_LITERAL();
    antlr4::tree::TerminalNode *DECIMAL_LITERAL();
    antlr4::tree::TerminalNode *STRING();
    antlr4::tree::TerminalNode *RAW_STRING();
    antlr4::tree::TerminalNode *MULTILINE_STRING();
    antlr4::tree::TerminalNode *NULL_LIT();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralValueContext* literalValue();

  class  ExpressionListContext : public antlr4::ParserRuleContext {
  public:
    ExpressionListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ExpressionContext *> expression();
    ExpressionContext* expression(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionListContext* expressionList();

  class  IdListContext : public antlr4::ParserRuleContext {
  public:
    IdListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<antlr4::tree::TerminalNode *> ID();
    antlr4::tree::TerminalNode* ID(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdListContext* idList();

  class  ArgumentContext : public antlr4::ParserRuleContext {
  public:
    ArgumentContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *EQUALS();
    ExpressionContext *expression();
    LambdaArgumentRuleContext *lambdaArgumentRule();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentContext* argument();

  class  LambdaArgumentRuleContext : public antlr4::ParserRuleContext {
  public:
    LambdaArgumentRuleContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ID();
    antlr4::tree::TerminalNode *LAMBDA_ARROW();
    ExpressionContext *expression();
    BlockExpressionContext *blockExpression();
    antlr4::tree::TerminalNode *LPAREN();
    ParameterListContext *parameterList();
    antlr4::tree::TerminalNode *RPAREN();
    SimpleDestructureContext *simpleDestructure();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LambdaArgumentRuleContext* lambdaArgumentRule();

  class  ArgumentListContext : public antlr4::ParserRuleContext {
  public:
    ArgumentListContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    std::vector<ArgumentContext *> argument();
    ArgumentContext* argument(size_t i);
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ArgumentListContext* argumentList();


  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};

