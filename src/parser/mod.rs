pub mod ast;

use crate::lexer::{token::Token, Span, Spanned};
use ast::*;
use thiserror::Error;

#[derive(Debug, Error, Clone)]
pub enum ParseError {
    #[error("{msg} at {span:?}")]
    Unexpected { msg: String, span: Span },
    #[error("unexpected end of input")]
    Eof,
}

pub type ParseResult<T> = Result<T, ParseError>;

// ── Parser ────────────────────────────────────────────────────────────────────

pub struct Parser {
    tokens: Vec<Spanned<Token>>,
    pos: usize,
}

impl Parser {
    pub fn new(tokens: Vec<Spanned<Token>>) -> Self {
        Self { tokens, pos: 0 }
    }

    // ── Primitives ────────────────────────────────────────────────────────

    fn peek(&self) -> Option<&Token> {
        self.tokens.get(self.pos).map(|s| &s.node)
    }

    fn peek_spanned(&self) -> Option<&Spanned<Token>> {
        self.tokens.get(self.pos)
    }

    fn span(&self) -> Span {
        self.tokens.get(self.pos)
            .map(|s| s.span.clone())
            .unwrap_or(0..0)
    }

    fn advance(&mut self) -> Option<Spanned<Token>> {
        let t = self.tokens.get(self.pos).cloned();
        if t.is_some() { self.pos += 1; }
        t
    }

    fn expect(&mut self, expected: &Token) -> ParseResult<Spanned<Token>> {
        let span = self.span();
        match self.peek() {
            Some(t) if t == expected => Ok(self.advance().unwrap()),
            Some(t) => Err(ParseError::Unexpected {
                msg: format!("expected {expected:?}, got {t:?}"),
                span,
            }),
            None => Err(ParseError::Eof),
        }
    }

    fn eat(&mut self, tok: &Token) -> bool {
        if self.peek() == Some(tok) {
            self.advance();
            true
        } else {
            false
        }
    }

    fn is_at_end(&self) -> bool { self.pos >= self.tokens.len() }

    fn error<T>(&self, msg: impl Into<String>) -> ParseResult<T> {
        Err(ParseError::Unexpected { msg: msg.into(), span: self.span() })
    }

    // ── Program ───────────────────────────────────────────────────────────

    pub fn parse_program(&mut self) -> ParseResult<Program> {
        let stmts = self.parse_statement_list()?;
        Ok(Program { stmts })
    }

    fn parse_statement_list(&mut self) -> ParseResult<Vec<Stmt>> {
        let mut stmts = Vec::new();
        while !self.is_at_end() {
            self.eat(&Token::Semi);
            if self.is_at_end() { break; }
            stmts.push(self.parse_statement()?);
            self.eat(&Token::Semi);
        }
        Ok(stmts)
    }

    // ── Statements ────────────────────────────────────────────────────────

    fn parse_statement(&mut self) -> ParseResult<Stmt> {
        let span_start = self.span();
        let kind = match self.peek() {
            Some(Token::Import) | Some(Token::From) => StmtKind::Import(self.parse_import_decl()?),
            Some(Token::Let)    => self.parse_binding_decl()?,
            Some(Token::Def)    => self.parse_function_decl()?,
            Some(Token::Type)   => self.parse_type_decl()?,
            Some(Token::Annotation) => self.parse_annotation_type_decl()?,
            Some(Token::Annotated)  => self.parse_annotation_stmt()?,
            Some(Token::Agent)  => self.parse_agent_decl()?,
            Some(Token::Solver) => self.parse_solver_decl()?,
            Some(Token::Proof)  => self.parse_proof_decl()?,
            Some(Token::Emit)   => { self.advance(); let e = self.parse_expression()?; StmtKind::Emit(e) }
            Some(Token::Signal) => { self.advance(); let e = self.parse_expression()?; StmtKind::Signal(e) }
            Some(Token::Assert) => { self.advance(); self.expect(&Token::LParen)?; let e = self.parse_expression()?; self.expect(&Token::RParen)?; StmtKind::Assert(e) }
            _ => {
                // Check for assignment: qualifiedName = expression ;
                if self.is_assignment() {
                    self.parse_assignment()?
                } else {
                    StmtKind::Expr(self.parse_expression()?)
                }
            }
        };
        let span = span_start.start..self.span().end;
        Ok(Stmt { kind, span })
    }

    fn is_assignment(&self) -> bool {
        let mut i = self.pos;
        while let Some(t) = self.tokens.get(i) {
            match &t.node {
                Token::Id(_) | Token::Dot => i += 1,
                Token::Equals => return true,
                _ => return false,
            }
        }
        false
    }

    fn parse_assignment(&mut self) -> ParseResult<StmtKind> {
        let mut parts = Vec::new();
        loop {
            match self.advance() {
                Some(Spanned { node: Token::Id(n), .. }) => parts.push(n),
                _ => return self.error("expected identifier in assignment"),
            }
            if !self.eat(&Token::Dot) { break; }
        }
        self.expect(&Token::Equals)?;
        let value = self.parse_expression()?;
        Ok(StmtKind::Assign { target: parts, value })
    }

    // ── Declarations ──────────────────────────────────────────────────────

    fn parse_import_decl(&mut self) -> ParseResult<ImportDecl> {
        if self.eat(&Token::From) {
            let module = self.parse_qualified_name()?.join(".");
            self.expect(&Token::Import)?;
            let targets = if self.eat(&Token::Mul) {
                ImportTargets::Star
            } else {
                let mut names = Vec::new();
                loop {
                    names.push(self.parse_import_as_name()?);
                    if !self.eat(&Token::Comma) { break; }
                }
                ImportTargets::Named(names)
            };
            Ok(ImportDecl::From { module, targets })
        } else {
            self.expect(&Token::Import)?;
            let mut items = vec![self.parse_dotted_as_name()?];
            while self.eat(&Token::Comma) {
                items.push(self.parse_dotted_as_name()?);
            }
            Ok(ImportDecl::Dotted(items))
        }
    }

    fn parse_dotted_as_name(&mut self) -> ParseResult<DottedAsName> {
        let path = self.parse_qualified_name()?;
        let alias = if self.eat(&Token::As) {
            Some(self.expect_id()?)
        } else { None };
        Ok(DottedAsName { path, alias })
    }

    fn parse_import_as_name(&mut self) -> ParseResult<ImportAsName> {
        let name = self.expect_id()?;
        let alias = if self.eat(&Token::As) {
            Some(self.expect_id()?)
        } else { None };
        Ok(ImportAsName { name, alias })
    }

    fn parse_binding_decl(&mut self) -> ParseResult<StmtKind> {
        self.expect(&Token::Let)?;
        let name = self.expect_id()?;
        let ty = if self.eat(&Token::Colon) {
            Some(self.parse_type()?)
        } else { None };
        self.expect(&Token::Equals)?;
        let value = self.parse_expression()?;
        Ok(StmtKind::Binding { name, ty, value })
    }

    fn parse_function_decl(&mut self) -> ParseResult<StmtKind> {
        self.expect(&Token::Def)?;
        let name = self.expect_id()?;
        self.expect(&Token::LParen)?;
        let params = if self.peek() == Some(&Token::RParen) {
            Vec::new()
        } else {
            self.parse_typed_param_list()?
        };
        self.expect(&Token::RParen)?;
        self.expect(&Token::Arrow)?;
        let ret = self.parse_type()?;
        self.expect(&Token::Equals)?;
        let body = self.parse_expression()?;
        Ok(StmtKind::Function { name, params, ret, body })
    }

    fn parse_typed_param_list(&mut self) -> ParseResult<Vec<TypedParam>> {
        let mut params = vec![self.parse_typed_param()?];
        while self.eat(&Token::Comma) {
            params.push(self.parse_typed_param()?);
        }
        Ok(params)
    }

    fn parse_typed_param(&mut self) -> ParseResult<TypedParam> {
        let name = self.expect_id()?;
        self.expect(&Token::Colon)?;
        let ty = self.parse_type()?;
        Ok(TypedParam { name, ty })
    }

    fn parse_type_decl(&mut self) -> ParseResult<StmtKind> {
        self.expect(&Token::Type)?;
        let name = self.expect_id()?;
        let generics = if self.eat(&Token::Lt) {
            let g = self.parse_generic_param_list()?;
            self.expect(&Token::Gt)?;
            g
        } else { Vec::new() };
        self.expect(&Token::LCurly)?;
        let fields = self.parse_typed_field_list()?;
        self.expect(&Token::RCurly)?;
        let where_clause = if self.eat(&Token::Where) {
            self.parse_constraint_list()?
        } else { Vec::new() };
        Ok(StmtKind::TypeDecl { name, generics, fields, where_clause })
    }

    fn parse_annotation_type_decl(&mut self) -> ParseResult<StmtKind> {
        self.expect(&Token::Annotation)?;
        let name = self.expect_id()?;
        self.expect(&Token::LCurly)?;
        let fields = self.parse_typed_field_list()?;
        self.expect(&Token::RCurly)?;
        Ok(StmtKind::AnnotationType { name, fields })
    }

    fn parse_annotation_stmt(&mut self) -> ParseResult<StmtKind> {
        self.expect(&Token::Annotated)?;
        let decl = Box::new(self.parse_statement()?);
        self.expect(&Token::With)?;
        self.expect(&Token::LCurly)?;
        let mut annotations = Vec::new();
        loop {
            let key = self.expect_id()?;
            self.expect(&Token::Colon)?;
            let value = self.parse_annotation_value()?;
            annotations.push(AnnotationPair { key, value });
            if !self.eat(&Token::Comma) { break; }
        }
        self.expect(&Token::RCurly)?;
        Ok(StmtKind::Annotation { decl, annotations })
    }

    fn parse_annotation_value(&mut self) -> ParseResult<AnnotationValue> {
        if self.peek() == Some(&Token::LBrack) {
            self.advance();
            let mut items = Vec::new();
            while self.peek() != Some(&Token::RBrack) {
                items.push(self.parse_annotation_value()?);
                if !self.eat(&Token::Comma) { break; }
            }
            self.expect(&Token::RBrack)?;
            Ok(AnnotationValue::List(items))
        } else {
            Ok(AnnotationValue::Lit(self.parse_literal()?))
        }
    }

    fn parse_agent_decl(&mut self) -> ParseResult<StmtKind> {
        self.expect(&Token::Agent)?;
        let name = self.expect_id()?;
        self.expect(&Token::LCurly)?;
        let mut members = Vec::new();
        while self.peek() != Some(&Token::RCurly) {
            members.push(self.parse_agent_member()?);
        }
        self.expect(&Token::RCurly)?;
        Ok(StmtKind::Agent { name, members })
    }

    fn parse_agent_member(&mut self) -> ParseResult<AgentMember> {
        match self.peek() {
            Some(Token::Capability) => {
                self.advance();
                let ids = self.parse_id_list()?;
                self.eat(&Token::Semi);
                Ok(AgentMember::Capability(ids))
            }
            Some(Token::Stream) => {
                self.advance();
                let name = self.expect_id()?;
                self.expect(&Token::Colon)?;
                let ty = self.parse_type()?;
                self.eat(&Token::Semi);
                Ok(AgentMember::Stream { name, ty })
            }
            Some(Token::Rule) => {
                self.advance();
                let name = match self.peek() {
                    Some(Token::Id(_)) => self.expect_id()?,
                    Some(Token::StringLit(_)) => {
                        if let Some(Spanned { node: Token::StringLit(s), .. }) = self.advance() { s } else { unreachable!() }
                    }
                    _ => return self.error("expected rule name"),
                };
                self.expect(&Token::LCurly)?;
                self.expect(&Token::When)?;
                let when = self.parse_expression()?;
                self.expect(&Token::Arrow)?;
                let body = self.parse_block_body()?;
                self.expect(&Token::RCurly)?;
                Ok(AgentMember::Rule { name, when, body })
            }
            _ => {
                let decl = self.parse_statement()?;
                Ok(AgentMember::Decl(Box::new(decl)))
            }
        }
    }

    fn parse_solver_decl(&mut self) -> ParseResult<StmtKind> {
        self.expect(&Token::Solver)?;
        let name = self.expect_id()?;
        self.expect(&Token::LCurly)?;
        let mut members = Vec::new();
        while self.peek() != Some(&Token::RCurly) {
            members.push(self.parse_solver_member()?);
        }
        self.expect(&Token::RCurly)?;
        Ok(StmtKind::Solver { name, members })
    }

    fn parse_solver_member(&mut self) -> ParseResult<SolverMember> {
        match self.peek() {
            Some(Token::Variable) => {
                self.advance();
                let name = self.expect_id()?;
                self.expect(&Token::Colon)?;
                let ty = self.parse_type()?;
                let domain = if self.eat(&Token::In) {
                    Some(self.parse_expression()?)
                } else { None };
                self.eat(&Token::Semi);
                Ok(SolverMember::Variable { name, ty, domain })
            }
            Some(Token::Satisfy) => {
                self.advance();
                self.expect(&Token::LCurly)?;
                let mut exprs = Vec::new();
                while self.peek() != Some(&Token::RCurly) {
                    exprs.push(self.parse_expression()?);
                    self.eat(&Token::Semi);
                }
                self.expect(&Token::RCurly)?;
                Ok(SolverMember::Satisfy(exprs))
            }
            Some(Token::Minimize) => {
                self.advance();
                let e = self.parse_expression()?;
                self.eat(&Token::Semi);
                Ok(SolverMember::Minimize(e))
            }
            Some(Token::Maximize) => {
                self.advance();
                let e = self.parse_expression()?;
                self.eat(&Token::Semi);
                Ok(SolverMember::Maximize(e))
            }
            _ => self.error("expected solver member"),
        }
    }

    fn parse_proof_decl(&mut self) -> ParseResult<StmtKind> {
        self.expect(&Token::Proof)?;
        let name = self.expect_id()?;
        self.expect(&Token::LCurly)?;
        let mut invariants = Vec::new();
        while self.peek() != Some(&Token::RCurly) {
            invariants.push(self.parse_invariant_decl()?);
        }
        self.expect(&Token::RCurly)?;
        Ok(StmtKind::Proof { name, invariants })
    }

    fn parse_invariant_decl(&mut self) -> ParseResult<InvariantDecl> {
        self.expect(&Token::Invariant)?;
        let name = self.expect_id()?;
        self.expect(&Token::LCurly)?;
        let mut body = Vec::new();
        while self.peek() != Some(&Token::RCurly) {
            body.push(self.parse_expression()?);
            self.eat(&Token::Semi);
        }
        self.expect(&Token::RCurly)?;
        Ok(InvariantDecl { name, body })
    }

    // ── Types ─────────────────────────────────────────────────────────────

    fn parse_type(&mut self) -> ParseResult<Type> {
        let mut ty = self.parse_optional_type()?;
        while self.eat(&Token::UnionPipe) {
            let rhs = self.parse_optional_type()?;
            ty = match ty {
                Type::Union(mut ts) => { ts.push(rhs); Type::Union(ts) }
                _ => Type::Union(vec![ty, rhs]),
            };
        }
        Ok(ty)
    }

    fn parse_optional_type(&mut self) -> ParseResult<Type> {
        let base = self.parse_base_type()?;
        if self.eat(&Token::Optional) {
            Ok(Type::Optional(Box::new(base)))
        } else {
            Ok(base)
        }
    }

    fn parse_base_type(&mut self) -> ParseResult<Type> {
        match self.peek() {
            Some(Token::IntType)    => { self.advance(); Ok(Type::Primitive(PrimitiveKind::Int)) }
            Some(Token::LongType)   => { self.advance(); Ok(Type::Primitive(PrimitiveKind::Long)) }
            Some(Token::FloatType)  => { self.advance(); Ok(Type::Primitive(PrimitiveKind::Float)) }
            Some(Token::DoubleType) => { self.advance(); Ok(Type::Primitive(PrimitiveKind::Double)) }
            Some(Token::BoolType)   => { self.advance(); Ok(Type::Primitive(PrimitiveKind::Bool)) }
            Some(Token::CharType)   => { self.advance(); Ok(Type::Primitive(PrimitiveKind::Char)) }
            Some(Token::StringType) => { self.advance(); Ok(Type::Primitive(PrimitiveKind::String)) }
            Some(Token::AnyType)    => { self.advance(); Ok(Type::Primitive(PrimitiveKind::Any)) }
            Some(Token::NeverType)  => { self.advance(); Ok(Type::Primitive(PrimitiveKind::Never)) }
            Some(Token::ListType)   => { self.advance(); self.expect(&Token::Lt)?; let e = self.parse_type()?; self.expect(&Token::Gt)?; Ok(Type::List(Box::new(e))) }
            Some(Token::MapType)    => { self.advance(); self.expect(&Token::Lt)?; let k = self.parse_type()?; self.expect(&Token::Comma)?; let v = self.parse_type()?; self.expect(&Token::Gt)?; Ok(Type::Map { key: Box::new(k), value: Box::new(v) }) }
            Some(Token::SetType)    => { self.advance(); self.expect(&Token::Lt)?; let e = self.parse_type()?; self.expect(&Token::Gt)?; Ok(Type::Set(Box::new(e))) }
            Some(Token::PipelineType) => {
                self.advance();
                self.expect(&Token::Lt)?;
                let i = self.parse_type()?;
                self.expect(&Token::Arrow)?;
                let o = self.parse_type()?;
                self.expect(&Token::Gt)?;
                Ok(Type::Pipeline { input: Box::new(i), output: Box::new(o) })
            }
            Some(Token::StreamType)    => { self.advance(); self.expect(&Token::Lt)?; let e = self.parse_type()?; self.expect(&Token::Gt)?; Ok(Type::Stream(Box::new(e))) }
            Some(Token::FutureType)    => { self.advance(); self.expect(&Token::Lt)?; let v = self.parse_type()?; self.expect(&Token::Gt)?; Ok(Type::Future(Box::new(v))) }
            Some(Token::ResultType)    => { self.advance(); self.expect(&Token::Lt)?; let ok = self.parse_type()?; self.expect(&Token::Comma)?; let err = self.parse_type()?; self.expect(&Token::Gt)?; Ok(Type::Result { ok: Box::new(ok), err: Box::new(err) }) }
            Some(Token::OptionType)    => { self.advance(); self.expect(&Token::Lt)?; let v = self.parse_type()?; self.expect(&Token::Gt)?; Ok(Type::Option(Box::new(v))) }
            Some(Token::ProvenanceType) => { self.advance(); self.expect(&Token::Lt)?; let d = self.parse_type()?; self.expect(&Token::Gt)?; Ok(Type::Provenance(Box::new(d))) }
            Some(Token::LParen) => {
                self.advance();
                if self.peek() == Some(&Token::RParen) {
                    self.advance();
                    self.expect(&Token::Arrow)?;
                    let ret = self.parse_type()?;
                    return Ok(Type::Function { params: Vec::new(), ret: Box::new(ret) });
                }
                // Either "(type)" or "(t1, t2) -> ret"
                let first = self.parse_type()?;
                if self.eat(&Token::RParen) {
                    if self.eat(&Token::Arrow) {
                        let ret = self.parse_type()?;
                        Ok(Type::Function { params: vec![first], ret: Box::new(ret) })
                    } else {
                        Ok(first)
                    }
                } else {
                    let mut params = vec![first];
                    while self.eat(&Token::Comma) {
                        params.push(self.parse_type()?);
                    }
                    self.expect(&Token::RParen)?;
                    self.expect(&Token::Arrow)?;
                    let ret = self.parse_type()?;
                    Ok(Type::Function { params, ret: Box::new(ret) })
                }
            }
            Some(Token::Id(_)) => {
                let name = self.parse_qualified_name()?.join(".");
                let type_args = if self.eat(&Token::Lt) {
                    let mut args = vec![self.parse_type()?];
                    while self.eat(&Token::Comma) {
                        args.push(self.parse_type()?);
                    }
                    self.expect(&Token::Gt)?;
                    args
                } else { Vec::new() };
                Ok(Type::UserDefined { name, type_args })
            }
            _ => self.error("expected type"),
        }
    }

    fn parse_typed_field_list(&mut self) -> ParseResult<Vec<TypedField>> {
        let mut fields = vec![self.parse_typed_field()?];
        while self.eat(&Token::Comma) {
            if self.peek() == Some(&Token::RCurly) { break; }
            fields.push(self.parse_typed_field()?);
        }
        Ok(fields)
    }

    fn parse_typed_field(&mut self) -> ParseResult<TypedField> {
        let name = self.expect_id()?;
        self.expect(&Token::Colon)?;
        let ty = self.parse_type()?;
        Ok(TypedField { name, ty })
    }

    fn parse_generic_param_list(&mut self) -> ParseResult<Vec<GenericParam>> {
        let mut params = vec![self.parse_generic_param()?];
        while self.eat(&Token::Comma) {
            params.push(self.parse_generic_param()?);
        }
        Ok(params)
    }

    fn parse_generic_param(&mut self) -> ParseResult<GenericParam> {
        let name = self.expect_id()?;
        let mut constraints = Vec::new();
        loop {
            match self.peek() {
                Some(Token::Colon)   => { self.advance(); constraints.push(GenericConstraint::IsType(self.parse_type()?)); }
                Some(Token::Equals)  => { self.advance(); constraints.push(GenericConstraint::DefaultsTo(self.parse_type()?)); }
                Some(Token::Extends) => { self.advance(); constraints.push(GenericConstraint::Extends(self.parse_type()?)); }
                _ => break,
            }
        }
        Ok(GenericParam { name, constraints })
    }

    fn parse_constraint_list(&mut self) -> ParseResult<Vec<Constraint>> {
        let mut cs = vec![self.parse_constraint()?];
        while self.eat(&Token::Comma) {
            cs.push(self.parse_constraint()?);
        }
        Ok(cs)
    }

    fn parse_constraint(&mut self) -> ParseResult<Constraint> {
        if let Some(Token::Id(_)) = self.peek() {
            let name = self.expect_id()?;
            match self.peek() {
                Some(Token::Colon)   => { self.advance(); Ok(Constraint::IsType { name, ty: self.parse_type()? }) }
                Some(Token::Equals)  => { self.advance(); Ok(Constraint::Equals  { name, ty: self.parse_type()? }) }
                Some(Token::Extends) => { self.advance(); Ok(Constraint::Extends { name, ty: self.parse_type()? }) }
                _ => {
                    // treat as expression starting with identifier
                    let start = self.pos - 1;
                    self.pos = start;
                    Ok(Constraint::Expr(self.parse_expression()?))
                }
            }
        } else {
            Ok(Constraint::Expr(self.parse_expression()?))
        }
    }

    // ── Expressions ───────────────────────────────────────────────────────

    fn parse_expression(&mut self) -> ParseResult<Expr> {
        match self.peek() {
            Some(Token::Map)        => self.parse_map_expr(),
            Some(Token::Filter)     => self.parse_filter_expr(),
            Some(Token::Reduce)     => self.parse_reduce_expr(),
            Some(Token::Foreach)    => self.parse_foreach_expr(),
            Some(Token::GroupBy)    => self.parse_group_by_expr(),
            Some(Token::FlatMap)    => self.parse_flatmap_expr(),
            Some(Token::Zip)        => self.parse_zip_expr(),
            Some(Token::Partition)  => self.parse_partition_expr(),
            Some(Token::Take)       => self.parse_take_expr(),
            Some(Token::Drop)       => self.parse_drop_expr(),
            Some(Token::TakeWhile)  => self.parse_take_while_expr(),
            Some(Token::DropWhile)  => self.parse_drop_while_expr(),
            Some(Token::SortBy)     => self.parse_sort_by_expr(),
            Some(Token::Distinct)   => self.parse_distinct_expr(),
            Some(Token::Count)      => self.parse_count_expr(),
            Some(Token::Find)       => self.parse_find_expr(),
            Some(Token::Any)        => self.parse_any_expr(),
            Some(Token::All)        => self.parse_all_expr(),
            Some(Token::Join)       => self.parse_join_expr(),
            Some(Token::Window)     => self.parse_window_expr(),
            Some(Token::Chunk)      => self.parse_chunk_expr(),
            Some(Token::Scan)       => self.parse_scan_expr(),
            Some(Token::Collect)    => self.parse_collect_expr(),
            _ => self.parse_lambda_or_pipeline(),
        }
    }

    fn parse_lambda_or_pipeline(&mut self) -> ParseResult<Expr> {
        // Try lambda first, then pipeline
        if self.is_lambda_start() {
            self.parse_lambda_expr()
        } else {
            self.parse_pipeline_expr()
        }
    }

    fn is_lambda_start(&self) -> bool {
        // (params) => ...  or  id => ...  or  {fields} => ...  or  [elems] => ...
        match self.peek() {
            Some(Token::LParen) => {
                // look-ahead to see if it's a lambda param list
                // simplified: if there's a => somewhere before the next binary op
                let mut i = self.pos + 1;
                let mut depth = 1usize;
                while let Some(t) = self.tokens.get(i) {
                    match &t.node {
                        Token::LParen => depth += 1,
                        Token::RParen => {
                            depth -= 1;
                            if depth == 0 {
                                if let Some(next) = self.tokens.get(i + 1) {
                                    return next.node == Token::LambdaArrow;
                                }
                                return false;
                            }
                        }
                        _ => {}
                    }
                    i += 1;
                }
                false
            }
            Some(Token::Id(_)) => {
                if let Some(t) = self.tokens.get(self.pos + 1) {
                    t.node == Token::LambdaArrow
                } else { false }
            }
            Some(Token::LCurly) | Some(Token::LBrack) => {
                // Could be object/list expr or destructure lambda
                // Look for =>
                let mut i = self.pos + 1;
                let mut depth = 1usize;
                let open = &self.tokens[self.pos].node;
                let (close_tok, _) = match open {
                    Token::LCurly => (Token::RCurly, Token::LCurly),
                    _             => (Token::RBrack, Token::LBrack),
                };
                while let Some(t) = self.tokens.get(i) {
                    if t.node == Token::LCurly || t.node == Token::LBrack { depth += 1; }
                    else if t.node == close_tok { depth -= 1; if depth == 0 {
                        return self.tokens.get(i + 1).map(|t| t.node == Token::LambdaArrow).unwrap_or(false);
                    }}
                    i += 1;
                }
                false
            }
            _ => false,
        }
    }

    fn parse_lambda_expr(&mut self) -> ParseResult<Expr> {
        let span_start = self.span();
        let params = match self.peek() {
            Some(Token::LParen) => {
                self.advance();
                let params = if self.peek() == Some(&Token::RParen) {
                    Vec::new()
                } else {
                    self.parse_lambda_param_list()?
                };
                self.expect(&Token::RParen)?;
                params
            }
            Some(Token::Id(_)) => {
                let name = self.expect_id()?;
                vec![LambdaParam { name, ty: None }]
            }
            Some(Token::LCurly) => {
                self.advance();
                let params = self.parse_simple_destructure_fields()?;
                self.expect(&Token::RCurly)?;
                params
            }
            Some(Token::LBrack) => {
                self.advance();
                let params = self.parse_simple_destructure_list()?;
                self.expect(&Token::RBrack)?;
                params
            }
            _ => return self.error("expected lambda params"),
        };
        self.expect(&Token::LambdaArrow)?;
        let body = if self.peek() == Some(&Token::LCurly) {
            let span = self.span();
            Expr::new(ExprKind::Block(self.parse_block_body()?), span)
        } else {
            self.parse_expression()?
        };
        let span = span_start.start..self.span().end;
        Ok(Expr::new(ExprKind::Lambda { params, body: Box::new(body) }, span))
    }

    fn parse_lambda_param_list(&mut self) -> ParseResult<Vec<LambdaParam>> {
        let mut params = vec![self.parse_lambda_param()?];
        while self.eat(&Token::Comma) {
            params.push(self.parse_lambda_param()?);
        }
        Ok(params)
    }

    fn parse_lambda_param(&mut self) -> ParseResult<LambdaParam> {
        let name = self.expect_id()?;
        let ty = if self.eat(&Token::Colon) { Some(self.parse_type()?) } else { None };
        Ok(LambdaParam { name, ty })
    }

    fn parse_simple_destructure_fields(&mut self) -> ParseResult<Vec<LambdaParam>> {
        let mut params = Vec::new();
        loop {
            match self.peek() {
                Some(Token::Id(_)) => {
                    let name = self.expect_id()?;
                    if self.eat(&Token::Colon) {
                        let alias = self.expect_id()?;
                        params.push(LambdaParam { name: alias, ty: None });
                    } else {
                        params.push(LambdaParam { name, ty: None });
                    }
                }
                Some(Token::Wildcard) => { self.advance(); params.push(LambdaParam { name: "_".into(), ty: None }); }
                _ => break,
            }
            if !self.eat(&Token::Comma) { break; }
        }
        Ok(params)
    }

    fn parse_simple_destructure_list(&mut self) -> ParseResult<Vec<LambdaParam>> {
        let mut params = Vec::new();
        loop {
            match self.peek() {
                Some(Token::Id(_)) => params.push(LambdaParam { name: self.expect_id()?, ty: None }),
                Some(Token::Wildcard) => { self.advance(); params.push(LambdaParam { name: "_".into(), ty: None }); }
                _ => break,
            }
            if !self.eat(&Token::Comma) { break; }
        }
        Ok(params)
    }

    fn parse_pipeline_expr(&mut self) -> ParseResult<Expr> {
        let mut lhs = self.parse_null_coalesce_expr()?;
        loop {
            let op = match self.peek() {
                Some(Token::PipelineOp) => { self.advance(); BinOp::Pipeline }
                Some(Token::ParallelOp) => { self.advance(); BinOp::Parallel }
                _ => break,
            };
            let rhs = self.parse_null_coalesce_expr()?;
            let span = lhs.span.start..rhs.span.end;
            lhs = Expr::new(ExprKind::Binary { op, lhs: Box::new(lhs), rhs: Box::new(rhs) }, span);
        }
        Ok(lhs)
    }

    fn parse_null_coalesce_expr(&mut self) -> ParseResult<Expr> {
        let mut lhs = self.parse_ternary_expr()?;
        while self.eat(&Token::NullCoalesce) {
            let rhs = self.parse_ternary_expr()?;
            let span = lhs.span.start..rhs.span.end;
            lhs = Expr::new(ExprKind::NullCoalesce { lhs: Box::new(lhs), rhs: Box::new(rhs) }, span);
        }
        Ok(lhs)
    }

    fn parse_ternary_expr(&mut self) -> ParseResult<Expr> {
        let cond = self.parse_logical_or_expr()?;
        if self.eat(&Token::Optional) {
            let then = self.parse_expression()?;
            self.expect(&Token::Colon)?;
            let else_ = self.parse_ternary_expr()?;
            let span = cond.span.start..else_.span.end;
            Ok(Expr::new(ExprKind::Ternary { cond: Box::new(cond), then: Box::new(then), else_: Box::new(else_) }, span))
        } else {
            Ok(cond)
        }
    }

    fn parse_logical_or_expr(&mut self) -> ParseResult<Expr> {
        let mut lhs = self.parse_logical_and_expr()?;
        loop {
            let has_op = match self.peek() {
                Some(Token::OrOp) | Some(Token::Or) => { self.advance(); true }
                _ => false,
            };
            if !has_op { break; }
            let rhs = self.parse_logical_and_expr()?;
            let span = lhs.span.start..rhs.span.end;
            lhs = Expr::new(ExprKind::Binary { op: BinOp::Or, lhs: Box::new(lhs), rhs: Box::new(rhs) }, span);
        }
        Ok(lhs)
    }

    fn parse_logical_and_expr(&mut self) -> ParseResult<Expr> {
        let mut lhs = self.parse_equality_expr()?;
        loop {
            let has_op = match self.peek() {
                Some(Token::AndOp) | Some(Token::And) => { self.advance(); true }
                _ => false,
            };
            if !has_op { break; }
            let rhs = self.parse_equality_expr()?;
            let span = lhs.span.start..rhs.span.end;
            lhs = Expr::new(ExprKind::Binary { op: BinOp::And, lhs: Box::new(lhs), rhs: Box::new(rhs) }, span);
        }
        Ok(lhs)
    }

    fn parse_equality_expr(&mut self) -> ParseResult<Expr> {
        let mut lhs = self.parse_relational_expr()?;
        loop {
            let op = match self.peek() {
                Some(Token::Eq)  => { self.advance(); BinOp::Eq }
                Some(Token::Neq) => { self.advance(); BinOp::Neq }
                _ => break,
            };
            let rhs = self.parse_relational_expr()?;
            let span = lhs.span.start..rhs.span.end;
            lhs = Expr::new(ExprKind::Binary { op, lhs: Box::new(lhs), rhs: Box::new(rhs) }, span);
        }
        Ok(lhs)
    }

    fn parse_relational_expr(&mut self) -> ParseResult<Expr> {
        let mut lhs = self.parse_range_expr()?;
        loop {
            let op = match self.peek() {
                Some(Token::Le)     => { self.advance(); BinOp::Le }
                Some(Token::Lt)     => { self.advance(); BinOp::Lt }
                Some(Token::Ge)     => { self.advance(); BinOp::Ge }
                Some(Token::Gt)     => { self.advance(); BinOp::Gt }
                Some(Token::Within) => { self.advance(); BinOp::Range }
                Some(Token::During) => { self.advance(); BinOp::Range }
                Some(Token::Until)  => { self.advance(); BinOp::Range }
                Some(Token::In)     => { self.advance(); BinOp::In }
                _ => break,
            };
            let rhs = self.parse_additive_expr()?;
            let span = lhs.span.start..rhs.span.end;
            lhs = Expr::new(ExprKind::Binary { op, lhs: Box::new(lhs), rhs: Box::new(rhs) }, span);
        }
        Ok(lhs)
    }

    fn parse_range_expr(&mut self) -> ParseResult<Expr> {
        let lhs = self.parse_additive_expr()?;
        match self.peek() {
            Some(Token::InclusiveRange) => {
                self.advance();
                let rhs = self.parse_additive_expr()?;
                let span = lhs.span.start..rhs.span.end;
                Ok(Expr::new(ExprKind::Range { lo: Box::new(lhs), hi: Box::new(rhs), inclusive: true }, span))
            }
            Some(Token::ExclusiveRange) => {
                self.advance();
                let rhs = self.parse_additive_expr()?;
                let span = lhs.span.start..rhs.span.end;
                Ok(Expr::new(ExprKind::Range { lo: Box::new(lhs), hi: Box::new(rhs), inclusive: false }, span))
            }
            Some(Token::RangeOp) => {
                self.advance();
                let rhs = self.parse_additive_expr()?;
                let span = lhs.span.start..rhs.span.end;
                Ok(Expr::new(ExprKind::Range { lo: Box::new(lhs), hi: Box::new(rhs), inclusive: false }, span))
            }
            _ => Ok(lhs),
        }
    }

    fn parse_additive_expr(&mut self) -> ParseResult<Expr> {
        let mut lhs = self.parse_multiplicative_expr()?;
        loop {
            let op = match self.peek() {
                Some(Token::Add) => { self.advance(); BinOp::Add }
                Some(Token::Sub) => { self.advance(); BinOp::Sub }
                _ => break,
            };
            let rhs = self.parse_multiplicative_expr()?;
            let span = lhs.span.start..rhs.span.end;
            lhs = Expr::new(ExprKind::Binary { op, lhs: Box::new(lhs), rhs: Box::new(rhs) }, span);
        }
        Ok(lhs)
    }

    fn parse_multiplicative_expr(&mut self) -> ParseResult<Expr> {
        let mut lhs = self.parse_unary_expr()?;
        loop {
            let op = match self.peek() {
                Some(Token::Mul) => { self.advance(); BinOp::Mul }
                Some(Token::Div) => { self.advance(); BinOp::Div }
                Some(Token::Mod) => { self.advance(); BinOp::Mod }
                _ => break,
            };
            let rhs = self.parse_unary_expr()?;
            let span = lhs.span.start..rhs.span.end;
            lhs = Expr::new(ExprKind::Binary { op, lhs: Box::new(lhs), rhs: Box::new(rhs) }, span);
        }
        Ok(lhs)
    }

    fn parse_unary_expr(&mut self) -> ParseResult<Expr> {
        let span_start = self.span();
        match self.peek() {
            Some(Token::Not)        => { self.advance(); let e = self.parse_unary_expr()?; let span = span_start.start..e.span.end; Ok(Expr::new(ExprKind::Unary { op: UnOp::Not, operand: Box::new(e) }, span)) }
            Some(Token::Sub)        => { self.advance(); let e = self.parse_unary_expr()?; let span = span_start.start..e.span.end; Ok(Expr::new(ExprKind::Unary { op: UnOp::Neg, operand: Box::new(e) }, span)) }
            Some(Token::Always)     => { self.advance(); let e = self.parse_unary_expr()?; let span = span_start.start..e.span.end; Ok(Expr::new(ExprKind::Always(Box::new(e)), span)) }
            Some(Token::Eventually) => { self.advance(); let e = self.parse_unary_expr()?; let span = span_start.start..e.span.end; Ok(Expr::new(ExprKind::Eventually(Box::new(e)), span)) }
            _ => self.parse_postfix_expr(),
        }
    }

    fn parse_postfix_expr(&mut self) -> ParseResult<Expr> {
        let mut base = self.parse_primary_expr()?;
        loop {
            match self.peek() {
                Some(Token::LParen) => {
                    let args = self.parse_call_args()?;
                    let span = base.span.start..self.span().end;
                    base = Expr::new(ExprKind::Call { callee: Box::new(base), args }, span);
                }
                Some(Token::Dot) => {
                    self.advance();
                    let member = self.expect_id()?;
                    let span = base.span.start..self.span().end;
                    if self.peek() == Some(&Token::LParen) {
                        let args = self.parse_call_args()?;
                        let span2 = base.span.start..self.span().end;
                        let method = Expr::new(ExprKind::Member { object: Box::new(base), member }, span);
                        base = Expr::new(ExprKind::Call { callee: Box::new(method), args }, span2);
                    } else {
                        base = Expr::new(ExprKind::Member { object: Box::new(base), member }, span);
                    }
                }
                Some(Token::LBrack) => {
                    self.advance();
                    let idx = self.parse_expression()?;
                    self.expect(&Token::RBrack)?;
                    let span = base.span.start..self.span().end;
                    base = Expr::new(ExprKind::Index { object: Box::new(base), index: Box::new(idx) }, span);
                }
                Some(Token::Optional) => {
                    let span = base.span.clone();
                    self.advance();
                    base = Expr::new(ExprKind::Try(Box::new(base)), span);
                }
                _ => break,
            }
        }
        Ok(base)
    }

    fn parse_call_args(&mut self) -> ParseResult<Vec<Argument>> {
        self.expect(&Token::LParen)?;
        let mut args = Vec::new();
        if self.peek() != Some(&Token::RParen) {
            loop {
                args.push(self.parse_argument()?);
                if !self.eat(&Token::Comma) { break; }
            }
        }
        self.expect(&Token::RParen)?;
        Ok(args)
    }

    fn parse_argument(&mut self) -> ParseResult<Argument> {
        // Named arg: id = expr  or  lambda arg  or  plain expr
        if let Some(Token::Id(_)) = self.peek() {
            if let Some(t) = self.tokens.get(self.pos + 1) {
                if t.node == Token::Equals {
                    let name = self.expect_id()?;
                    self.advance(); // consume =
                    let value = self.parse_expression()?;
                    return Ok(Argument { label: Some(name), value });
                }
            }
        }
        Ok(Argument { label: None, value: self.parse_expression()? })
    }

    fn parse_primary_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        match self.peek() {
            Some(Token::True)  => { self.advance(); Ok(Expr::new(ExprKind::Lit(Lit::Bool(true)), span)) }
            Some(Token::False) => { self.advance(); Ok(Expr::new(ExprKind::Lit(Lit::Bool(false)), span)) }
            Some(Token::NullLit) => { self.advance(); Ok(Expr::new(ExprKind::Lit(Lit::Null), span)) }
            Some(Token::IntLiteral(_)) => {
                if let Some(Spanned { node: Token::IntLiteral(s), span: sp }) = self.advance() {
                    let s = s.trim_end_matches(['l', 'L']).replace('_', "");
                    let v = s.parse::<i64>().unwrap_or(0);
                    Ok(Expr::new(ExprKind::Lit(Lit::Int(v)), sp))
                } else { unreachable!() }
            }
            Some(Token::DecimalLiteral(_)) => {
                if let Some(Spanned { node: Token::DecimalLiteral(s), span: sp }) = self.advance() {
                    let s = s.trim_end_matches(['f','F','d','D']).replace('_', "");
                    let v = s.parse::<f64>().unwrap_or(0.0);
                    Ok(Expr::new(ExprKind::Lit(Lit::Float(v)), sp))
                } else { unreachable!() }
            }
            Some(Token::StringLit(_)) => {
                if let Some(Spanned { node: Token::StringLit(s), span: sp }) = self.advance() {
                    let inner = s.trim_matches('"').to_owned();
                    Ok(Expr::new(ExprKind::Lit(Lit::Str(inner)), sp))
                } else { unreachable!() }
            }
            Some(Token::RawString(_)) | Some(Token::MultilineString(_)) => {
                if let Some(Spanned { node: t, span: sp }) = self.advance() {
                    let s = match t {
                        Token::RawString(s) => s.trim_start_matches("r\"").trim_end_matches('"').to_owned(),
                        Token::MultilineString(s) => s.trim_start_matches("\"\"\"").trim_end_matches("\"\"\"").to_owned(),
                        _ => unreachable!(),
                    };
                    Ok(Expr::new(ExprKind::Lit(Lit::Str(s)), sp))
                } else { unreachable!() }
            }
            Some(Token::LBrack) => {
                self.advance();
                let mut items = Vec::new();
                if self.peek() != Some(&Token::RBrack) {
                    loop {
                        items.push(self.parse_expression()?);
                        if !self.eat(&Token::Comma) { break; }
                    }
                }
                let end_span = self.span();
                self.expect(&Token::RBrack)?;
                Ok(Expr::new(ExprKind::List(items), span.start..end_span.end))
            }
            Some(Token::LCurly) if !self.is_lambda_start() => {
                // Object literal or block
                self.parse_object_or_block()
            }
            Some(Token::When) => {
                // LTL implication: when cond -> body
                let span = self.span();
                self.advance();
                let cond = self.parse_expression()?;
                self.expect(&Token::Arrow)?;
                let body = self.parse_expression()?;
                let span2 = span.start..body.span.end;
                Ok(Expr::new(ExprKind::When { cond: Box::new(cond), body: Box::new(body) }, span2))
            }
            Some(Token::Match) => self.parse_match_expr(),
            Some(Token::LParen) => {
                self.advance();
                let e = self.parse_expression()?;
                self.expect(&Token::RParen)?;
                Ok(e)
            }
            Some(Token::Id(_)) => {
                let parts = self.parse_qualified_name()?;
                let span2 = span.start..self.span().end;
                if parts.len() == 1 {
                    Ok(Expr::new(ExprKind::Ident(parts.into_iter().next().unwrap()), span2))
                } else {
                    Ok(Expr::new(ExprKind::Qualified(parts), span2))
                }
            }
            // Combinator keywords used as callees in pipeline RHS: filter(pred), map(fn), etc.
            Some(Token::Filter)    | Some(Token::Map)       | Some(Token::Reduce)    |
            Some(Token::Foreach)   | Some(Token::GroupBy)   | Some(Token::FlatMap)   |
            Some(Token::Zip)       | Some(Token::Partition) | Some(Token::Take)       |
            Some(Token::Drop)      | Some(Token::TakeWhile) | Some(Token::DropWhile) |
            Some(Token::SortBy)    | Some(Token::Distinct)  | Some(Token::Count)      |
            Some(Token::Find)      | Some(Token::Any)       | Some(Token::All)        |
            Some(Token::Join)      | Some(Token::Window)    | Some(Token::Chunk)      |
            Some(Token::Scan)      | Some(Token::Collect)   => {
                let name = self.advance().unwrap().node.to_string().to_lowercase();
                Ok(Expr::new(ExprKind::Ident(name), span))
            }
            // Type-name keywords usable as expressions (e.g. collect(x => x, List, []))
            Some(Token::ListType) | Some(Token::MapType) | Some(Token::SetType) => {
                let name = match self.advance().unwrap().node {
                    Token::ListType => "List",
                    Token::MapType  => "Map",
                    Token::SetType  => "Set",
                    _ => unreachable!(),
                };
                Ok(Expr::new(ExprKind::Ident(name.to_owned()), span))
            }
            _ => self.error("expected expression"),
        }
    }

    fn parse_object_or_block(&mut self) -> ParseResult<Expr> {
        // Heuristic: if first token after { is an identifier followed by :, it's an object literal.
        // Otherwise, treat as a block expression (used in certain contexts).
        let span = self.span();
        self.expect(&Token::LCurly)?;
        if self.peek() == Some(&Token::RCurly) {
            self.advance();
            return Ok(Expr::new(ExprKind::Object(Vec::new()), span));
        }
        // check for "key :" pattern
        let is_object = matches!(
            (self.tokens.get(self.pos), self.tokens.get(self.pos + 1)),
            (Some(Spanned { node: Token::Id(_), .. }), Some(Spanned { node: Token::Colon, .. }))
                | (Some(Spanned { node: Token::StringLit(_), .. }), Some(Spanned { node: Token::Colon, .. }))
        );
        if is_object {
            let mut fields = Vec::new();
            loop {
                let key = match self.peek() {
                    Some(Token::Id(_)) => self.expect_id()?,
                    Some(Token::StringLit(_)) => {
                        if let Some(Spanned { node: Token::StringLit(s), .. }) = self.advance() {
                            s.trim_matches('"').to_owned()
                        } else { unreachable!() }
                    }
                    _ => break,
                };
                self.expect(&Token::Colon)?;
                let value = self.parse_expression()?;
                fields.push(ObjectField { key, value });
                if !self.eat(&Token::Comma) { break; }
            }
            self.expect(&Token::RCurly)?;
            Ok(Expr::new(ExprKind::Object(fields), span))
        } else {
            // block
            let body = self.parse_block_body_inner()?;
            self.expect(&Token::RCurly)?;
            Ok(Expr::new(ExprKind::Block(body), span))
        }
    }

    fn parse_block_body(&mut self) -> ParseResult<Vec<Transformation>> {
        self.expect(&Token::LCurly)?;
        let body = self.parse_block_body_inner()?;
        self.expect(&Token::RCurly)?;
        Ok(body)
    }

    fn parse_block_body_inner(&mut self) -> ParseResult<Vec<Transformation>> {
        let mut items = Vec::new();
        while self.peek() != Some(&Token::RCurly) && !self.is_at_end() {
            if self.eat(&Token::Semi) { continue; }
            if self.peek() == Some(&Token::Let) {
                self.advance();
                let name = self.expect_id()?;
                let ty = if self.eat(&Token::Colon) { Some(self.parse_type()?) } else { None };
                self.expect(&Token::Equals)?;
                let value = self.parse_expression()?;
                items.push(Transformation::Let { name, ty, value });
            } else if self.peek() == Some(&Token::Emit) {
                let span = self.span();
                self.advance();
                let e = self.parse_expression()?;
                items.push(Transformation::Expr(Expr::new(ExprKind::Unary {
                    op: UnOp::Not, // repurpose as a carrier; codegen ignores it
                    operand: Box::new(e),
                }, span)));
            } else if self.peek() == Some(&Token::Signal) {
                self.advance();
                let e = self.parse_expression()?;
                items.push(Transformation::Expr(e));
            } else if self.peek() == Some(&Token::Assert) {
                self.advance();
                self.eat(&Token::LParen);
                let e = self.parse_expression()?;
                self.eat(&Token::RParen);
                items.push(Transformation::Expr(e));
            } else {
                items.push(Transformation::Expr(self.parse_expression()?));
            }
            self.eat(&Token::Semi);
        }
        Ok(items)
    }

    fn parse_match_expr(&mut self) -> ParseResult<Expr> {
        let span_start = self.span();
        self.expect(&Token::Match)?;
        let subject = self.parse_expression()?;
        self.expect(&Token::LCurly)?;
        let mut arms = Vec::new();
        while self.peek() != Some(&Token::RCurly) {
            arms.push(self.parse_match_arm()?);
            self.eat(&Token::Comma);
        }
        self.expect(&Token::RCurly)?;
        let span = span_start.start..self.span().end;
        Ok(Expr::new(ExprKind::Match { subject: Box::new(subject), arms }, span))
    }

    fn parse_match_arm(&mut self) -> ParseResult<MatchArm> {
        let pattern = self.parse_pattern()?;
        self.expect(&Token::Arrow)?;
        let body = if self.peek() == Some(&Token::LCurly) {
            let span = self.span();
            let body = self.parse_block_body()?;
            Expr::new(ExprKind::Block(body), span)
        } else {
            self.parse_expression()?
        };
        Ok(MatchArm { pattern, body })
    }

    fn parse_pattern(&mut self) -> ParseResult<Pattern> {
        let mut pats = vec![self.parse_and_pattern()?];
        while self.eat(&Token::UnionPipe) {
            pats.push(self.parse_and_pattern()?);
        }
        if pats.len() == 1 { Ok(pats.remove(0)) } else { Ok(Pattern::Or(pats)) }
    }

    fn parse_and_pattern(&mut self) -> ParseResult<Pattern> {
        self.parse_primary_pattern()
    }

    fn parse_primary_pattern(&mut self) -> ParseResult<Pattern> {
        match self.peek() {
            Some(Token::Wildcard) => { self.advance(); Ok(Pattern::Wildcard) }
            Some(Token::True)  => { self.advance(); Ok(Pattern::Literal(Lit::Bool(true))) }
            Some(Token::False) => { self.advance(); Ok(Pattern::Literal(Lit::Bool(false))) }
            Some(Token::NullLit) => { self.advance(); Ok(Pattern::Literal(Lit::Null)) }
            Some(Token::IntLiteral(_)) | Some(Token::DecimalLiteral(_)) | Some(Token::StringLit(_)) => {
                Ok(Pattern::Literal(self.parse_literal()?))
            }
            Some(Token::LCurly) => {
                self.advance();
                let fields = if self.peek() == Some(&Token::RCurly) {
                    Vec::new()
                } else {
                    self.parse_pattern_field_list()?
                };
                self.expect(&Token::RCurly)?;
                Ok(Pattern::ObjectDestruct(fields))
            }
            Some(Token::LBrack) => {
                self.advance();
                let mut pats = Vec::new();
                while self.peek() != Some(&Token::RBrack) {
                    pats.push(self.parse_pattern()?);
                    if !self.eat(&Token::Comma) { break; }
                }
                self.expect(&Token::RBrack)?;
                Ok(Pattern::ListDestruct(pats))
            }
            Some(Token::LParen) => {
                self.advance();
                let mut pats = vec![self.parse_pattern()?];
                while self.eat(&Token::Comma) {
                    pats.push(self.parse_pattern()?);
                }
                self.expect(&Token::RParen)?;
                if pats.len() == 1 { Ok(pats.remove(0)) } else { Ok(Pattern::Tuple(pats)) }
            }
            Some(Token::Id(_)) => {
                let name = self.parse_qualified_name()?.join(".");
                // Check for named destructure: Name { ... }
                if self.peek() == Some(&Token::LCurly) {
                    self.advance();
                    let fields = if self.peek() == Some(&Token::RCurly) {
                        Vec::new()
                    } else {
                        self.parse_pattern_field_list()?
                    };
                    self.expect(&Token::RCurly)?;
                    return Ok(Pattern::Named { constructor: name, fields });
                }
                // type pattern: name : Type
                if self.eat(&Token::Colon) {
                    let ty = self.parse_type()?;
                    return Ok(Pattern::Type { inner: Box::new(Pattern::Ident(name)), ty: Box::new(ty) });
                }
                // guard pattern: name when condition
                if self.eat(&Token::When) {
                    let cond = self.parse_expression()?;
                    return Ok(Pattern::Guard { inner: Box::new(Pattern::Ident(name.clone())), cond: Box::new(cond) });
                }
                Ok(Pattern::Ident(name))
            }
            _ => self.error("expected pattern"),
        }
    }

    fn parse_pattern_field_list(&mut self) -> ParseResult<Vec<PatternField>> {
        let mut fields = vec![self.parse_pattern_field()?];
        while self.eat(&Token::Comma) {
            if self.peek() == Some(&Token::RCurly) { break; }
            fields.push(self.parse_pattern_field()?);
        }
        Ok(fields)
    }

    fn parse_pattern_field(&mut self) -> ParseResult<PatternField> {
        match self.peek() {
            Some(Token::Wildcard) => { self.advance(); Ok(PatternField { name: "_".into(), pattern: None }) }
            Some(Token::Id(_)) => {
                let name = self.expect_id()?;
                if self.eat(&Token::Colon) {
                    let pat = self.parse_pattern()?;
                    Ok(PatternField { name, pattern: Some(Box::new(pat)) })
                } else {
                    Ok(PatternField { name, pattern: None })
                }
            }
            _ => self.error("expected pattern field"),
        }
    }

    // ── Functional combinators ────────────────────────────────────────────

    fn parse_map_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Map)?; self.expect(&Token::LParen)?;
        let func = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Map { func: Box::new(func), collection: Box::new(coll) }, span))
    }

    fn parse_filter_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Filter)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let pred = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Filter { collection: Box::new(coll), pred: Box::new(pred) }, span))
    }

    fn parse_reduce_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Reduce)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let func = self.parse_expression()?;
        let init = if self.eat(&Token::Comma) { Some(Box::new(self.parse_expression()?)) } else { None };
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Reduce { collection: Box::new(coll), func: Box::new(func), init }, span))
    }

    fn parse_foreach_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Foreach)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let func = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Foreach { collection: Box::new(coll), func: Box::new(func) }, span))
    }

    fn parse_group_by_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::GroupBy)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let key_fn = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::GroupBy { collection: Box::new(coll), key_fn: Box::new(key_fn) }, span))
    }

    fn parse_flatmap_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::FlatMap)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let func = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::FlatMap { collection: Box::new(coll), func: Box::new(func) }, span))
    }

    fn parse_zip_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Zip)?; self.expect(&Token::LParen)?;
        let left = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let right = self.parse_expression()?;
        let combiner = if self.eat(&Token::Comma) { Some(Box::new(self.parse_expression()?)) } else { None };
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Zip { left: Box::new(left), right: Box::new(right), combiner }, span))
    }

    fn parse_partition_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Partition)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let pred = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Partition { collection: Box::new(coll), pred: Box::new(pred) }, span))
    }

    fn parse_take_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Take)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let n = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Take { collection: Box::new(coll), n: Box::new(n) }, span))
    }

    fn parse_drop_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Drop)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let n = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Drop { collection: Box::new(coll), n: Box::new(n) }, span))
    }

    fn parse_take_while_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::TakeWhile)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let pred = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::TakeWhile { collection: Box::new(coll), pred: Box::new(pred) }, span))
    }

    fn parse_drop_while_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::DropWhile)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let pred = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::DropWhile { collection: Box::new(coll), pred: Box::new(pred) }, span))
    }

    fn parse_sort_by_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::SortBy)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let key_fn = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::SortBy { collection: Box::new(coll), key_fn: Box::new(key_fn) }, span))
    }

    fn parse_distinct_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Distinct)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        let eq_fn = if self.eat(&Token::Comma) { Some(Box::new(self.parse_expression()?)) } else { None };
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Distinct { collection: Box::new(coll), eq_fn }, span))
    }

    fn parse_count_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Count)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        let pred = if self.eat(&Token::Comma) { Some(Box::new(self.parse_expression()?)) } else { None };
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Count { collection: Box::new(coll), pred }, span))
    }

    fn parse_find_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Find)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let pred = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Find { collection: Box::new(coll), pred: Box::new(pred) }, span))
    }

    fn parse_any_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Any)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let pred = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Any { collection: Box::new(coll), pred: Box::new(pred) }, span))
    }

    fn parse_all_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::All)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let pred = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::All { collection: Box::new(coll), pred: Box::new(pred) }, span))
    }

    fn parse_join_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Join)?; self.expect(&Token::LParen)?;
        let left = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let right = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        self.expect(&Token::On)?; self.expect(&Token::Equals)?;
        let on = self.parse_expression()?;
        let select = if self.eat(&Token::Comma) { Some(Box::new(self.parse_expression()?)) } else { None };
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Join { left: Box::new(left), right: Box::new(right), on: Box::new(on), select }, span))
    }

    fn parse_window_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Window)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let size = self.parse_expression()?;
        let step = if self.eat(&Token::Comma) { Some(Box::new(self.parse_expression()?)) } else { None };
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Window { collection: Box::new(coll), size: Box::new(size), step }, span))
    }

    fn parse_chunk_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Chunk)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let size = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Chunk { collection: Box::new(coll), size: Box::new(size) }, span))
    }

    fn parse_scan_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Scan)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let func = self.parse_expression()?;
        let init = if self.eat(&Token::Comma) { Some(Box::new(self.parse_expression()?)) } else { None };
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Scan { collection: Box::new(coll), func: Box::new(func), init }, span))
    }

    fn parse_collect_expr(&mut self) -> ParseResult<Expr> {
        let span = self.span();
        self.expect(&Token::Collect)?; self.expect(&Token::LParen)?;
        let coll = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let func = self.parse_expression()?;
        self.expect(&Token::Comma)?;
        let init = self.parse_expression()?;
        self.expect(&Token::RParen)?;
        Ok(Expr::new(ExprKind::Collect { collection: Box::new(coll), func: Box::new(func), init: Box::new(init) }, span))
    }

    // ── Helpers ───────────────────────────────────────────────────────────

    /// A token that can serve as an identifier component in a qualified name.
    fn token_as_name(tok: &Token) -> Option<String> {
        match tok {
            Token::Id(n) => Some(n.clone()),
            // Type keywords commonly appear in import paths
            Token::ListType     => Some("List".into()),
            Token::MapType      => Some("Map".into()),
            Token::SetType      => Some("Set".into()),
            Token::StreamType   => Some("Stream".into()),
            Token::FutureType   => Some("Future".into()),
            Token::ResultType   => Some("Result".into()),
            Token::OptionType   => Some("Option".into()),
            Token::ProvenanceType => Some("Provenance".into()),
            Token::PipelineType => Some("Pipeline".into()),
            _ => None,
        }
    }

    fn parse_qualified_name(&mut self) -> ParseResult<Vec<String>> {
        let span = self.span();
        let first = match self.advance() {
            Some(Spanned { node: t, .. }) => Self::token_as_name(&t)
                .ok_or_else(|| ParseError::Unexpected {
                    msg: format!("expected identifier, got {t:?}"),
                    span: span.clone(),
                })?,
            None => return Err(ParseError::Eof),
        };
        let mut parts = vec![first];
        while self.peek() == Some(&Token::Dot) {
            let lookahead = self.tokens.get(self.pos + 1).map(|s| &s.node);
            if lookahead.and_then(Self::token_as_name).is_some() {
                self.advance(); // consume Dot
                let name = self.tokens.get(self.pos)
                    .and_then(|s| Self::token_as_name(&s.node))
                    .unwrap();
                self.advance(); // consume the name token
                parts.push(name);
            } else { break; }
        }
        Ok(parts)
    }

    fn parse_id_list(&mut self) -> ParseResult<Vec<String>> {
        let mut ids = vec![self.expect_id()?];
        while self.eat(&Token::Comma) {
            ids.push(self.expect_id()?);
        }
        Ok(ids)
    }

    fn parse_literal(&mut self) -> ParseResult<Lit> {
        match self.peek() {
            Some(Token::True)  => { self.advance(); Ok(Lit::Bool(true)) }
            Some(Token::False) => { self.advance(); Ok(Lit::Bool(false)) }
            Some(Token::NullLit) => { self.advance(); Ok(Lit::Null) }
            Some(Token::IntLiteral(_)) => {
                if let Some(Spanned { node: Token::IntLiteral(s), .. }) = self.advance() {
                    let s = s.trim_end_matches(['l', 'L']);
                    Ok(Lit::Int(s.parse().unwrap_or(0)))
                } else { unreachable!() }
            }
            Some(Token::DecimalLiteral(_)) => {
                if let Some(Spanned { node: Token::DecimalLiteral(s), .. }) = self.advance() {
                    let s = s.trim_end_matches(['f','F','d','D']);
                    Ok(Lit::Float(s.parse().unwrap_or(0.0)))
                } else { unreachable!() }
            }
            Some(Token::StringLit(_)) => {
                if let Some(Spanned { node: Token::StringLit(s), .. }) = self.advance() {
                    Ok(Lit::Str(s.trim_matches('"').to_owned()))
                } else { unreachable!() }
            }
            _ => self.error("expected literal"),
        }
    }

    fn expect_id(&mut self) -> ParseResult<String> {
        let span = self.span();
        match self.advance() {
            Some(Spanned { node: Token::Id(n), .. }) => Ok(n),
            Some(Spanned { node: t, .. }) => Err(ParseError::Unexpected {
                msg: format!("expected identifier, got {t:?}"),
                span,
            }),
            None => Err(ParseError::Eof),
        }
    }
}

/// Parse a complete program from a token stream.
pub fn parse(tokens: Vec<Spanned<Token>>) -> ParseResult<Program> {
    Parser::new(tokens).parse_program()
}
