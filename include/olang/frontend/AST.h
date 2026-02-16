#pragma once
#include <cstdint>
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/StringRef.h"
#include "olang/frontend/SourceLocation.h"

namespace olang::ast {

enum class NodeKind : uint16_t {
  Program, StatementList,
  ImportDecl, BindingDecl, FunctionDecl, PipelineDecl,
  TypeDecl, AnnotationTypeDecl, AnnotationStmt,
  AgentDecl, SolverDecl, ProofDecl, InvariantDecl,
  ExprStmt, EmitStmt, SignalStmt, AssertStmt, AssignStmt,
  LambdaExpr, BlockExpr, MatchExpr, MatchArm,
  PipelineExpr, ParallelExpr,
  NullCoalesceExpr, TernaryExpr,
  BinaryExpr, UnaryExpr,
  CallExpr, MemberAccessExpr, IndexExpr,
  ListExpr, ObjectExpr, StreamExpr,
  MutationExpr, RangeExpr,
  MapExpr, FilterExpr, ReduceExpr, ForeachExpr,
  GroupByExpr, FlatMapExpr, ZipExpr, PartitionExpr,
  TakeExpr, DropExpr, SortByExpr, DistinctExpr,
  CountExpr, FindExpr, AnyExpr, AllExpr,
  JoinExpr, WindowExpr, ChunkExpr, ScanExpr, CollectExpr,
  AlwaysExpr, EventuallyExpr, DuringExpr, UntilExpr, WithinExpr,
  BoolLit, IntLit, FloatLit, StringLit, NullLit,
  WildcardPat, LiteralPat, IdentPat,
  ObjectDestructPat, ListDestructPat, TuplePat, NamedPat,
  RangePat, TypePat, GuardPat,
  PrimitiveType, UserDefinedType, PipelineType,
  ListType, MapType, SetType, StreamType,
  FutureType, ResultType, OptionType, ProvenanceType,
  FunctionType, OptionalType, UnionType,
};

class ASTNode {
public:
  explicit ASTNode(NodeKind kind, SourceLocation loc) noexcept
      : kind_(kind), loc_(loc) {}
  [[nodiscard]] NodeKind       kind() const noexcept { return kind_; }
  [[nodiscard]] SourceLocation loc()  const noexcept { return loc_;  }
protected:
  NodeKind kind_;
  SourceLocation loc_;
};

// Forward declarations of concrete node types
namespace types { class Type; }

class Expr : public ASTNode {
public:
  using ASTNode::ASTNode;
  [[nodiscard]] const types::Type* resolvedType() const noexcept { return type_; }
  void setResolvedType(const types::Type* t) noexcept { type_ = t; }
private:
  const types::Type* type_{nullptr};
};

class Stmt : public ASTNode { public: using ASTNode::ASTNode; };

class Decl : public Stmt {
public:
  Decl(NodeKind k, SourceLocation l, llvm::StringRef n) noexcept
      : Stmt(k,l), name_(n) {}
  [[nodiscard]] llvm::StringRef name() const noexcept { return name_; }
private:
  llvm::StringRef name_;
};

struct PipelineExprNode : Expr {
  Expr* lhs{nullptr}; Expr* rhs{nullptr}; bool isParallel{false};
  using Expr::Expr;
};

struct TemporalExprNode : Expr { Expr* operand{nullptr}; using Expr::Expr; };
struct AgentDeclNode    : Decl { using Decl::Decl; };
struct SolverDeclNode   : Decl { using Decl::Decl; };
struct ProofDeclNode    : Decl { using Decl::Decl; };
struct InvariantDeclNode: Decl { using Decl::Decl; };

struct MatchExprNode : Expr {
  Expr* subject{nullptr};
  llvm::ArrayRef<struct MatchArmNode*> arms;
  using Expr::Expr;
};
struct MatchArmNode : ASTNode {
  ASTNode* pattern{nullptr}; Expr* body{nullptr};
  using ASTNode::ASTNode;
};

} // namespace olang::ast
