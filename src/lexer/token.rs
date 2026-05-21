use logos::{Lexer, Logos};

// ── Multiline string callback ─────────────────────────────────────────────────

fn lex_multiline_string(lex: &mut Lexer<'_, Token>) -> Option<String> {
    let rem = lex.remainder();
    let end = rem.find("\"\"\"").map(|p| p + 3)?;
    lex.bump(end);
    Some(lex.slice().to_owned())
}

// ── Token ─────────────────────────────────────────────────────────────────────

#[derive(Logos, Debug, Clone, PartialEq)]
#[logos(skip r"[ \t\r\n]+")]
#[logos(skip r"//[^\r\n]*")]
#[logos(skip r"/\*([^*]|\*[^/])*\*/")]
pub enum Token {
    // ── Keywords ──────────────────────────────────────────────────────────
    #[token("import")]     Import,
    #[token("from")]       From,
    #[token("let")]        Let,
    #[token("as")]         As,
    #[token("with")]       With,
    #[token("type")]       Type,
    #[token("extends")]    Extends,
    #[token("annotation")] Annotation,
    #[token("annotated")]  Annotated,
    #[token("def")]        Def,
    #[token("match")]      Match,
    #[token("when")]       When,
    #[token("where")]      Where,
    #[token("in")]         In,
    #[token("on")]         On,

    // ── Agent / Proof ──────────────────────────────────────────────────────
    #[token("agent")]      Agent,
    #[token("capability")] Capability,
    #[token("PHYSICAL")]   Physical,
    #[token("VIRTUAL")]    Virtual,
    #[token("ATOMIC")]     Atomic,
    #[token("proof")]      Proof,
    #[token("invariant")]  Invariant,
    #[token("assert")]     Assert,
    #[token("always")]     Always,
    #[token("eventually")] Eventually,
    #[token("during")]     During,
    #[token("until")]      Until,

    // ── Solver ────────────────────────────────────────────────────────────
    #[token("solver")]   Solver,
    #[token("satisfy")]  Satisfy,
    #[token("minimize")] Minimize,
    #[token("maximize")] Maximize,
    #[token("variable")] Variable,

    // ── Stream / Reactive ─────────────────────────────────────────────────
    #[token("stream")]  Stream,
    #[token("rule")]    Rule,
    #[token("emit")]    Emit,
    #[token("signal")]  Signal,
    #[token("within")]  Within,

    // ── Functional combinators ────────────────────────────────────────────
    #[token("map")]        Map,
    #[token("filter")]     Filter,
    #[token("reduce")]     Reduce,
    #[token("foreach")]    Foreach,
    #[token("group_by")]   GroupBy,
    #[token("flatmap")]    FlatMap,
    #[token("zip")]        Zip,
    #[token("partition")]  Partition,
    #[token("take")]       Take,
    #[token("drop")]       Drop,
    #[token("take_while")] TakeWhile,
    #[token("drop_while")] DropWhile,
    #[token("sort_by")]    SortBy,
    #[token("distinct")]   Distinct,
    #[token("count")]      Count,
    #[token("find")]       Find,
    #[token("any")]        Any,
    #[token("all")]        All,
    #[token("join")]       Join,
    #[token("window")]     Window,
    #[token("chunk")]      Chunk,
    #[token("scan")]       Scan,
    #[token("collect")]    Collect,

    // ── Built-in types ────────────────────────────────────────────────────
    #[token("int")]        IntType,
    #[token("long")]       LongType,
    #[token("float")]      FloatType,
    #[token("double")]     DoubleType,
    #[token("bool")]       BoolType,
    #[token("char")]       CharType,
    #[token("string")]     StringType,
    #[token("any_type")]   AnyType,
    #[token("never_type")] NeverType,
    #[token("null")]       NullLit,
    #[token("List")]       ListType,
    #[token("Map")]        MapType,
    #[token("Set")]        SetType,
    #[token("Pipeline")]   PipelineType,
    // Uppercase type names — distinct from lowercase keywords above
    #[token("Stream")]     StreamType,
    #[token("Future")]     FutureType,
    #[token("Result")]     ResultType,
    #[token("Option")]     OptionType,
    #[token("Provenance")] ProvenanceType,

    // ── Arithmetic operators ──────────────────────────────────────────────
    #[token("+")] Add,
    #[token("-")] Sub,
    #[token("*")] Mul,
    #[token("/")] Div,
    #[token("%")] Mod,

    // ── Comparison operators ──────────────────────────────────────────────
    #[token("==")] Eq,
    #[token("!=")] Neq,
    #[token("<=")] Le,
    #[token("<")]  Lt,
    #[token(">=")] Ge,
    #[token(">")]  Gt,

    // ── Logical operators ─────────────────────────────────────────────────
    #[token("&&")]  AndOp,
    #[token("||")]  OrOp,
    #[token("!")]   Not,
    #[token("and")] And,
    #[token("or")]  Or,

    // ── Pipeline / Arrow operators ────────────────────────────────────────
    #[token("↦")]
    #[token("~>")]  PipelineOp,
    #[token("|||")] ParallelOp,
    #[token("=>")]  LambdaArrow,
    #[token("->")]  Arrow,
    #[token("|")]   UnionPipe,
    #[token("??")]  NullCoalesce,
    #[token("?")]   Optional,

    // ── Bio / Mutation operators ──────────────────────────────────────────
    #[token("@")]   MutateAt,
    #[token("→")]
    #[token("-->")] BioTransform,
    #[token("..<")] ExclusiveRange,
    #[token("..=")] InclusiveRange,
    #[token("..")]  RangeOp,
    #[token("^")]   PositionStart,
    #[token("$")]   PositionEnd,
    #[token("~")]   Complement,

    // Wildcard must have higher priority than Id since `_` matches both
    #[token("_", priority = 3)]
    Wildcard,

    // ── Boolean literals ──────────────────────────────────────────────────
    #[token("true")]  True,
    #[token("false")] False,

    // ── Literals ──────────────────────────────────────────────────────────

    // IntLiteral: digit sequence (with optional _ separators) and optional long suffix
    #[regex(r"[0-9][0-9_]*[lL]?", |lex| lex.slice().to_owned(), priority = 2)]
    IntLiteral(String),

    // DecimalLiteral: requires dot or exponent or float suffix (underscore separators allowed)
    #[regex(
        r"[0-9][0-9_]*\.[0-9][0-9_]*([eE][+\-]?[0-9][0-9_]*)?[fFdD]?|[0-9][0-9_]*[eE][+\-]?[0-9][0-9_]*[fFdD]?|[0-9][0-9_]*[fFdD]",
        |lex| lex.slice().to_owned(),
        priority = 3
    )]
    DecimalLiteral(String),

    #[regex(r#""([^"\\]|\\.)*""#, |lex| lex.slice().to_owned())]
    StringLit(String),

    #[regex(r#"r"[^"]*""#, |lex| lex.slice().to_owned())]
    RawString(String),

    // Multiline string: """ ... """ via callback (non-greedy not supported in logos)
    #[token("\"\"\"", lex_multiline_string)]
    MultilineString(String),

    // ── Delimiters ────────────────────────────────────────────────────────
    #[token("(")] LParen,
    #[token(")")] RParen,
    #[token("[")] LBrack,
    #[token("]")] RBrack,
    #[token("{")] LCurly,
    #[token("}")] RCurly,
    #[token(".")] Dot,
    #[token(",")] Comma,
    #[token(":")] Colon,
    #[token(";")] Semi,
    #[token("=")] Equals,

    // ── Identifier ────────────────────────────────────────────────────────
    #[regex(r"[a-zA-Z_][a-zA-Z0-9_]*", |lex| lex.slice().to_owned())]
    Id(String),
}

impl std::fmt::Display for Token {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        match self {
            Token::Id(s) | Token::IntLiteral(s) | Token::DecimalLiteral(s)
            | Token::StringLit(s) | Token::RawString(s) | Token::MultilineString(s) => {
                write!(f, "{s}")
            }
            t => write!(f, "{t:?}"),
        }
    }
}
