
// Generated from /home/scott/Projects/olang/grammar/OLangParser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "OLangParserListener.h"


/**
 * This class provides an empty implementation of OLangParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  OLangParserBaseListener : public OLangParserListener {
public:

  virtual void enterProgram(OLangParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(OLangParser::ProgramContext * /*ctx*/) override { }

  virtual void enterStatementList(OLangParser::StatementListContext * /*ctx*/) override { }
  virtual void exitStatementList(OLangParser::StatementListContext * /*ctx*/) override { }

  virtual void enterStatement(OLangParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(OLangParser::StatementContext * /*ctx*/) override { }

  virtual void enterExpressionStatement(OLangParser::ExpressionStatementContext * /*ctx*/) override { }
  virtual void exitExpressionStatement(OLangParser::ExpressionStatementContext * /*ctx*/) override { }

  virtual void enterEmitStatement(OLangParser::EmitStatementContext * /*ctx*/) override { }
  virtual void exitEmitStatement(OLangParser::EmitStatementContext * /*ctx*/) override { }

  virtual void enterSignalStatement(OLangParser::SignalStatementContext * /*ctx*/) override { }
  virtual void exitSignalStatement(OLangParser::SignalStatementContext * /*ctx*/) override { }

  virtual void enterAssertStatement(OLangParser::AssertStatementContext * /*ctx*/) override { }
  virtual void exitAssertStatement(OLangParser::AssertStatementContext * /*ctx*/) override { }

  virtual void enterDeclaration(OLangParser::DeclarationContext * /*ctx*/) override { }
  virtual void exitDeclaration(OLangParser::DeclarationContext * /*ctx*/) override { }

  virtual void enterAgentDeclaration(OLangParser::AgentDeclarationContext * /*ctx*/) override { }
  virtual void exitAgentDeclaration(OLangParser::AgentDeclarationContext * /*ctx*/) override { }

  virtual void enterAgentMember(OLangParser::AgentMemberContext * /*ctx*/) override { }
  virtual void exitAgentMember(OLangParser::AgentMemberContext * /*ctx*/) override { }

  virtual void enterSolverDeclaration(OLangParser::SolverDeclarationContext * /*ctx*/) override { }
  virtual void exitSolverDeclaration(OLangParser::SolverDeclarationContext * /*ctx*/) override { }

  virtual void enterSolverMember(OLangParser::SolverMemberContext * /*ctx*/) override { }
  virtual void exitSolverMember(OLangParser::SolverMemberContext * /*ctx*/) override { }

  virtual void enterProofDeclaration(OLangParser::ProofDeclarationContext * /*ctx*/) override { }
  virtual void exitProofDeclaration(OLangParser::ProofDeclarationContext * /*ctx*/) override { }

  virtual void enterInvariantDeclaration(OLangParser::InvariantDeclarationContext * /*ctx*/) override { }
  virtual void exitInvariantDeclaration(OLangParser::InvariantDeclarationContext * /*ctx*/) override { }

  virtual void enterImportDeclaration(OLangParser::ImportDeclarationContext * /*ctx*/) override { }
  virtual void exitImportDeclaration(OLangParser::ImportDeclarationContext * /*ctx*/) override { }

  virtual void enterDottedAsNamesList(OLangParser::DottedAsNamesListContext * /*ctx*/) override { }
  virtual void exitDottedAsNamesList(OLangParser::DottedAsNamesListContext * /*ctx*/) override { }

  virtual void enterDottedAsNames(OLangParser::DottedAsNamesContext * /*ctx*/) override { }
  virtual void exitDottedAsNames(OLangParser::DottedAsNamesContext * /*ctx*/) override { }

  virtual void enterRelativeModule(OLangParser::RelativeModuleContext * /*ctx*/) override { }
  virtual void exitRelativeModule(OLangParser::RelativeModuleContext * /*ctx*/) override { }

  virtual void enterImportTargets(OLangParser::ImportTargetsContext * /*ctx*/) override { }
  virtual void exitImportTargets(OLangParser::ImportTargetsContext * /*ctx*/) override { }

  virtual void enterImportAsNames(OLangParser::ImportAsNamesContext * /*ctx*/) override { }
  virtual void exitImportAsNames(OLangParser::ImportAsNamesContext * /*ctx*/) override { }

  virtual void enterBindingDeclaration(OLangParser::BindingDeclarationContext * /*ctx*/) override { }
  virtual void exitBindingDeclaration(OLangParser::BindingDeclarationContext * /*ctx*/) override { }

  virtual void enterFunctionDeclaration(OLangParser::FunctionDeclarationContext * /*ctx*/) override { }
  virtual void exitFunctionDeclaration(OLangParser::FunctionDeclarationContext * /*ctx*/) override { }

  virtual void enterPipelineDeclaration(OLangParser::PipelineDeclarationContext * /*ctx*/) override { }
  virtual void exitPipelineDeclaration(OLangParser::PipelineDeclarationContext * /*ctx*/) override { }

  virtual void enterTypeDeclaration(OLangParser::TypeDeclarationContext * /*ctx*/) override { }
  virtual void exitTypeDeclaration(OLangParser::TypeDeclarationContext * /*ctx*/) override { }

  virtual void enterAnnotationTypeDeclaration(OLangParser::AnnotationTypeDeclarationContext * /*ctx*/) override { }
  virtual void exitAnnotationTypeDeclaration(OLangParser::AnnotationTypeDeclarationContext * /*ctx*/) override { }

  virtual void enterAnnotationStatement(OLangParser::AnnotationStatementContext * /*ctx*/) override { }
  virtual void exitAnnotationStatement(OLangParser::AnnotationStatementContext * /*ctx*/) override { }

  virtual void enterExpression(OLangParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(OLangParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterPipelineExpression(OLangParser::PipelineExpressionContext * /*ctx*/) override { }
  virtual void exitPipelineExpression(OLangParser::PipelineExpressionContext * /*ctx*/) override { }

  virtual void enterPipelineBody(OLangParser::PipelineBodyContext * /*ctx*/) override { }
  virtual void exitPipelineBody(OLangParser::PipelineBodyContext * /*ctx*/) override { }

  virtual void enterNullCoalesceExpression(OLangParser::NullCoalesceExpressionContext * /*ctx*/) override { }
  virtual void exitNullCoalesceExpression(OLangParser::NullCoalesceExpressionContext * /*ctx*/) override { }

  virtual void enterTernaryExpression(OLangParser::TernaryExpressionContext * /*ctx*/) override { }
  virtual void exitTernaryExpression(OLangParser::TernaryExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalOrExpression(OLangParser::LogicalOrExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalOrExpression(OLangParser::LogicalOrExpressionContext * /*ctx*/) override { }

  virtual void enterLogicalAndExpression(OLangParser::LogicalAndExpressionContext * /*ctx*/) override { }
  virtual void exitLogicalAndExpression(OLangParser::LogicalAndExpressionContext * /*ctx*/) override { }

  virtual void enterEqualityExpression(OLangParser::EqualityExpressionContext * /*ctx*/) override { }
  virtual void exitEqualityExpression(OLangParser::EqualityExpressionContext * /*ctx*/) override { }

  virtual void enterRelationalExpression(OLangParser::RelationalExpressionContext * /*ctx*/) override { }
  virtual void exitRelationalExpression(OLangParser::RelationalExpressionContext * /*ctx*/) override { }

  virtual void enterAdditiveExpression(OLangParser::AdditiveExpressionContext * /*ctx*/) override { }
  virtual void exitAdditiveExpression(OLangParser::AdditiveExpressionContext * /*ctx*/) override { }

  virtual void enterMultiplicativeExpression(OLangParser::MultiplicativeExpressionContext * /*ctx*/) override { }
  virtual void exitMultiplicativeExpression(OLangParser::MultiplicativeExpressionContext * /*ctx*/) override { }

  virtual void enterUnaryExpression(OLangParser::UnaryExpressionContext * /*ctx*/) override { }
  virtual void exitUnaryExpression(OLangParser::UnaryExpressionContext * /*ctx*/) override { }

  virtual void enterErrorPropagationExpression(OLangParser::ErrorPropagationExpressionContext * /*ctx*/) override { }
  virtual void exitErrorPropagationExpression(OLangParser::ErrorPropagationExpressionContext * /*ctx*/) override { }

  virtual void enterPostfixExpression(OLangParser::PostfixExpressionContext * /*ctx*/) override { }
  virtual void exitPostfixExpression(OLangParser::PostfixExpressionContext * /*ctx*/) override { }

  virtual void enterCallSuffix(OLangParser::CallSuffixContext * /*ctx*/) override { }
  virtual void exitCallSuffix(OLangParser::CallSuffixContext * /*ctx*/) override { }

  virtual void enterCallArguments(OLangParser::CallArgumentsContext * /*ctx*/) override { }
  virtual void exitCallArguments(OLangParser::CallArgumentsContext * /*ctx*/) override { }

  virtual void enterPrimaryExpression(OLangParser::PrimaryExpressionContext * /*ctx*/) override { }
  virtual void exitPrimaryExpression(OLangParser::PrimaryExpressionContext * /*ctx*/) override { }

  virtual void enterType(OLangParser::TypeContext * /*ctx*/) override { }
  virtual void exitType(OLangParser::TypeContext * /*ctx*/) override { }

  virtual void enterOptionalType(OLangParser::OptionalTypeContext * /*ctx*/) override { }
  virtual void exitOptionalType(OLangParser::OptionalTypeContext * /*ctx*/) override { }

  virtual void enterBaseType(OLangParser::BaseTypeContext * /*ctx*/) override { }
  virtual void exitBaseType(OLangParser::BaseTypeContext * /*ctx*/) override { }

  virtual void enterPrimitiveType(OLangParser::PrimitiveTypeContext * /*ctx*/) override { }
  virtual void exitPrimitiveType(OLangParser::PrimitiveTypeContext * /*ctx*/) override { }

  virtual void enterUserDefinedType(OLangParser::UserDefinedTypeContext * /*ctx*/) override { }
  virtual void exitUserDefinedType(OLangParser::UserDefinedTypeContext * /*ctx*/) override { }

  virtual void enterPipelineType(OLangParser::PipelineTypeContext * /*ctx*/) override { }
  virtual void exitPipelineType(OLangParser::PipelineTypeContext * /*ctx*/) override { }

  virtual void enterListType(OLangParser::ListTypeContext * /*ctx*/) override { }
  virtual void exitListType(OLangParser::ListTypeContext * /*ctx*/) override { }

  virtual void enterMapType(OLangParser::MapTypeContext * /*ctx*/) override { }
  virtual void exitMapType(OLangParser::MapTypeContext * /*ctx*/) override { }

  virtual void enterSetType(OLangParser::SetTypeContext * /*ctx*/) override { }
  virtual void exitSetType(OLangParser::SetTypeContext * /*ctx*/) override { }

  virtual void enterStreamType(OLangParser::StreamTypeContext * /*ctx*/) override { }
  virtual void exitStreamType(OLangParser::StreamTypeContext * /*ctx*/) override { }

  virtual void enterFutureType(OLangParser::FutureTypeContext * /*ctx*/) override { }
  virtual void exitFutureType(OLangParser::FutureTypeContext * /*ctx*/) override { }

  virtual void enterResultType(OLangParser::ResultTypeContext * /*ctx*/) override { }
  virtual void exitResultType(OLangParser::ResultTypeContext * /*ctx*/) override { }

  virtual void enterOptionType(OLangParser::OptionTypeContext * /*ctx*/) override { }
  virtual void exitOptionType(OLangParser::OptionTypeContext * /*ctx*/) override { }

  virtual void enterProvenanceType(OLangParser::ProvenanceTypeContext * /*ctx*/) override { }
  virtual void exitProvenanceType(OLangParser::ProvenanceTypeContext * /*ctx*/) override { }

  virtual void enterFunctionType(OLangParser::FunctionTypeContext * /*ctx*/) override { }
  virtual void exitFunctionType(OLangParser::FunctionTypeContext * /*ctx*/) override { }

  virtual void enterParenthesisType(OLangParser::ParenthesisTypeContext * /*ctx*/) override { }
  virtual void exitParenthesisType(OLangParser::ParenthesisTypeContext * /*ctx*/) override { }

  virtual void enterGenericArguments(OLangParser::GenericArgumentsContext * /*ctx*/) override { }
  virtual void exitGenericArguments(OLangParser::GenericArgumentsContext * /*ctx*/) override { }

  virtual void enterTypeList(OLangParser::TypeListContext * /*ctx*/) override { }
  virtual void exitTypeList(OLangParser::TypeListContext * /*ctx*/) override { }

  virtual void enterGenericParameters(OLangParser::GenericParametersContext * /*ctx*/) override { }
  virtual void exitGenericParameters(OLangParser::GenericParametersContext * /*ctx*/) override { }

  virtual void enterGenericParameterList(OLangParser::GenericParameterListContext * /*ctx*/) override { }
  virtual void exitGenericParameterList(OLangParser::GenericParameterListContext * /*ctx*/) override { }

  virtual void enterGenericParameter(OLangParser::GenericParameterContext * /*ctx*/) override { }
  virtual void exitGenericParameter(OLangParser::GenericParameterContext * /*ctx*/) override { }

  virtual void enterGenericParameterConstraint(OLangParser::GenericParameterConstraintContext * /*ctx*/) override { }
  virtual void exitGenericParameterConstraint(OLangParser::GenericParameterConstraintContext * /*ctx*/) override { }

  virtual void enterWhereClause(OLangParser::WhereClauseContext * /*ctx*/) override { }
  virtual void exitWhereClause(OLangParser::WhereClauseContext * /*ctx*/) override { }

  virtual void enterConstraintList(OLangParser::ConstraintListContext * /*ctx*/) override { }
  virtual void exitConstraintList(OLangParser::ConstraintListContext * /*ctx*/) override { }

  virtual void enterConstraint(OLangParser::ConstraintContext * /*ctx*/) override { }
  virtual void exitConstraint(OLangParser::ConstraintContext * /*ctx*/) override { }

  virtual void enterTypedField(OLangParser::TypedFieldContext * /*ctx*/) override { }
  virtual void exitTypedField(OLangParser::TypedFieldContext * /*ctx*/) override { }

  virtual void enterTypedFieldList(OLangParser::TypedFieldListContext * /*ctx*/) override { }
  virtual void exitTypedFieldList(OLangParser::TypedFieldListContext * /*ctx*/) override { }

  virtual void enterTypedParameter(OLangParser::TypedParameterContext * /*ctx*/) override { }
  virtual void exitTypedParameter(OLangParser::TypedParameterContext * /*ctx*/) override { }

  virtual void enterTypedParameterList(OLangParser::TypedParameterListContext * /*ctx*/) override { }
  virtual void exitTypedParameterList(OLangParser::TypedParameterListContext * /*ctx*/) override { }

  virtual void enterFunctionalExpression(OLangParser::FunctionalExpressionContext * /*ctx*/) override { }
  virtual void exitFunctionalExpression(OLangParser::FunctionalExpressionContext * /*ctx*/) override { }

  virtual void enterMapExpression(OLangParser::MapExpressionContext * /*ctx*/) override { }
  virtual void exitMapExpression(OLangParser::MapExpressionContext * /*ctx*/) override { }

  virtual void enterFilterExpression(OLangParser::FilterExpressionContext * /*ctx*/) override { }
  virtual void exitFilterExpression(OLangParser::FilterExpressionContext * /*ctx*/) override { }

  virtual void enterReduceExpression(OLangParser::ReduceExpressionContext * /*ctx*/) override { }
  virtual void exitReduceExpression(OLangParser::ReduceExpressionContext * /*ctx*/) override { }

  virtual void enterForeachExpression(OLangParser::ForeachExpressionContext * /*ctx*/) override { }
  virtual void exitForeachExpression(OLangParser::ForeachExpressionContext * /*ctx*/) override { }

  virtual void enterGroupByExpression(OLangParser::GroupByExpressionContext * /*ctx*/) override { }
  virtual void exitGroupByExpression(OLangParser::GroupByExpressionContext * /*ctx*/) override { }

  virtual void enterFlatMapExpression(OLangParser::FlatMapExpressionContext * /*ctx*/) override { }
  virtual void exitFlatMapExpression(OLangParser::FlatMapExpressionContext * /*ctx*/) override { }

  virtual void enterZipExpression(OLangParser::ZipExpressionContext * /*ctx*/) override { }
  virtual void exitZipExpression(OLangParser::ZipExpressionContext * /*ctx*/) override { }

  virtual void enterPartitionExpression(OLangParser::PartitionExpressionContext * /*ctx*/) override { }
  virtual void exitPartitionExpression(OLangParser::PartitionExpressionContext * /*ctx*/) override { }

  virtual void enterTakeExpression(OLangParser::TakeExpressionContext * /*ctx*/) override { }
  virtual void exitTakeExpression(OLangParser::TakeExpressionContext * /*ctx*/) override { }

  virtual void enterDropExpression(OLangParser::DropExpressionContext * /*ctx*/) override { }
  virtual void exitDropExpression(OLangParser::DropExpressionContext * /*ctx*/) override { }

  virtual void enterTakeWhileExpression(OLangParser::TakeWhileExpressionContext * /*ctx*/) override { }
  virtual void exitTakeWhileExpression(OLangParser::TakeWhileExpressionContext * /*ctx*/) override { }

  virtual void enterDropWhileExpression(OLangParser::DropWhileExpressionContext * /*ctx*/) override { }
  virtual void exitDropWhileExpression(OLangParser::DropWhileExpressionContext * /*ctx*/) override { }

  virtual void enterSortByExpression(OLangParser::SortByExpressionContext * /*ctx*/) override { }
  virtual void exitSortByExpression(OLangParser::SortByExpressionContext * /*ctx*/) override { }

  virtual void enterDistinctExpression(OLangParser::DistinctExpressionContext * /*ctx*/) override { }
  virtual void exitDistinctExpression(OLangParser::DistinctExpressionContext * /*ctx*/) override { }

  virtual void enterCountExpression(OLangParser::CountExpressionContext * /*ctx*/) override { }
  virtual void exitCountExpression(OLangParser::CountExpressionContext * /*ctx*/) override { }

  virtual void enterFindExpression(OLangParser::FindExpressionContext * /*ctx*/) override { }
  virtual void exitFindExpression(OLangParser::FindExpressionContext * /*ctx*/) override { }

  virtual void enterAnyExpression(OLangParser::AnyExpressionContext * /*ctx*/) override { }
  virtual void exitAnyExpression(OLangParser::AnyExpressionContext * /*ctx*/) override { }

  virtual void enterAllExpression(OLangParser::AllExpressionContext * /*ctx*/) override { }
  virtual void exitAllExpression(OLangParser::AllExpressionContext * /*ctx*/) override { }

  virtual void enterJoinExpression(OLangParser::JoinExpressionContext * /*ctx*/) override { }
  virtual void exitJoinExpression(OLangParser::JoinExpressionContext * /*ctx*/) override { }

  virtual void enterJoinClause(OLangParser::JoinClauseContext * /*ctx*/) override { }
  virtual void exitJoinClause(OLangParser::JoinClauseContext * /*ctx*/) override { }

  virtual void enterWindowExpression(OLangParser::WindowExpressionContext * /*ctx*/) override { }
  virtual void exitWindowExpression(OLangParser::WindowExpressionContext * /*ctx*/) override { }

  virtual void enterChunkExpression(OLangParser::ChunkExpressionContext * /*ctx*/) override { }
  virtual void exitChunkExpression(OLangParser::ChunkExpressionContext * /*ctx*/) override { }

  virtual void enterScanExpression(OLangParser::ScanExpressionContext * /*ctx*/) override { }
  virtual void exitScanExpression(OLangParser::ScanExpressionContext * /*ctx*/) override { }

  virtual void enterCollectExpression(OLangParser::CollectExpressionContext * /*ctx*/) override { }
  virtual void exitCollectExpression(OLangParser::CollectExpressionContext * /*ctx*/) override { }

  virtual void enterLambdaExpression(OLangParser::LambdaExpressionContext * /*ctx*/) override { }
  virtual void exitLambdaExpression(OLangParser::LambdaExpressionContext * /*ctx*/) override { }

  virtual void enterMultipleParameterLambda(OLangParser::MultipleParameterLambdaContext * /*ctx*/) override { }
  virtual void exitMultipleParameterLambda(OLangParser::MultipleParameterLambdaContext * /*ctx*/) override { }

  virtual void enterParameterList(OLangParser::ParameterListContext * /*ctx*/) override { }
  virtual void exitParameterList(OLangParser::ParameterListContext * /*ctx*/) override { }

  virtual void enterParameter(OLangParser::ParameterContext * /*ctx*/) override { }
  virtual void exitParameter(OLangParser::ParameterContext * /*ctx*/) override { }

  virtual void enterSimplePatternLambda(OLangParser::SimplePatternLambdaContext * /*ctx*/) override { }
  virtual void exitSimplePatternLambda(OLangParser::SimplePatternLambdaContext * /*ctx*/) override { }

  virtual void enterSimpleDestructure(OLangParser::SimpleDestructureContext * /*ctx*/) override { }
  virtual void exitSimpleDestructure(OLangParser::SimpleDestructureContext * /*ctx*/) override { }

  virtual void enterSimpleLambda(OLangParser::SimpleLambdaContext * /*ctx*/) override { }
  virtual void exitSimpleLambda(OLangParser::SimpleLambdaContext * /*ctx*/) override { }

  virtual void enterSimplePatternList(OLangParser::SimplePatternListContext * /*ctx*/) override { }
  virtual void exitSimplePatternList(OLangParser::SimplePatternListContext * /*ctx*/) override { }

  virtual void enterSimplePatternFieldList(OLangParser::SimplePatternFieldListContext * /*ctx*/) override { }
  virtual void exitSimplePatternFieldList(OLangParser::SimplePatternFieldListContext * /*ctx*/) override { }

  virtual void enterSimplePatternElement(OLangParser::SimplePatternElementContext * /*ctx*/) override { }
  virtual void exitSimplePatternElement(OLangParser::SimplePatternElementContext * /*ctx*/) override { }

  virtual void enterSimplePatternField(OLangParser::SimplePatternFieldContext * /*ctx*/) override { }
  virtual void exitSimplePatternField(OLangParser::SimplePatternFieldContext * /*ctx*/) override { }

  virtual void enterBlockExpression(OLangParser::BlockExpressionContext * /*ctx*/) override { }
  virtual void exitBlockExpression(OLangParser::BlockExpressionContext * /*ctx*/) override { }

  virtual void enterTransformationList(OLangParser::TransformationListContext * /*ctx*/) override { }
  virtual void exitTransformationList(OLangParser::TransformationListContext * /*ctx*/) override { }

  virtual void enterTransformation(OLangParser::TransformationContext * /*ctx*/) override { }
  virtual void exitTransformation(OLangParser::TransformationContext * /*ctx*/) override { }

  virtual void enterMatchExpression(OLangParser::MatchExpressionContext * /*ctx*/) override { }
  virtual void exitMatchExpression(OLangParser::MatchExpressionContext * /*ctx*/) override { }

  virtual void enterMatchArm(OLangParser::MatchArmContext * /*ctx*/) override { }
  virtual void exitMatchArm(OLangParser::MatchArmContext * /*ctx*/) override { }

  virtual void enterMatchArmList(OLangParser::MatchArmListContext * /*ctx*/) override { }
  virtual void exitMatchArmList(OLangParser::MatchArmListContext * /*ctx*/) override { }

  virtual void enterPattern(OLangParser::PatternContext * /*ctx*/) override { }
  virtual void exitPattern(OLangParser::PatternContext * /*ctx*/) override { }

  virtual void enterOrPattern(OLangParser::OrPatternContext * /*ctx*/) override { }
  virtual void exitOrPattern(OLangParser::OrPatternContext * /*ctx*/) override { }

  virtual void enterAndPattern(OLangParser::AndPatternContext * /*ctx*/) override { }
  virtual void exitAndPattern(OLangParser::AndPatternContext * /*ctx*/) override { }

  virtual void enterPrimaryPattern(OLangParser::PrimaryPatternContext * /*ctx*/) override { }
  virtual void exitPrimaryPattern(OLangParser::PrimaryPatternContext * /*ctx*/) override { }

  virtual void enterWildcardPattern(OLangParser::WildcardPatternContext * /*ctx*/) override { }
  virtual void exitWildcardPattern(OLangParser::WildcardPatternContext * /*ctx*/) override { }

  virtual void enterLiteralPattern(OLangParser::LiteralPatternContext * /*ctx*/) override { }
  virtual void exitLiteralPattern(OLangParser::LiteralPatternContext * /*ctx*/) override { }

  virtual void enterIdentifierPattern(OLangParser::IdentifierPatternContext * /*ctx*/) override { }
  virtual void exitIdentifierPattern(OLangParser::IdentifierPatternContext * /*ctx*/) override { }

  virtual void enterDestructurePattern(OLangParser::DestructurePatternContext * /*ctx*/) override { }
  virtual void exitDestructurePattern(OLangParser::DestructurePatternContext * /*ctx*/) override { }

  virtual void enterObjectDestructure(OLangParser::ObjectDestructureContext * /*ctx*/) override { }
  virtual void exitObjectDestructure(OLangParser::ObjectDestructureContext * /*ctx*/) override { }

  virtual void enterListDestructure(OLangParser::ListDestructureContext * /*ctx*/) override { }
  virtual void exitListDestructure(OLangParser::ListDestructureContext * /*ctx*/) override { }

  virtual void enterTupleDestructure(OLangParser::TupleDestructureContext * /*ctx*/) override { }
  virtual void exitTupleDestructure(OLangParser::TupleDestructureContext * /*ctx*/) override { }

  virtual void enterNamedDestructure(OLangParser::NamedDestructureContext * /*ctx*/) override { }
  virtual void exitNamedDestructure(OLangParser::NamedDestructureContext * /*ctx*/) override { }

  virtual void enterRangePattern(OLangParser::RangePatternContext * /*ctx*/) override { }
  virtual void exitRangePattern(OLangParser::RangePatternContext * /*ctx*/) override { }

  virtual void enterSimpleRangeValue(OLangParser::SimpleRangeValueContext * /*ctx*/) override { }
  virtual void exitSimpleRangeValue(OLangParser::SimpleRangeValueContext * /*ctx*/) override { }

  virtual void enterTypePattern(OLangParser::TypePatternContext * /*ctx*/) override { }
  virtual void exitTypePattern(OLangParser::TypePatternContext * /*ctx*/) override { }

  virtual void enterSimplePattern(OLangParser::SimplePatternContext * /*ctx*/) override { }
  virtual void exitSimplePattern(OLangParser::SimplePatternContext * /*ctx*/) override { }

  virtual void enterGuardPattern(OLangParser::GuardPatternContext * /*ctx*/) override { }
  virtual void exitGuardPattern(OLangParser::GuardPatternContext * /*ctx*/) override { }

  virtual void enterSimpleCondition(OLangParser::SimpleConditionContext * /*ctx*/) override { }
  virtual void exitSimpleCondition(OLangParser::SimpleConditionContext * /*ctx*/) override { }

  virtual void enterParenthesisPattern(OLangParser::ParenthesisPatternContext * /*ctx*/) override { }
  virtual void exitParenthesisPattern(OLangParser::ParenthesisPatternContext * /*ctx*/) override { }

  virtual void enterPatternField(OLangParser::PatternFieldContext * /*ctx*/) override { }
  virtual void exitPatternField(OLangParser::PatternFieldContext * /*ctx*/) override { }

  virtual void enterPatternFieldList(OLangParser::PatternFieldListContext * /*ctx*/) override { }
  virtual void exitPatternFieldList(OLangParser::PatternFieldListContext * /*ctx*/) override { }

  virtual void enterPatternList(OLangParser::PatternListContext * /*ctx*/) override { }
  virtual void exitPatternList(OLangParser::PatternListContext * /*ctx*/) override { }

  virtual void enterMutationExpression(OLangParser::MutationExpressionContext * /*ctx*/) override { }
  virtual void exitMutationExpression(OLangParser::MutationExpressionContext * /*ctx*/) override { }

  virtual void enterMutationSite(OLangParser::MutationSiteContext * /*ctx*/) override { }
  virtual void exitMutationSite(OLangParser::MutationSiteContext * /*ctx*/) override { }

  virtual void enterMutationChange(OLangParser::MutationChangeContext * /*ctx*/) override { }
  virtual void exitMutationChange(OLangParser::MutationChangeContext * /*ctx*/) override { }

  virtual void enterRangeExpression(OLangParser::RangeExpressionContext * /*ctx*/) override { }
  virtual void exitRangeExpression(OLangParser::RangeExpressionContext * /*ctx*/) override { }

  virtual void enterListExpression(OLangParser::ListExpressionContext * /*ctx*/) override { }
  virtual void exitListExpression(OLangParser::ListExpressionContext * /*ctx*/) override { }

  virtual void enterObjectExpression(OLangParser::ObjectExpressionContext * /*ctx*/) override { }
  virtual void exitObjectExpression(OLangParser::ObjectExpressionContext * /*ctx*/) override { }

  virtual void enterObjectField(OLangParser::ObjectFieldContext * /*ctx*/) override { }
  virtual void exitObjectField(OLangParser::ObjectFieldContext * /*ctx*/) override { }

  virtual void enterObjectFieldList(OLangParser::ObjectFieldListContext * /*ctx*/) override { }
  virtual void exitObjectFieldList(OLangParser::ObjectFieldListContext * /*ctx*/) override { }

  virtual void enterAssignmentStatement(OLangParser::AssignmentStatementContext * /*ctx*/) override { }
  virtual void exitAssignmentStatement(OLangParser::AssignmentStatementContext * /*ctx*/) override { }

  virtual void enterAnnotationPairList(OLangParser::AnnotationPairListContext * /*ctx*/) override { }
  virtual void exitAnnotationPairList(OLangParser::AnnotationPairListContext * /*ctx*/) override { }

  virtual void enterAnnotationPair(OLangParser::AnnotationPairContext * /*ctx*/) override { }
  virtual void exitAnnotationPair(OLangParser::AnnotationPairContext * /*ctx*/) override { }

  virtual void enterAnnotationValue(OLangParser::AnnotationValueContext * /*ctx*/) override { }
  virtual void exitAnnotationValue(OLangParser::AnnotationValueContext * /*ctx*/) override { }

  virtual void enterListLiteral(OLangParser::ListLiteralContext * /*ctx*/) override { }
  virtual void exitListLiteral(OLangParser::ListLiteralContext * /*ctx*/) override { }

  virtual void enterAnnotationValueList(OLangParser::AnnotationValueListContext * /*ctx*/) override { }
  virtual void exitAnnotationValueList(OLangParser::AnnotationValueListContext * /*ctx*/) override { }

  virtual void enterQualifiedName(OLangParser::QualifiedNameContext * /*ctx*/) override { }
  virtual void exitQualifiedName(OLangParser::QualifiedNameContext * /*ctx*/) override { }

  virtual void enterLiteralValue(OLangParser::LiteralValueContext * /*ctx*/) override { }
  virtual void exitLiteralValue(OLangParser::LiteralValueContext * /*ctx*/) override { }

  virtual void enterExpressionList(OLangParser::ExpressionListContext * /*ctx*/) override { }
  virtual void exitExpressionList(OLangParser::ExpressionListContext * /*ctx*/) override { }

  virtual void enterIdList(OLangParser::IdListContext * /*ctx*/) override { }
  virtual void exitIdList(OLangParser::IdListContext * /*ctx*/) override { }

  virtual void enterArgument(OLangParser::ArgumentContext * /*ctx*/) override { }
  virtual void exitArgument(OLangParser::ArgumentContext * /*ctx*/) override { }

  virtual void enterLambdaArgumentRule(OLangParser::LambdaArgumentRuleContext * /*ctx*/) override { }
  virtual void exitLambdaArgumentRule(OLangParser::LambdaArgumentRuleContext * /*ctx*/) override { }

  virtual void enterArgumentList(OLangParser::ArgumentListContext * /*ctx*/) override { }
  virtual void exitArgumentList(OLangParser::ArgumentListContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};

