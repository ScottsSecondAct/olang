
// Generated from /home/scott/Projects/olang/grammar/OLangParser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "OLangParserVisitor.h"


/**
 * This class provides an empty implementation of OLangParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  OLangParserBaseVisitor : public OLangParserVisitor {
public:

  virtual std::any visitProgram(OLangParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatementList(OLangParser::StatementListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(OLangParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionStatement(OLangParser::ExpressionStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEmitStatement(OLangParser::EmitStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSignalStatement(OLangParser::SignalStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssertStatement(OLangParser::AssertStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDeclaration(OLangParser::DeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAgentDeclaration(OLangParser::AgentDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAgentMember(OLangParser::AgentMemberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSolverDeclaration(OLangParser::SolverDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSolverMember(OLangParser::SolverMemberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProofDeclaration(OLangParser::ProofDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitInvariantDeclaration(OLangParser::InvariantDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportDeclaration(OLangParser::ImportDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDottedAsNamesList(OLangParser::DottedAsNamesListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDottedAsNames(OLangParser::DottedAsNamesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelativeModule(OLangParser::RelativeModuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportTargets(OLangParser::ImportTargetsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitImportAsNames(OLangParser::ImportAsNamesContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBindingDeclaration(OLangParser::BindingDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionDeclaration(OLangParser::FunctionDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPipelineDeclaration(OLangParser::PipelineDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeDeclaration(OLangParser::TypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotationTypeDeclaration(OLangParser::AnnotationTypeDeclarationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotationStatement(OLangParser::AnnotationStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpression(OLangParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPipelineExpression(OLangParser::PipelineExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPipelineBody(OLangParser::PipelineBodyContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNullCoalesceExpression(OLangParser::NullCoalesceExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTernaryExpression(OLangParser::TernaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOrExpression(OLangParser::LogicalOrExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalAndExpression(OLangParser::LogicalAndExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitEqualityExpression(OLangParser::EqualityExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRelationalExpression(OLangParser::RelationalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditiveExpression(OLangParser::AdditiveExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicativeExpression(OLangParser::MultiplicativeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUnaryExpression(OLangParser::UnaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitErrorPropagationExpression(OLangParser::ErrorPropagationExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPostfixExpression(OLangParser::PostfixExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallSuffix(OLangParser::CallSuffixContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCallArguments(OLangParser::CallArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryExpression(OLangParser::PrimaryExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitType(OLangParser::TypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOptionalType(OLangParser::OptionalTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBaseType(OLangParser::BaseTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimitiveType(OLangParser::PrimitiveTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitUserDefinedType(OLangParser::UserDefinedTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPipelineType(OLangParser::PipelineTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitListType(OLangParser::ListTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMapType(OLangParser::MapTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSetType(OLangParser::SetTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStreamType(OLangParser::StreamTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFutureType(OLangParser::FutureTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitResultType(OLangParser::ResultTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOptionType(OLangParser::OptionTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitProvenanceType(OLangParser::ProvenanceTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionType(OLangParser::FunctionTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenthesisType(OLangParser::ParenthesisTypeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericArguments(OLangParser::GenericArgumentsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypeList(OLangParser::TypeListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericParameters(OLangParser::GenericParametersContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericParameterList(OLangParser::GenericParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericParameter(OLangParser::GenericParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGenericParameterConstraint(OLangParser::GenericParameterConstraintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWhereClause(OLangParser::WhereClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstraintList(OLangParser::ConstraintListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitConstraint(OLangParser::ConstraintContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypedField(OLangParser::TypedFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypedFieldList(OLangParser::TypedFieldListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypedParameter(OLangParser::TypedParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypedParameterList(OLangParser::TypedParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionalExpression(OLangParser::FunctionalExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMapExpression(OLangParser::MapExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFilterExpression(OLangParser::FilterExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitReduceExpression(OLangParser::ReduceExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitForeachExpression(OLangParser::ForeachExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGroupByExpression(OLangParser::GroupByExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlatMapExpression(OLangParser::FlatMapExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitZipExpression(OLangParser::ZipExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPartitionExpression(OLangParser::PartitionExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTakeExpression(OLangParser::TakeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDropExpression(OLangParser::DropExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTakeWhileExpression(OLangParser::TakeWhileExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDropWhileExpression(OLangParser::DropWhileExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSortByExpression(OLangParser::SortByExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDistinctExpression(OLangParser::DistinctExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCountExpression(OLangParser::CountExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFindExpression(OLangParser::FindExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnyExpression(OLangParser::AnyExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAllExpression(OLangParser::AllExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJoinExpression(OLangParser::JoinExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitJoinClause(OLangParser::JoinClauseContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWindowExpression(OLangParser::WindowExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChunkExpression(OLangParser::ChunkExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitScanExpression(OLangParser::ScanExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCollectExpression(OLangParser::CollectExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLambdaExpression(OLangParser::LambdaExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultipleParameterLambda(OLangParser::MultipleParameterLambdaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameterList(OLangParser::ParameterListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParameter(OLangParser::ParameterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimplePatternLambda(OLangParser::SimplePatternLambdaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleDestructure(OLangParser::SimpleDestructureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleLambda(OLangParser::SimpleLambdaContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimplePatternList(OLangParser::SimplePatternListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimplePatternFieldList(OLangParser::SimplePatternFieldListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimplePatternElement(OLangParser::SimplePatternElementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimplePatternField(OLangParser::SimplePatternFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBlockExpression(OLangParser::BlockExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTransformationList(OLangParser::TransformationListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTransformation(OLangParser::TransformationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMatchExpression(OLangParser::MatchExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMatchArm(OLangParser::MatchArmContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMatchArmList(OLangParser::MatchArmListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPattern(OLangParser::PatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitOrPattern(OLangParser::OrPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAndPattern(OLangParser::AndPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPrimaryPattern(OLangParser::PrimaryPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitWildcardPattern(OLangParser::WildcardPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralPattern(OLangParser::LiteralPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifierPattern(OLangParser::IdentifierPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDestructurePattern(OLangParser::DestructurePatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjectDestructure(OLangParser::ObjectDestructureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitListDestructure(OLangParser::ListDestructureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTupleDestructure(OLangParser::TupleDestructureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNamedDestructure(OLangParser::NamedDestructureContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRangePattern(OLangParser::RangePatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleRangeValue(OLangParser::SimpleRangeValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTypePattern(OLangParser::TypePatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimplePattern(OLangParser::SimplePatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitGuardPattern(OLangParser::GuardPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSimpleCondition(OLangParser::SimpleConditionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParenthesisPattern(OLangParser::ParenthesisPatternContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPatternField(OLangParser::PatternFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPatternFieldList(OLangParser::PatternFieldListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitPatternList(OLangParser::PatternListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMutationExpression(OLangParser::MutationExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMutationSite(OLangParser::MutationSiteContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMutationChange(OLangParser::MutationChangeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRangeExpression(OLangParser::RangeExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitListExpression(OLangParser::ListExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjectExpression(OLangParser::ObjectExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjectField(OLangParser::ObjectFieldContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitObjectFieldList(OLangParser::ObjectFieldListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignmentStatement(OLangParser::AssignmentStatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotationPairList(OLangParser::AnnotationPairListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotationPair(OLangParser::AnnotationPairContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotationValue(OLangParser::AnnotationValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitListLiteral(OLangParser::ListLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAnnotationValueList(OLangParser::AnnotationValueListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitQualifiedName(OLangParser::QualifiedNameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteralValue(OLangParser::LiteralValueContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExpressionList(OLangParser::ExpressionListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdList(OLangParser::IdListContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgument(OLangParser::ArgumentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLambdaArgumentRule(OLangParser::LambdaArgumentRuleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgumentList(OLangParser::ArgumentListContext *ctx) override {
    return visitChildren(ctx);
  }


};

