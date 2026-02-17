
// Generated from /home/scott/Projects/olang/grammar/OLangParser.g4 by ANTLR 4.11.1

#pragma once


#include "antlr4-runtime.h"
#include "OLangParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by OLangParser.
 */
class  OLangParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by OLangParser.
   */
    virtual std::any visitProgram(OLangParser::ProgramContext *context) = 0;

    virtual std::any visitStatementList(OLangParser::StatementListContext *context) = 0;

    virtual std::any visitStatement(OLangParser::StatementContext *context) = 0;

    virtual std::any visitExpressionStatement(OLangParser::ExpressionStatementContext *context) = 0;

    virtual std::any visitEmitStatement(OLangParser::EmitStatementContext *context) = 0;

    virtual std::any visitSignalStatement(OLangParser::SignalStatementContext *context) = 0;

    virtual std::any visitAssertStatement(OLangParser::AssertStatementContext *context) = 0;

    virtual std::any visitDeclaration(OLangParser::DeclarationContext *context) = 0;

    virtual std::any visitAgentDeclaration(OLangParser::AgentDeclarationContext *context) = 0;

    virtual std::any visitAgentMember(OLangParser::AgentMemberContext *context) = 0;

    virtual std::any visitSolverDeclaration(OLangParser::SolverDeclarationContext *context) = 0;

    virtual std::any visitSolverMember(OLangParser::SolverMemberContext *context) = 0;

    virtual std::any visitProofDeclaration(OLangParser::ProofDeclarationContext *context) = 0;

    virtual std::any visitInvariantDeclaration(OLangParser::InvariantDeclarationContext *context) = 0;

    virtual std::any visitImportDeclaration(OLangParser::ImportDeclarationContext *context) = 0;

    virtual std::any visitDottedAsNamesList(OLangParser::DottedAsNamesListContext *context) = 0;

    virtual std::any visitDottedAsNames(OLangParser::DottedAsNamesContext *context) = 0;

    virtual std::any visitRelativeModule(OLangParser::RelativeModuleContext *context) = 0;

    virtual std::any visitImportTargets(OLangParser::ImportTargetsContext *context) = 0;

    virtual std::any visitImportAsNames(OLangParser::ImportAsNamesContext *context) = 0;

    virtual std::any visitBindingDeclaration(OLangParser::BindingDeclarationContext *context) = 0;

    virtual std::any visitFunctionDeclaration(OLangParser::FunctionDeclarationContext *context) = 0;

    virtual std::any visitPipelineDeclaration(OLangParser::PipelineDeclarationContext *context) = 0;

    virtual std::any visitTypeDeclaration(OLangParser::TypeDeclarationContext *context) = 0;

    virtual std::any visitAnnotationTypeDeclaration(OLangParser::AnnotationTypeDeclarationContext *context) = 0;

    virtual std::any visitAnnotationStatement(OLangParser::AnnotationStatementContext *context) = 0;

    virtual std::any visitExpression(OLangParser::ExpressionContext *context) = 0;

    virtual std::any visitPipelineExpression(OLangParser::PipelineExpressionContext *context) = 0;

    virtual std::any visitPipelineBody(OLangParser::PipelineBodyContext *context) = 0;

    virtual std::any visitNullCoalesceExpression(OLangParser::NullCoalesceExpressionContext *context) = 0;

    virtual std::any visitTernaryExpression(OLangParser::TernaryExpressionContext *context) = 0;

    virtual std::any visitLogicalOrExpression(OLangParser::LogicalOrExpressionContext *context) = 0;

    virtual std::any visitLogicalAndExpression(OLangParser::LogicalAndExpressionContext *context) = 0;

    virtual std::any visitEqualityExpression(OLangParser::EqualityExpressionContext *context) = 0;

    virtual std::any visitRelationalExpression(OLangParser::RelationalExpressionContext *context) = 0;

    virtual std::any visitAdditiveExpression(OLangParser::AdditiveExpressionContext *context) = 0;

    virtual std::any visitMultiplicativeExpression(OLangParser::MultiplicativeExpressionContext *context) = 0;

    virtual std::any visitUnaryExpression(OLangParser::UnaryExpressionContext *context) = 0;

    virtual std::any visitErrorPropagationExpression(OLangParser::ErrorPropagationExpressionContext *context) = 0;

    virtual std::any visitPostfixExpression(OLangParser::PostfixExpressionContext *context) = 0;

    virtual std::any visitCallSuffix(OLangParser::CallSuffixContext *context) = 0;

    virtual std::any visitCallArguments(OLangParser::CallArgumentsContext *context) = 0;

    virtual std::any visitPrimaryExpression(OLangParser::PrimaryExpressionContext *context) = 0;

    virtual std::any visitType(OLangParser::TypeContext *context) = 0;

    virtual std::any visitOptionalType(OLangParser::OptionalTypeContext *context) = 0;

    virtual std::any visitBaseType(OLangParser::BaseTypeContext *context) = 0;

    virtual std::any visitPrimitiveType(OLangParser::PrimitiveTypeContext *context) = 0;

    virtual std::any visitUserDefinedType(OLangParser::UserDefinedTypeContext *context) = 0;

    virtual std::any visitPipelineType(OLangParser::PipelineTypeContext *context) = 0;

    virtual std::any visitListType(OLangParser::ListTypeContext *context) = 0;

    virtual std::any visitMapType(OLangParser::MapTypeContext *context) = 0;

    virtual std::any visitSetType(OLangParser::SetTypeContext *context) = 0;

    virtual std::any visitStreamType(OLangParser::StreamTypeContext *context) = 0;

    virtual std::any visitFutureType(OLangParser::FutureTypeContext *context) = 0;

    virtual std::any visitResultType(OLangParser::ResultTypeContext *context) = 0;

    virtual std::any visitOptionType(OLangParser::OptionTypeContext *context) = 0;

    virtual std::any visitProvenanceType(OLangParser::ProvenanceTypeContext *context) = 0;

    virtual std::any visitFunctionType(OLangParser::FunctionTypeContext *context) = 0;

    virtual std::any visitParenthesisType(OLangParser::ParenthesisTypeContext *context) = 0;

    virtual std::any visitGenericArguments(OLangParser::GenericArgumentsContext *context) = 0;

    virtual std::any visitTypeList(OLangParser::TypeListContext *context) = 0;

    virtual std::any visitGenericParameters(OLangParser::GenericParametersContext *context) = 0;

    virtual std::any visitGenericParameterList(OLangParser::GenericParameterListContext *context) = 0;

    virtual std::any visitGenericParameter(OLangParser::GenericParameterContext *context) = 0;

    virtual std::any visitGenericParameterConstraint(OLangParser::GenericParameterConstraintContext *context) = 0;

    virtual std::any visitWhereClause(OLangParser::WhereClauseContext *context) = 0;

    virtual std::any visitConstraintList(OLangParser::ConstraintListContext *context) = 0;

    virtual std::any visitConstraint(OLangParser::ConstraintContext *context) = 0;

    virtual std::any visitTypedField(OLangParser::TypedFieldContext *context) = 0;

    virtual std::any visitTypedFieldList(OLangParser::TypedFieldListContext *context) = 0;

    virtual std::any visitTypedParameter(OLangParser::TypedParameterContext *context) = 0;

    virtual std::any visitTypedParameterList(OLangParser::TypedParameterListContext *context) = 0;

    virtual std::any visitFunctionalExpression(OLangParser::FunctionalExpressionContext *context) = 0;

    virtual std::any visitMapExpression(OLangParser::MapExpressionContext *context) = 0;

    virtual std::any visitFilterExpression(OLangParser::FilterExpressionContext *context) = 0;

    virtual std::any visitReduceExpression(OLangParser::ReduceExpressionContext *context) = 0;

    virtual std::any visitForeachExpression(OLangParser::ForeachExpressionContext *context) = 0;

    virtual std::any visitGroupByExpression(OLangParser::GroupByExpressionContext *context) = 0;

    virtual std::any visitFlatMapExpression(OLangParser::FlatMapExpressionContext *context) = 0;

    virtual std::any visitZipExpression(OLangParser::ZipExpressionContext *context) = 0;

    virtual std::any visitPartitionExpression(OLangParser::PartitionExpressionContext *context) = 0;

    virtual std::any visitTakeExpression(OLangParser::TakeExpressionContext *context) = 0;

    virtual std::any visitDropExpression(OLangParser::DropExpressionContext *context) = 0;

    virtual std::any visitTakeWhileExpression(OLangParser::TakeWhileExpressionContext *context) = 0;

    virtual std::any visitDropWhileExpression(OLangParser::DropWhileExpressionContext *context) = 0;

    virtual std::any visitSortByExpression(OLangParser::SortByExpressionContext *context) = 0;

    virtual std::any visitDistinctExpression(OLangParser::DistinctExpressionContext *context) = 0;

    virtual std::any visitCountExpression(OLangParser::CountExpressionContext *context) = 0;

    virtual std::any visitFindExpression(OLangParser::FindExpressionContext *context) = 0;

    virtual std::any visitAnyExpression(OLangParser::AnyExpressionContext *context) = 0;

    virtual std::any visitAllExpression(OLangParser::AllExpressionContext *context) = 0;

    virtual std::any visitJoinExpression(OLangParser::JoinExpressionContext *context) = 0;

    virtual std::any visitJoinClause(OLangParser::JoinClauseContext *context) = 0;

    virtual std::any visitWindowExpression(OLangParser::WindowExpressionContext *context) = 0;

    virtual std::any visitChunkExpression(OLangParser::ChunkExpressionContext *context) = 0;

    virtual std::any visitScanExpression(OLangParser::ScanExpressionContext *context) = 0;

    virtual std::any visitCollectExpression(OLangParser::CollectExpressionContext *context) = 0;

    virtual std::any visitLambdaExpression(OLangParser::LambdaExpressionContext *context) = 0;

    virtual std::any visitMultipleParameterLambda(OLangParser::MultipleParameterLambdaContext *context) = 0;

    virtual std::any visitParameterList(OLangParser::ParameterListContext *context) = 0;

    virtual std::any visitParameter(OLangParser::ParameterContext *context) = 0;

    virtual std::any visitSimplePatternLambda(OLangParser::SimplePatternLambdaContext *context) = 0;

    virtual std::any visitSimpleDestructure(OLangParser::SimpleDestructureContext *context) = 0;

    virtual std::any visitSimpleLambda(OLangParser::SimpleLambdaContext *context) = 0;

    virtual std::any visitSimplePatternList(OLangParser::SimplePatternListContext *context) = 0;

    virtual std::any visitSimplePatternFieldList(OLangParser::SimplePatternFieldListContext *context) = 0;

    virtual std::any visitSimplePatternElement(OLangParser::SimplePatternElementContext *context) = 0;

    virtual std::any visitSimplePatternField(OLangParser::SimplePatternFieldContext *context) = 0;

    virtual std::any visitBlockExpression(OLangParser::BlockExpressionContext *context) = 0;

    virtual std::any visitTransformationList(OLangParser::TransformationListContext *context) = 0;

    virtual std::any visitTransformation(OLangParser::TransformationContext *context) = 0;

    virtual std::any visitMatchExpression(OLangParser::MatchExpressionContext *context) = 0;

    virtual std::any visitMatchArm(OLangParser::MatchArmContext *context) = 0;

    virtual std::any visitMatchArmList(OLangParser::MatchArmListContext *context) = 0;

    virtual std::any visitPattern(OLangParser::PatternContext *context) = 0;

    virtual std::any visitOrPattern(OLangParser::OrPatternContext *context) = 0;

    virtual std::any visitAndPattern(OLangParser::AndPatternContext *context) = 0;

    virtual std::any visitPrimaryPattern(OLangParser::PrimaryPatternContext *context) = 0;

    virtual std::any visitWildcardPattern(OLangParser::WildcardPatternContext *context) = 0;

    virtual std::any visitLiteralPattern(OLangParser::LiteralPatternContext *context) = 0;

    virtual std::any visitIdentifierPattern(OLangParser::IdentifierPatternContext *context) = 0;

    virtual std::any visitDestructurePattern(OLangParser::DestructurePatternContext *context) = 0;

    virtual std::any visitObjectDestructure(OLangParser::ObjectDestructureContext *context) = 0;

    virtual std::any visitListDestructure(OLangParser::ListDestructureContext *context) = 0;

    virtual std::any visitTupleDestructure(OLangParser::TupleDestructureContext *context) = 0;

    virtual std::any visitNamedDestructure(OLangParser::NamedDestructureContext *context) = 0;

    virtual std::any visitRangePattern(OLangParser::RangePatternContext *context) = 0;

    virtual std::any visitSimpleRangeValue(OLangParser::SimpleRangeValueContext *context) = 0;

    virtual std::any visitTypePattern(OLangParser::TypePatternContext *context) = 0;

    virtual std::any visitSimplePattern(OLangParser::SimplePatternContext *context) = 0;

    virtual std::any visitGuardPattern(OLangParser::GuardPatternContext *context) = 0;

    virtual std::any visitSimpleCondition(OLangParser::SimpleConditionContext *context) = 0;

    virtual std::any visitParenthesisPattern(OLangParser::ParenthesisPatternContext *context) = 0;

    virtual std::any visitPatternField(OLangParser::PatternFieldContext *context) = 0;

    virtual std::any visitPatternFieldList(OLangParser::PatternFieldListContext *context) = 0;

    virtual std::any visitPatternList(OLangParser::PatternListContext *context) = 0;

    virtual std::any visitMutationExpression(OLangParser::MutationExpressionContext *context) = 0;

    virtual std::any visitMutationSite(OLangParser::MutationSiteContext *context) = 0;

    virtual std::any visitMutationChange(OLangParser::MutationChangeContext *context) = 0;

    virtual std::any visitRangeExpression(OLangParser::RangeExpressionContext *context) = 0;

    virtual std::any visitListExpression(OLangParser::ListExpressionContext *context) = 0;

    virtual std::any visitObjectExpression(OLangParser::ObjectExpressionContext *context) = 0;

    virtual std::any visitObjectField(OLangParser::ObjectFieldContext *context) = 0;

    virtual std::any visitObjectFieldList(OLangParser::ObjectFieldListContext *context) = 0;

    virtual std::any visitAssignmentStatement(OLangParser::AssignmentStatementContext *context) = 0;

    virtual std::any visitAnnotationPairList(OLangParser::AnnotationPairListContext *context) = 0;

    virtual std::any visitAnnotationPair(OLangParser::AnnotationPairContext *context) = 0;

    virtual std::any visitAnnotationValue(OLangParser::AnnotationValueContext *context) = 0;

    virtual std::any visitListLiteral(OLangParser::ListLiteralContext *context) = 0;

    virtual std::any visitAnnotationValueList(OLangParser::AnnotationValueListContext *context) = 0;

    virtual std::any visitQualifiedName(OLangParser::QualifiedNameContext *context) = 0;

    virtual std::any visitLiteralValue(OLangParser::LiteralValueContext *context) = 0;

    virtual std::any visitExpressionList(OLangParser::ExpressionListContext *context) = 0;

    virtual std::any visitIdList(OLangParser::IdListContext *context) = 0;

    virtual std::any visitArgument(OLangParser::ArgumentContext *context) = 0;

    virtual std::any visitLambdaArgumentRule(OLangParser::LambdaArgumentRuleContext *context) = 0;

    virtual std::any visitArgumentList(OLangParser::ArgumentListContext *context) = 0;


};

