pub mod token;
pub use token::Token;

use logos::{Logos, SpannedIter};

pub type Span = std::ops::Range<usize>;

#[derive(Debug, Clone)]
pub struct Spanned<T> {
    pub node: T,
    pub span: Span,
}

impl<T> Spanned<T> {
    pub fn new(node: T, span: Span) -> Self {
        Self { node, span }
    }
}

pub struct Lexer<'src> {
    inner: SpannedIter<'src, Token>,
    source: &'src str,
}

impl<'src> Lexer<'src> {
    pub fn new(source: &'src str) -> Self {
        Self {
            inner: Token::lexer(source).spanned(),
            source,
        }
    }

    pub fn source(&self) -> &'src str {
        self.source
    }
}

impl<'src> Iterator for Lexer<'src> {
    type Item = Result<Spanned<Token>, LexError>;

    fn next(&mut self) -> Option<Self::Item> {
        let (tok, span) = self.inner.next()?;
        match tok {
            Ok(t) => Some(Ok(Spanned::new(t, span))),
            Err(_) => Some(Err(LexError { span })),
        }
    }
}

#[derive(Debug, Clone, thiserror::Error)]
#[error("unrecognized token at {span:?}")]
pub struct LexError {
    pub span: Span,
}

/// Collect all tokens, returning the first lex error if any.
pub fn tokenize(source: &str) -> Result<Vec<Spanned<Token>>, LexError> {
    Lexer::new(source).collect()
}
