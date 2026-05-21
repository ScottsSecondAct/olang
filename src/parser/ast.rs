use crate::lexer::Span;

// ── Source location ──────────────────────────────────────────────────────────

#[derive(Debug, Clone, Copy, PartialEq, Eq, Default)]
pub struct SourceLocation {
    pub line: u32,
    pub col: u32,
}

// ── Types ────────────────────────────────────────────────────────────────────

#[derive(Debug, Clone, PartialEq)]
pub enum PrimitiveKind {
    Int, Long, Float, Double, Bool, Char, String, Any, Never, Null,
}

#[derive(Debug, Clone, PartialEq)]
pub enum Type {
    Primitive(PrimitiveKind),
    UserDefined { name: String, type_args: Vec<Type> },
    Pipeline    { input: Box<Type>, output: Box<Type> },
    List(Box<Type>),
    Map         { key: Box<Type>, value: Box<Type> },
    Set(Box<Type>),
    Stream(Box<Type>),
    Future(Box<Type>),
    Result      { ok: Box<Type>, err: Box<Type> },
    Option(Box<Type>),
    Provenance(Box<Type>),
    Function    { params: Vec<Type>, ret: Box<Type> },
    Union(Vec<Type>),
    Optional(Box<Type>),
}

impl Type {
    pub fn is_primitive(&self) -> bool { matches!(self, Type::Primitive(_)) }
    pub fn is_optional(&self)  -> bool { matches!(self, Type::Optional(_)) }
    pub fn is_union(&self)     -> bool { matches!(self, Type::Union(_)) }

    pub fn to_display(&self) -> String {
        match self {
            Type::Primitive(k) => match k {
                PrimitiveKind::Int    => "int",
                PrimitiveKind::Long   => "long",
                PrimitiveKind::Float  => "float",
                PrimitiveKind::Double => "double",
                PrimitiveKind::Bool   => "bool",
                PrimitiveKind::Char   => "char",
                PrimitiveKind::String => "string",
                PrimitiveKind::Any    => "any_type",
                PrimitiveKind::Never  => "never_type",
                PrimitiveKind::Null   => "null",
            }.to_owned(),
            Type::UserDefined { name, type_args } => {
                if type_args.is_empty() {
                    name.clone()
                } else {
                    format!("{}<{}>", name, type_args.iter().map(|t| t.to_display()).collect::<Vec<_>>().join(", "))
                }
            }
            Type::Pipeline { input, output } =>
                format!("Pipeline<{} -> {}>", input.to_display(), output.to_display()),
            Type::List(e)        => format!("List<{}>", e.to_display()),
            Type::Map { key, value } =>
                format!("Map<{}, {}>", key.to_display(), value.to_display()),
            Type::Set(e)         => format!("Set<{}>", e.to_display()),
            Type::Stream(e)      => format!("Stream<{}>", e.to_display()),
            Type::Future(v)      => format!("Future<{}>", v.to_display()),
            Type::Result { ok, err } =>
                format!("Result<{}, {}>", ok.to_display(), err.to_display()),
            Type::Option(v)      => format!("Option<{}>", v.to_display()),
            Type::Provenance(d)  => format!("Provenance<{}>", d.to_display()),
            Type::Function { params, ret } => {
                let ps = params.iter().map(|p| p.to_display()).collect::<Vec<_>>().join(", ");
                format!("({}) -> {}", ps, ret.to_display())
            }
            Type::Union(ts) =>
                ts.iter().map(|t| t.to_display()).collect::<Vec<_>>().join(" | "),
            Type::Optional(b)    => format!("{}?", b.to_display()),
        }
    }
}

// ── Patterns ─────────────────────────────────────────────────────────────────

#[derive(Debug, Clone)]
pub enum Pattern {
    Wildcard,
    Literal(Lit),
    Ident(String),
    ObjectDestruct(Vec<PatternField>),
    ListDestruct(Vec<Pattern>),
    Tuple(Vec<Pattern>),
    Named { constructor: String, fields: Vec<PatternField> },
    Range { lo: Box<Lit>, hi: Box<Lit>, inclusive: bool },
    Type { inner: Box<Pattern>, ty: Box<Type> },
    Guard { inner: Box<Pattern>, cond: Box<Expr> },
    Or(Vec<Pattern>),
}

#[derive(Debug, Clone)]
pub struct PatternField {
    pub name: String,
    pub pattern: Option<Box<Pattern>>,
}

// ── Literals ──────────────────────────────────────────────────────────────────

#[derive(Debug, Clone)]
pub enum Lit {
    Bool(bool),
    Int(i64),
    Float(f64),
    Str(String),
    Null,
}

// ── Binary / Unary operators ─────────────────────────────────────────────────

#[derive(Debug, Clone, PartialEq)]
pub enum BinOp {
    Add, Sub, Mul, Div, Mod,
    Eq, Neq, Lt, Le, Gt, Ge,
    And, Or,
    Pipeline, Parallel,
    NullCoalesce,
    Range, InclusiveRange,
    Within, During, Until, In,
}

#[derive(Debug, Clone, PartialEq)]
pub enum UnOp { Neg, Not, Always, Eventually }

// ── Expressions ───────────────────────────────────────────────────────────────

#[derive(Debug, Clone)]
pub struct Expr {
    pub kind: ExprKind,
    pub span: Span,
}

impl Expr {
    pub fn new(kind: ExprKind, span: Span) -> Self { Self { kind, span } }
}

#[derive(Debug, Clone)]
pub enum ExprKind {
    Lit(Lit),
    Ident(String),
    Qualified(Vec<String>),

    // Operators
    Binary  { op: BinOp, lhs: Box<Expr>, rhs: Box<Expr> },
    Unary   { op: UnOp,  operand: Box<Expr> },
    Ternary { cond: Box<Expr>, then: Box<Expr>, else_: Box<Expr> },
    NullCoalesce { lhs: Box<Expr>, rhs: Box<Expr> },

    // Postfix
    Call    { callee: Box<Expr>, args: Vec<Argument> },
    Member  { object: Box<Expr>, member: String },
    Index   { object: Box<Expr>, index: Box<Expr> },

    // Collection literals
    List(Vec<Expr>),
    Object(Vec<ObjectField>),

    // Lambda / Block
    Lambda  { params: Vec<LambdaParam>, body: Box<Expr> },
    Block(Vec<Transformation>),

    // Match
    Match   { subject: Box<Expr>, arms: Vec<MatchArm> },

    // Functional combinators
    Map       { func: Box<Expr>, collection: Box<Expr> },
    Filter    { collection: Box<Expr>, pred: Box<Expr> },
    Reduce    { collection: Box<Expr>, func: Box<Expr>, init: Option<Box<Expr>> },
    Foreach   { collection: Box<Expr>, func: Box<Expr> },
    GroupBy   { collection: Box<Expr>, key_fn: Box<Expr> },
    FlatMap   { collection: Box<Expr>, func: Box<Expr> },
    Zip       { left: Box<Expr>, right: Box<Expr>, combiner: Option<Box<Expr>> },
    Partition { collection: Box<Expr>, pred: Box<Expr> },
    Take      { collection: Box<Expr>, n: Box<Expr> },
    Drop      { collection: Box<Expr>, n: Box<Expr> },
    TakeWhile { collection: Box<Expr>, pred: Box<Expr> },
    DropWhile { collection: Box<Expr>, pred: Box<Expr> },
    SortBy    { collection: Box<Expr>, key_fn: Box<Expr> },
    Distinct  { collection: Box<Expr>, eq_fn: Option<Box<Expr>> },
    Count     { collection: Box<Expr>, pred: Option<Box<Expr>> },
    Find      { collection: Box<Expr>, pred: Box<Expr> },
    Any       { collection: Box<Expr>, pred: Box<Expr> },
    All       { collection: Box<Expr>, pred: Box<Expr> },
    Join      { left: Box<Expr>, right: Box<Expr>, on: Box<Expr>, select: Option<Box<Expr>> },
    Window    { collection: Box<Expr>, size: Box<Expr>, step: Option<Box<Expr>> },
    Chunk     { collection: Box<Expr>, size: Box<Expr> },
    Scan      { collection: Box<Expr>, func: Box<Expr>, init: Option<Box<Expr>> },
    Collect   { collection: Box<Expr>, func: Box<Expr>, init: Box<Expr> },

    // Temporal
    Always(Box<Expr>),
    Eventually(Box<Expr>),
    During { operand: Box<Expr>, window: Box<Expr> },
    Until  { operand: Box<Expr>, cond: Box<Expr> },
    // LTL implication: when cond -> body
    When   { cond: Box<Expr>, body: Box<Expr> },

    // Error propagation
    Try(Box<Expr>),

    // Mutation
    Mutation { target: Box<Expr>, site: MutationSite, change: MutationChange },

    // Range
    Range { lo: Box<Expr>, hi: Box<Expr>, inclusive: bool },
}

#[derive(Debug, Clone)]
pub struct Argument {
    pub label: Option<String>,
    pub value: Expr,
}

#[derive(Debug, Clone)]
pub struct ObjectField {
    pub key: String,
    pub value: Expr,
}

#[derive(Debug, Clone)]
pub struct LambdaParam {
    pub name: String,
    pub ty: Option<Type>,
}

#[derive(Debug, Clone)]
pub struct MatchArm {
    pub pattern: Pattern,
    pub body: Expr,
}

#[derive(Debug, Clone)]
pub enum Transformation {
    Let { name: String, ty: Option<Type>, value: Expr },
    Expr(Expr),
}

#[derive(Debug, Clone)]
pub enum MutationSite {
    Pos(i64),
    Named { name: String, pos: i64 },
    Range(Box<Expr>, Box<Expr>),
}

#[derive(Debug, Clone)]
pub struct MutationChange {
    pub from: Box<Expr>,
    pub to: Box<Expr>,
}

// ── Statements / Declarations ─────────────────────────────────────────────────

#[derive(Debug, Clone)]
pub struct Stmt {
    pub kind: StmtKind,
    pub span: Span,
}

#[derive(Debug, Clone)]
pub enum StmtKind {
    // Declarations
    Import(ImportDecl),
    Binding    { name: String, ty: Option<Type>, value: Expr },
    Function   { name: String, params: Vec<TypedParam>, ret: Type, body: Expr },
    Pipeline   { name: String, input: Type, output: Type, body: Expr },
    TypeDecl   { name: String, generics: Vec<GenericParam>, fields: Vec<TypedField>, where_clause: Vec<Constraint> },
    AnnotationType { name: String, fields: Vec<TypedField> },
    Annotation { decl: Box<Stmt>, annotations: Vec<AnnotationPair> },
    Agent      { name: String, members: Vec<AgentMember> },
    Solver     { name: String, members: Vec<SolverMember> },
    Proof      { name: String, invariants: Vec<InvariantDecl> },

    // Statements
    Expr(Expr),
    Emit(Expr),
    Signal(Expr, Expr),
    Assert(Expr),
    Assign { target: Vec<String>, value: Expr },
}

#[derive(Debug, Clone)]
pub enum ImportDecl {
    Dotted(Vec<DottedAsName>),
    From { module: String, targets: ImportTargets },
}

#[derive(Debug, Clone)]
pub struct DottedAsName {
    pub path: Vec<String>,
    pub alias: Option<String>,
}

#[derive(Debug, Clone)]
pub enum ImportTargets {
    Star,
    Named(Vec<ImportAsName>),
}

#[derive(Debug, Clone)]
pub struct ImportAsName {
    pub name: String,
    pub alias: Option<String>,
}

#[derive(Debug, Clone)]
pub struct TypedParam {
    pub name: String,
    pub ty: Type,
}

#[derive(Debug, Clone)]
pub struct TypedField {
    pub name: String,
    pub ty: Type,
}

#[derive(Debug, Clone)]
pub struct GenericParam {
    pub name: String,
    pub constraints: Vec<GenericConstraint>,
}

#[derive(Debug, Clone)]
pub enum GenericConstraint {
    IsType(Type),
    DefaultsTo(Type),
    Extends(Type),
}

#[derive(Debug, Clone)]
pub enum Constraint {
    IsType { name: String, ty: Type },
    Equals { name: String, ty: Type },
    Extends { name: String, ty: Type },
    Expr(Expr),
}

#[derive(Debug, Clone)]
pub struct AnnotationPair {
    pub key: String,
    pub value: AnnotationValue,
}

#[derive(Debug, Clone)]
pub enum AnnotationValue {
    Lit(Lit),
    List(Vec<AnnotationValue>),
}

#[derive(Debug, Clone)]
pub enum AgentMember {
    Capability(Vec<String>),
    Stream { name: String, ty: Type },
    Rule { name: String, when: Expr, body: Vec<Transformation> },
    Decl(Box<Stmt>),
}

#[derive(Debug, Clone)]
pub enum SolverMember {
    Variable { name: String, ty: Type, domain: Option<Expr> },
    Satisfy(Vec<Expr>),
    Minimize(Expr),
    Maximize(Expr),
}

#[derive(Debug, Clone)]
pub struct InvariantDecl {
    pub name: String,
    pub body: Vec<Expr>,
}

// ── Top-level program ─────────────────────────────────────────────────────────

#[derive(Debug, Clone)]
pub struct Program {
    pub stmts: Vec<Stmt>,
}
