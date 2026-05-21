mod lexer;
mod parser;
mod semantic;
mod codegen;

use std::{fs, path::PathBuf, process};

use clap::Parser as ClapParser;
use inkwell::context::Context;

use crate::{
    codegen::IrGen,
    parser::{ast::Program, parse},
    semantic::{ErrorReporter, TypeChecker, TypeEnvironment},
};

// ── CLI ───────────────────────────────────────────────────────────────────────

/// OLang compiler — Rust/Inkwell port
#[derive(ClapParser, Debug)]
#[command(name = "olangc", version, about)]
struct Cli {
    /// Source file (.olang)
    input: PathBuf,

    /// Output file
    #[arg(short = 'o', default_value = "a.out")]
    output: PathBuf,

    /// Emit LLVM IR text to stdout instead of compiling
    #[arg(long)]
    emit_ir: bool,

    /// Run semantic analysis only (no codegen)
    #[arg(long)]
    verify_only: bool,

    /// Dump the parsed AST to stdout
    #[arg(long)]
    emit_ast: bool,

    /// Optimisation level (0–3)
    #[arg(long, default_value_t = 2)]
    opt: u8,
}

// ── Entry point ───────────────────────────────────────────────────────────────

fn main() {
    let cli = Cli::parse();

    // ── Read source ──────────────────────────────────────────────────────
    let source = match fs::read_to_string(&cli.input) {
        Ok(s) => s,
        Err(e) => {
            eprintln!("olangc: cannot read '{}': {e}", cli.input.display());
            process::exit(1);
        }
    };

    // ── Parse ────────────────────────────────────────────────────────────
    let program: Program = match parse(&source) {
        Ok(p) => p,
        Err(e) => {
            eprintln!("olangc: parse error: {e}");
            process::exit(1);
        }
    };

    if cli.emit_ast {
        println!("{program:#?}");
        return;
    }

    // ── Semantic analysis ────────────────────────────────────────────────
    let mut type_env  = TypeEnvironment::new();
    let mut reporter  = ErrorReporter::default();
    let mut checker   = TypeChecker::new(&mut type_env, &mut reporter);

    // Validate all declared types in the program
    for stmt in &program.stmts {
        validate_stmt_types(&stmt.kind, &mut checker);
    }

    if reporter.has_errors() {
        eprintln!("olangc: semantic errors found.");
        process::exit(1);
    }

    if cli.verify_only {
        println!("olangc: '{}' OK.", cli.input.display());
        return;
    }

    // ── IR codegen ───────────────────────────────────────────────────────
    let context = Context::create();
    let module_name = cli.input
        .file_stem()
        .and_then(|s| s.to_str())
        .unwrap_or("module");
    let mut irgen = IrGen::new(&context, module_name);

    if let Err(e) = irgen.compile_program(&program) {
        eprintln!("olangc: codegen error: {e}");
        process::exit(1);
    }

    irgen.emit_main_stub();

    if let Err(e) = irgen.verify() {
        eprintln!("olangc: IR verification failed: {e}");
        process::exit(1);
    }

    if cli.emit_ir {
        print!("{}", irgen.emit_ir());
        return;
    }

    // Write bitcode / object
    let ir_path = cli.output.with_extension("ll");
    fs::write(&ir_path, irgen.emit_ir()).unwrap_or_else(|e| {
        eprintln!("olangc: cannot write IR: {e}");
        process::exit(1);
    });

    println!(
        "olangc: '{}' → '{}' (use `llc` + `clang` to link).",
        cli.input.display(),
        ir_path.display()
    );
}

// ── Semantic helpers ──────────────────────────────────────────────────────────

fn validate_stmt_types(kind: &parser::ast::StmtKind, checker: &mut TypeChecker<'_>) {
    use parser::ast::StmtKind;
    match kind {
        StmtKind::Function { params, ret, .. } => {
            checker.enter_scope();
            for p in params { checker.check_type(&p.ty); }
            checker.check_type(ret);
            checker.exit_scope();
        }
        StmtKind::Binding { ty, .. } => {
            if let Some(t) = ty { checker.check_type(t); }
        }
        StmtKind::TypeDecl { fields, .. } => {
            for f in fields { checker.check_type(&f.ty); }
        }
        StmtKind::Agent { members, .. } => {
            use parser::ast::AgentMember;
            for m in members {
                match m {
                    AgentMember::Stream { ty, .. } => checker.check_type(ty),
                    AgentMember::Decl(d) => validate_stmt_types(&d.kind, checker),
                    _ => {}
                }
            }
        }
        _ => {}
    }
}
