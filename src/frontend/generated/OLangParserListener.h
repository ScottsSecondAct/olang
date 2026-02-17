
// Generated from /home/scott/Projects/olang/grammar/OLangParser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "OLangParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by OLangParser.
 */
class  OLangParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(OLangParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(OLangParser::ProgramContext *ctx) = 0;

  virtual void enterStatementList(OLangParser::StatementListContext *ctx) = 0;
  virtual void exitStatementList(OLangParser::StatementListContext *ctx) = 0;

  virtual void enterStatement(OLangParser::StatementContext *ctx) = 0;
  virtual void exitStatement(OLangParser::StatementContext *ctx) = 0;

  virtual void enterExpressionStatement(OLangParser::ExpressionStatementContext *ctx) = 0;
  virtual void exitExpressionStatement(OLangParser::ExpressionStatementContext *ctx) = 0;

  virtual void enterEmitStatement(OLangParser::EmitStatementContext *ctx) = 0;
  virtual void exitEmitStatement(OLangParser::EmitStatementContext *ctx) = 0;

  virtual void enterSignalStatement(OLangParser::SignalStatementContext *ctx) = 0;
  virtual void exitSignalStatement(OLangParser::SignalStatementContext *ctx) = 0;

  virtual void enterAssertStatement(OLangParser::AssertStatementContext *ctx) = 0;
  virtual void exitAssertStatement(OLangParser::AssertStatementContext *ctx) = 0;

  virtual void enterDeclaration(OLangParser::DeclarationContext *ctx) = 0;
  virtual void exitDeclaration(OLangParser::DeclarationContext *ctx) = 0;

  virtual void enterAgentDeclaration(OLangParser::AgentDeclarationContext *ctx) = 0;
  virtual void exitAgentDeclaration(OLangParser::AgentDeclarationContext *ctx) = 0;

  virtual void enterAgentMember(OLangParser::AgentMemberContext *ctx) = 0;
  virtual void exitAgentMember(OLangParser::AgentMemberContext *ctx) = 0;

  virtual void enterSolverDeclaration(OLangParser::SolverDeclarationContext *ctx) = 0;
  virtual void exitSolverDeclaration(OLangParser::SolverDeclarationContext *ctx) = 0;

  virtual void enterSolverMember(OLangParser::SolverMemberContext *ctx) = 0;
  virtual void exitSolverMember(OLangParser::SolverMemberContext *ctx) = 0;

  virtual void enterProofDeclaration(OLangParser::ProofDeclarationContext *ctx) = 0;
  virtual void exitProofDeclaration(OLangParser::ProofDeclarationContext *ctx) = 0;

  virtual void enterInvariantDeclaration(OLangParser::InvariantDeclarationContext *ctx) = 0;
  virtual void exitInvariantDeclaration(OLangParser::InvariantDeclarationContext *ctx) = 0;

  virtual void enterImportDeclaration(OLangParser::ImportDeclarationContext *ctx) = 0;
  virtual void exitImportDeclaration(OLangParser::ImportDeclarationContext *ctx) = 0;

  virtual void enterDottedAsNamesList(OLangParser::DottedAsNamesListContext *ctx) = 0;
  virtual void exitDottedAsNamesList(OLangParser::DottedAsNamesListContext *ctx) = 0;

  virtual void enterDottedAsNames(OLangParser::DottedAsNamesContext *ctx) = 0;
  virtual void exitDottedAsNames(OLangParser::DottedAsNamesContext *ctx) = 0;

  virtual void enterRelativeModule(OLangParser::RelativeModuleContext *ctx) = 0;
  virtual void exitRelativeModule(OLangParser::RelativeModuleContext *ctx) = 0;

  virtual void enterImportTargets(OLangParser::ImportTargetsContext *ctx) = 0;
  virtual void exitImportTargets(OLangParser::ImportTargetsContext *ctx) = 0;

  virtual void enterImportAsNames(OLangParser::ImportAsNamesContext *ctx) = 0;
  virtual void exitImportAsNames(OLangParser::ImportAsNamesContext *ctx) = 0;

  virtual void enterBindingDeclaration(OLangParser::BindingDeclarationContext *ctx) = 0;
  virtual void exitBindingDeclaration(OLangParser::BindingDeclarationContext *ctx) = 0;

  virtual void enterFunctionDeclaration(OLangParser::FunctionDeclarationContext *ctx) = 0;
  virtual void exitFunctionDeclaration(OLangParser::FunctionDeclarationContext *ctx) = 0;

  virtual void enterPipelineDeclaration(OLangParser::PipelineDeclarationContext *ctx) = 0;
  virtual void exitPipelineDeclaration(OLangParser::PipelineDeclarationContext *ctx) = 0;

  virtual void enterTypeDeclaration(OLangParser::TypeDeclarationContext *ctx) = 0;
  virtual void exitTypeDeclaration(OLangParser::TypeDeclarationContext *ctx) = 0;

  virtual void enterAnnotationTypeDeclaration(OLangParser::AnnotationTypeDeclarationContext *ctx) = 0;
  virtual void exitAnnotationTypeDeclaration(OLangParser::AnnotationTypeDeclarationContext *ctx) = 0;

  virtual void enterAnnotationStatement(OLangParser::AnnotationStatementContext *ctx) = 0;
  virtual void exitAnnotationStatement(OLangParser::AnnotationStatementContext *ctx) = 0;

  virtual void enterExpression(OLangParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(OLangParser::ExpressionContext *ctx) = 0;

  virtual void enterPipelineExpression(OLangParser::PipelineExpressionContext *ctx) = 0;
  virtual void exitPipelineExpression(OLangParser::PipelineExpressionContext *ctx) = 0;

  virtual void enterPipelineBody(OLangParser::PipelineBodyContext *ctx) = 0;
  virtual void exitPipelineBody(OLangParser::PipelineBodyContext *ctx) = 0;

  virtual void enterNullCoalesceExpression(OLangParser::NullCoalesceExpressionContext *ctx) = 0;
  virtual void exitNullCoalesceExpression(OLangParser::NullCoalesceExpressionContext *ctx) = 0;

  virtual void enterTernaryExpression(OLangParser::TernaryExpressionContext *ctx) = 0;
  virtual void exitTernaryExpression(OLangParser::TernaryExpressionContext *ctx) = 0;

  virtual void enterLogicalOrExpression(OLangParser::LogicalOrExpressionContext *ctx) = 0;
  virtual void exitLogicalOrExpression(OLangParser::LogicalOrExpressionContext *ctx) = 0;

  virtual void enterLogicalAndExpression(OLangParser::LogicalAndExpressionContext *ctx) = 0;
  virtual void exitLogicalAndExpression(OLangParser::LogicalAndExpressionContext *ctx) = 0;

  virtual void enterEqualityExpression(OLangParser::EqualityExpressionContext *ctx) = 0;
  virtual void exitEqualityExpression(OLangParser::EqualityExpressionContext *ctx) = 0;

  virtual void enterRelationalExpression(OLangParser::RelationalExpressionContext *ctx) = 0;
  virtual void exitRelationalExpression(OLangParser::RelationalExpressionContext *ctx) = 0;

  virtual void enterAdditiveExpression(OLangParser::AdditiveExpressionContext *ctx) = 0;
  virtual void exitAdditiveExpression(OLangParser::AdditiveExpressionContext *ctx) = 0;

  virtual void enterMultiplicativeExpression(OLangParser::MultiplicativeExpressionContext *ctx) = 0;
  virtual void exitMultiplicativeExpression(OLangParser::MultiplicativeExpressionContext *ctx) = 0;

  virtual void enterUnaryExpression(OLangParser::UnaryExpressionContext *ctx) = 0;
  virtual void exitUnaryExpression(OLangParser::UnaryExpressionContext *ctx) = 0;

  virtual void enterErrorPropagationExpression(OLangParser::ErrorPropagationExpressionContext *ctx) = 0;
  virtual void exitErrorPropagationExpression(OLangParser::ErrorPropagationExpressionContext *ctx) = 0;

  virtual void enterPostfixExpression(OLangParser::PostfixExpressionContext *ctx) = 0;
  virtual void exitPostfixExpression(OLangParser::PostfixExpressionContext *ctx) = 0;

  virtual void enterCallSuffix(OLangParser::CallSuffixContext *ctx) = 0;
  virtual void exitCallSuffix(OLangParser::CallSuffixContext *ctx) = 0;

  virtual void enterCallArguments(OLangParser::CallArgumentsContext *ctx) = 0;
  virtual void exitCallArguments(OLangParser::CallArgumentsContext *ctx) = 0;

  virtual void enterPrimaryExpression(OLangParser::PrimaryExpressionContext *ctx) = 0;
  virtual void exitPrimaryExpression(OLangParser::PrimaryExpressionContext *ctx) = 0;

  virtual void enterType(OLangParser::TypeContext *ctx) = 0;
  virtual void exitType(OLangParser::TypeContext *ctx) = 0;

  virtual void enterOptionalType(OLangParser::OptionalTypeContext *ctx) = 0;
  virtual void exitOptionalType(OLangParser::OptionalTypeContext *ctx) = 0;

  virtual void enterBaseType(OLangParser::BaseTypeContext *ctx) = 0;
  virtual void exitBaseType(OLangParser::BaseTypeContext *ctx) = 0;

  virtual void enterPrimitiveType(OLangParser::PrimitiveTypeContext *ctx) = 0;
  virtual void exitPrimitiveType(OLangParser::PrimitiveTypeContext *ctx) = 0;

  virtual void enterUserDefinedType(OLangParser::UserDefinedTypeContext *ctx) = 0;
  virtual void exitUserDefinedType(OLangParser::UserDefinedTypeContext *ctx) = 0;

  virtual void enterPipelineType(OLangParser::PipelineTypeContext *ctx) = 0;
  virtual void exitPipelineType(OLangParser::PipelineTypeContext *ctx) = 0;

  virtual void enterListType(OLangParser::ListTypeContext *ctx) = 0;
  virtual void exitListType(OLangParser::ListTypeContext *ctx) = 0;

  virtual void enterMapType(OLangParser::MapTypeContext *ctx) = 0;
  virtual void exitMapType(OLangParser::MapTypeContext *ctx) = 0;

  virtual void enterSetType(OLangParser::SetTypeContext *ctx) = 0;
  virtual void exitSetType(OLangParser::SetTypeContext *ctx) = 0;

  virtual void enterStreamType(OLangParser::StreamTypeContext *ctx) = 0;
  virtual void exitStreamType(OLangParser::StreamTypeContext *ctx) = 0;

  virtual void enterFutureType(OLangParser::FutureTypeContext *ctx) = 0;
  virtual void exitFutureType(OLangParser::FutureTypeContext *ctx) = 0;

  virtual void enterResultType(OLangParser::ResultTypeContext *ctx) = 0;
  virtual void exitResultType(OLangParser::ResultTypeContext *ctx) = 0;

  virtual void enterOptionType(OLangParser::OptionTypeContext *ctx) = 0;
  virtual void exitOptionType(OLangParser::OptionTypeContext *ctx) = 0;

  virtual void enterProvenanceType(OLangParser::ProvenanceTypeContext *ctx) = 0;
  virtual void exitProvenanceType(OLangParser::ProvenanceTypeContext *ctx) = 0;

  virtual void enterFunctionType(OLangParser::FunctionTypeContext *ctx) = 0;
  virtual void exitFunctionType(OLangParser::FunctionTypeContext *ctx) = 0;

  virtual void enterParenthesisType(OLangParser::ParenthesisTypeContext *ctx) = 0;
  virtual void exitParenthesisType(OLangParser::ParenthesisTypeContext *ctx) = 0;

  virtual void enterGenericArguments(OLangParser::GenericArgumentsContext *ctx) = 0;
  virtual void exitGenericArguments(OLangParser::GenericArgumentsContext *ctx) = 0;

  virtual void enterTypeList(OLangParser::TypeListContext *ctx) = 0;
  virtual void exitTypeList(OLangParser::TypeListContext *ctx) = 0;

  virtual void enterGenericParameters(OLangParser::GenericParametersContext *ctx) = 0;
  virtual void exitGenericParameters(OLangParser::GenericParametersContext *ctx) = 0;

  virtual void enterGenericParameterList(OLangParser::GenericParameterListContext *ctx) = 0;
  virtual void exitGenericParameterList(OLangParser::GenericParameterListContext *ctx) = 0;

  virtual void enterGenericParameter(OLangParser::GenericParameterContext *ctx) = 0;
  virtual void exitGenericParameter(OLangParser::GenericParameterContext *ctx) = 0;

  virtual void enterGenericParameterConstraint(OLangParser::GenericParameterConstraintContext *ctx) = 0;
  virtual void exitGenericParameterConstraint(OLangParser::GenericParameterConstraintContext *ctx) = 0;

  virtual void enterWhereClause(OLangParser::WhereClauseContext *ctx) = 0;
  virtual void exitWhereClause(OLangParser::WhereClauseContext *ctx) = 0;

  virtual void enterConstraintList(OLangParser::ConstraintListContext *ctx) = 0;
  virtual void exitConstraintList(OLangParser::ConstraintListContext *ctx) = 0;

  virtual void enterConstraint(OLangParser::ConstraintContext *ctx) = 0;
  virtual void exitConstraint(OLangParser::ConstraintContext *ctx) = 0;

  virtual void enterTypedField(OLangParser::TypedFieldContext *ctx) = 0;
  virtual void exitTypedField(OLangParser::TypedFieldContext *ctx) = 0;

  virtual void enterTypedFieldList(OLangParser::TypedFieldListContext *ctx) = 0;
  virtual void exitTypedFieldList(OLangParser::TypedFieldListContext *ctx) = 0;

  virtual void enterTypedParameter(OLangParser::TypedParameterContext *ctx) = 0;
  virtual void exitTypedParameter(OLangParser::TypedParameterContext *ctx) = 0;

  virtual void enterTypedParameterList(OLangParser::TypedParameterListContext *ctx) = 0;
  virtual void exitTypedParameterList(OLangParser::TypedParameterListContext *ctx) = 0;

  virtual void enterFunctionalExpression(OLangParser::FunctionalExpressionContext *ctx) = 0;
  virtual void exitFunctionalExpression(OLangParser::FunctionalExpressionContext *ctx) = 0;

  virtual void enterMapExpression(OLangParser::MapExpressionContext *ctx) = 0;
  virtual void exitMapExpression(OLangParser::MapExpressionContext *ctx) = 0;

  virtual void enterFilterExpression(OLangParser::FilterExpressionContext *ctx) = 0;
  virtual void exitFilterExpression(OLangParser::FilterExpressionContext *ctx) = 0;

  virtual void enterReduceExpression(OLangParser::ReduceExpressionContext *ctx) = 0;
  virtual void exitReduceExpression(OLangParser::ReduceExpressionContext *ctx) = 0;

  virtual void enterForeachExpression(OLangParser::ForeachExpressionContext *ctx) = 0;
  virtual void exitForeachExpression(OLangParser::ForeachExpressionContext *ctx) = 0;

  virtual void enterGroupByExpression(OLangParser::GroupByExpressionContext *ctx) = 0;
  virtual void exitGroupByExpression(OLangParser::GroupByExpressionContext *ctx) = 0;

  virtual void enterFlatMapExpression(OLangParser::FlatMapExpressionContext *ctx) = 0;
  virtual void exitFlatMapExpression(OLangParser::FlatMapExpressionContext *ctx) = 0;

  virtual void enterZipExpression(OLangParser::ZipExpressionContext *ctx) = 0;
  virtual void exitZipExpression(OLangParser::ZipExpressionContext *ctx) = 0;

  virtual void enterPartitionExpression(OLangParser::PartitionExpressionContext *ctx) = 0;
  virtual void exitPartitionExpression(OLangParser::PartitionExpressionContext *ctx) = 0;

  virtual void enterTakeExpression(OLangParser::TakeExpressionContext *ctx) = 0;
  virtual void exitTakeExpression(OLangParser::TakeExpressionContext *ctx) = 0;

  virtual void enterDropExpression(OLangParser::DropExpressionContext *ctx) = 0;
  virtual void exitDropExpression(OLangParser::DropExpressionContext *ctx) = 0;

  virtual void enterTakeWhileExpression(OLangParser::TakeWhileExpressionContext *ctx) = 0;
  virtual void exitTakeWhileExpression(OLangParser::TakeWhileExpressionContext *ctx) = 0;

  virtual void enterDropWhileExpression(OLangParser::DropWhileExpressionContext *ctx) = 0;
  virtual void exitDropWhileExpression(OLangParser::DropWhileExpressionContext *ctx) = 0;

  virtual void enterSortByExpression(OLangParser::SortByExpressionContext *ctx) = 0;
  virtual void exitSortByExpression(OLangParser::SortByExpressionContext *ctx) = 0;

  virtual void enterDistinctExpression(OLangParser::DistinctExpressionContext *ctx) = 0;
  virtual void exitDistinctExpression(OLangParser::DistinctExpressionContext *ctx) = 0;

  virtual void enterCountExpression(OLangParser::CountExpressionContext *ctx) = 0;
  virtual void exitCountExpression(OLangParser::CountExpressionContext *ctx) = 0;

  virtual void enterFindExpression(OLangParser::FindExpressionContext *ctx) = 0;
  virtual void exitFindExpression(OLangParser::FindExpressionContext *ctx) = 0;

  virtual void enterAnyExpression(OLangParser::AnyExpressionContext *ctx) = 0;
  virtual void exitAnyExpression(OLangParser::AnyExpressionContext *ctx) = 0;

  virtual void enterAllExpression(OLangParser::AllExpressionContext *ctx) = 0;
  virtual void exitAllExpression(OLangParser::AllExpressionContext *ctx) = 0;

  virtual void enterJoinExpression(OLangParser::JoinExpressionContext *ctx) = 0;
  virtual void exitJoinExpression(OLangParser::JoinExpressionContext *ctx) = 0;

  virtual void enterJoinClause(OLangParser::JoinClauseContext *ctx) = 0;
  virtual void exitJoinClause(OLangParser::JoinClauseContext *ctx) = 0;

  virtual void enterWindowExpression(OLangParser::WindowExpressionContext *ctx) = 0;
  virtual void exitWindowExpression(OLangParser::WindowExpressionContext *ctx) = 0;

  virtual void enterChunkExpression(OLangParser::ChunkExpressionContext *ctx) = 0;
  virtual void exitChunkExpression(OLangParser::ChunkExpressionContext *ctx) = 0;

  virtual void enterScanExpression(OLangParser::ScanExpressionContext *ctx) = 0;
  virtual void exitScanExpression(OLangParser::ScanExpressionContext *ctx) = 0;

  virtual void enterCollectExpression(OLangParser::CollectExpressionContext *ctx) = 0;
  virtual void exitCollectExpression(OLangParser::CollectExpressionContext *ctx) = 0;

  virtual void enterLambdaExpression(OLangParser::LambdaExpressionContext *ctx) = 0;
  virtual void exitLambdaExpression(OLangParser::LambdaExpressionContext *ctx) = 0;

  virtual void enterMultipleParameterLambda(OLangParser::MultipleParameterLambdaContext *ctx) = 0;
  virtual void exitMultipleParameterLambda(OLangParser::MultipleParameterLambdaContext *ctx) = 0;

  virtual void enterParameterList(OLangParser::ParameterListContext *ctx) = 0;
  virtual void exitParameterList(OLangParser::ParameterListContext *ctx) = 0;

  virtual void enterParameter(OLangParser::ParameterContext *ctx) = 0;
  virtual void exitParameter(OLangParser::ParameterContext *ctx) = 0;

  virtual void enterSimplePatternLambda(OLangParser::SimplePatternLambdaContext *ctx) = 0;
  virtual void exitSimplePatternLambda(OLangParser::SimplePatternLambdaContext *ctx) = 0;

  virtual void enterSimpleDestructure(OLangParser::SimpleDestructureContext *ctx) = 0;
  virtual void exitSimpleDestructure(OLangParser::SimpleDestructureContext *ctx) = 0;

  virtual void enterSimpleLambda(OLangParser::SimpleLambdaContext *ctx) = 0;
  virtual void exitSimpleLambda(OLangParser::SimpleLambdaContext *ctx) = 0;

  virtual void enterSimplePatternList(OLangParser::SimplePatternListContext *ctx) = 0;
  virtual void exitSimplePatternList(OLangParser::SimplePatternListContext *ctx) = 0;

  virtual void enterSimplePatternFieldList(OLangParser::SimplePatternFieldListContext *ctx) = 0;
  virtual void exitSimplePatternFieldList(OLangParser::SimplePatternFieldListContext *ctx) = 0;

  virtual void enterSimplePatternElement(OLangParser::SimplePatternElementContext *ctx) = 0;
  virtual void exitSimplePatternElement(OLangParser::SimplePatternElementContext *ctx) = 0;

  virtual void enterSimplePatternField(OLangParser::SimplePatternFieldContext *ctx) = 0;
  virtual void exitSimplePatternField(OLangParser::SimplePatternFieldContext *ctx) = 0;

  virtual void enterBlockExpression(OLangParser::BlockExpressionContext *ctx) = 0;
  virtual void exitBlockExpression(OLangParser::BlockExpressionContext *ctx) = 0;

  virtual void enterTransformationList(OLangParser::TransformationListContext *ctx) = 0;
  virtual void exitTransformationList(OLangParser::TransformationListContext *ctx) = 0;

  virtual void enterTransformation(OLangParser::TransformationContext *ctx) = 0;
  virtual void exitTransformation(OLangParser::TransformationContext *ctx) = 0;

  virtual void enterMatchExpression(OLangParser::MatchExpressionContext *ctx) = 0;
  virtual void exitMatchExpression(OLangParser::MatchExpressionContext *ctx) = 0;

  virtual void enterMatchArm(OLangParser::MatchArmContext *ctx) = 0;
  virtual void exitMatchArm(OLangParser::MatchArmContext *ctx) = 0;

  virtual void enterMatchArmList(OLangParser::MatchArmListContext *ctx) = 0;
  virtual void exitMatchArmList(OLangParser::MatchArmListContext *ctx) = 0;

  virtual void enterPattern(OLangParser::PatternContext *ctx) = 0;
  virtual void exitPattern(OLangParser::PatternContext *ctx) = 0;

  virtual void enterOrPattern(OLangParser::OrPatternContext *ctx) = 0;
  virtual void exitOrPattern(OLangParser::OrPatternContext *ctx) = 0;

  virtual void enterAndPattern(OLangParser::AndPatternContext *ctx) = 0;
  virtual void exitAndPattern(OLangParser::AndPatternContext *ctx) = 0;

  virtual void enterPrimaryPattern(OLangParser::PrimaryPatternContext *ctx) = 0;
  virtual void exitPrimaryPattern(OLangParser::PrimaryPatternContext *ctx) = 0;

  virtual void enterWildcardPattern(OLangParser::WildcardPatternContext *ctx) = 0;
  virtual void exitWildcardPattern(OLangParser::WildcardPatternContext *ctx) = 0;

  virtual void enterLiteralPattern(OLangParser::LiteralPatternContext *ctx) = 0;
  virtual void exitLiteralPattern(OLangParser::LiteralPatternContext *ctx) = 0;

  virtual void enterIdentifierPattern(OLangParser::IdentifierPatternContext *ctx) = 0;
  virtual void exitIdentifierPattern(OLangParser::IdentifierPatternContext *ctx) = 0;

  virtual void enterDestructurePattern(OLangParser::DestructurePatternContext *ctx) = 0;
  virtual void exitDestructurePattern(OLangParser::DestructurePatternContext *ctx) = 0;

  virtual void enterObjectDestructure(OLangParser::ObjectDestructureContext *ctx) = 0;
  virtual void exitObjectDestructure(OLangParser::ObjectDestructureContext *ctx) = 0;

  virtual void enterListDestructure(OLangParser::ListDestructureContext *ctx) = 0;
  virtual void exitListDestructure(OLangParser::ListDestructureContext *ctx) = 0;

  virtual void enterTupleDestructure(OLangParser::TupleDestructureContext *ctx) = 0;
  virtual void exitTupleDestructure(OLangParser::TupleDestructureContext *ctx) = 0;

  virtual void enterNamedDestructure(OLangParser::NamedDestructureContext *ctx) = 0;
  virtual void exitNamedDestructure(OLangParser::NamedDestructureContext *ctx) = 0;

  virtual void enterRangePattern(OLangParser::RangePatternContext *ctx) = 0;
  virtual void exitRangePattern(OLangParser::RangePatternContext *ctx) = 0;

  virtual void enterSimpleRangeValue(OLangParser::SimpleRangeValueContext *ctx) = 0;
  virtual void exitSimpleRangeValue(OLangParser::SimpleRangeValueContext *ctx) = 0;

  virtual void enterTypePattern(OLangParser::TypePatternContext *ctx) = 0;
  virtual void exitTypePattern(OLangParser::TypePatternContext *ctx) = 0;

  virtual void enterSimplePattern(OLangParser::SimplePatternContext *ctx) = 0;
  virtual void exitSimplePattern(OLangParser::SimplePatternContext *ctx) = 0;

  virtual void enterGuardPattern(OLangParser::GuardPatternContext *ctx) = 0;
  virtual void exitGuardPattern(OLangParser::GuardPatternContext *ctx) = 0;

  virtual void enterSimpleCondition(OLangParser::SimpleConditionContext *ctx) = 0;
  virtual void exitSimpleCondition(OLangParser::SimpleConditionContext *ctx) = 0;

  virtual void enterParenthesisPattern(OLangParser::ParenthesisPatternContext *ctx) = 0;
  virtual void exitParenthesisPattern(OLangParser::ParenthesisPatternContext *ctx) = 0;

  virtual void enterPatternField(OLangParser::PatternFieldContext *ctx) = 0;
  virtual void exitPatternField(OLangParser::PatternFieldContext *ctx) = 0;

  virtual void enterPatternFieldList(OLangParser::PatternFieldListContext *ctx) = 0;
  virtual void exitPatternFieldList(OLangParser::PatternFieldListContext *ctx) = 0;

  virtual void enterPatternList(OLangParser::PatternListContext *ctx) = 0;
  virtual void exitPatternList(OLangParser::PatternListContext *ctx) = 0;

  virtual void enterMutationExpression(OLangParser::MutationExpressionContext *ctx) = 0;
  virtual void exitMutationExpression(OLangParser::MutationExpressionContext *ctx) = 0;

  virtual void enterMutationSite(OLangParser::MutationSiteContext *ctx) = 0;
  virtual void exitMutationSite(OLangParser::MutationSiteContext *ctx) = 0;

  virtual void enterMutationChange(OLangParser::MutationChangeContext *ctx) = 0;
  virtual void exitMutationChange(OLangParser::MutationChangeContext *ctx) = 0;

  virtual void enterRangeExpression(OLangParser::RangeExpressionContext *ctx) = 0;
  virtual void exitRangeExpression(OLangParser::RangeExpressionContext *ctx) = 0;

  virtual void enterListExpression(OLangParser::ListExpressionContext *ctx) = 0;
  virtual void exitListExpression(OLangParser::ListExpressionContext *ctx) = 0;

  virtual void enterObjectExpression(OLangParser::ObjectExpressionContext *ctx) = 0;
  virtual void exitObjectExpression(OLangParser::ObjectExpressionContext *ctx) = 0;

  virtual void enterObjectField(OLangParser::ObjectFieldContext *ctx) = 0;
  virtual void exitObjectField(OLangParser::ObjectFieldContext *ctx) = 0;

  virtual void enterObjectFieldList(OLangParser::ObjectFieldListContext *ctx) = 0;
  virtual void exitObjectFieldList(OLangParser::ObjectFieldListContext *ctx) = 0;

  virtual void enterAssignmentStatement(OLangParser::AssignmentStatementContext *ctx) = 0;
  virtual void exitAssignmentStatement(OLangParser::AssignmentStatementContext *ctx) = 0;

  virtual void enterAnnotationPairList(OLangParser::AnnotationPairListContext *ctx) = 0;
  virtual void exitAnnotationPairList(OLangParser::AnnotationPairListContext *ctx) = 0;

  virtual void enterAnnotationPair(OLangParser::AnnotationPairContext *ctx) = 0;
  virtual void exitAnnotationPair(OLangParser::AnnotationPairContext *ctx) = 0;

  virtual void enterAnnotationValue(OLangParser::AnnotationValueContext *ctx) = 0;
  virtual void exitAnnotationValue(OLangParser::AnnotationValueContext *ctx) = 0;

  virtual void enterListLiteral(OLangParser::ListLiteralContext *ctx) = 0;
  virtual void exitListLiteral(OLangParser::ListLiteralContext *ctx) = 0;

  virtual void enterAnnotationValueList(OLangParser::AnnotationValueListContext *ctx) = 0;
  virtual void exitAnnotationValueList(OLangParser::AnnotationValueListContext *ctx) = 0;

  virtual void enterQualifiedName(OLangParser::QualifiedNameContext *ctx) = 0;
  virtual void exitQualifiedName(OLangParser::QualifiedNameContext *ctx) = 0;

  virtual void enterLiteralValue(OLangParser::LiteralValueContext *ctx) = 0;
  virtual void exitLiteralValue(OLangParser::LiteralValueContext *ctx) = 0;

  virtual void enterExpressionList(OLangParser::ExpressionListContext *ctx) = 0;
  virtual void exitExpressionList(OLangParser::ExpressionListContext *ctx) = 0;

  virtual void enterIdList(OLangParser::IdListContext *ctx) = 0;
  virtual void exitIdList(OLangParser::IdListContext *ctx) = 0;

  virtual void enterArgument(OLangParser::ArgumentContext *ctx) = 0;
  virtual void exitArgument(OLangParser::ArgumentContext *ctx) = 0;

  virtual void enterLambdaArgumentRule(OLangParser::LambdaArgumentRuleContext *ctx) = 0;
  virtual void exitLambdaArgumentRule(OLangParser::LambdaArgumentRuleContext *ctx) = 0;

  virtual void enterArgumentList(OLangParser::ArgumentListContext *ctx) = 0;
  virtual void exitArgumentList(OLangParser::ArgumentListContext *ctx) = 0;


};

