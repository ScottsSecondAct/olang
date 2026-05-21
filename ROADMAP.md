# OLang Development Roadmap

**Project:** Agentic Orchestration Architecture for Computational Immunology  
**Principal Architect:** Scott Eugene Davis  
**Timeline:** 2026–2028 (3-year project)  
**Current Status:** Phase 1 complete — Rust compiler operational

---

## Overview

OLang development follows a three-phase timeline aligned with Scott's academic progression:

- **Phase 1 (2026):** Compiler infrastructure, type safety, LLVM IR generation
- **Phase 2 (2027):** GPU backend, agent runtime, SMT solver integration
- **Phase 3 (2028):** Formal verification, hardware bridge, wet-lab validation

---

## Phase 1: Foundation (2026 — Sierra College)

### ✅ Milestone 1.1: Grammar Definition — COMPLETE

- [x] Full OLang lexical and syntactic grammar
- [x] Agent orchestration keywords (`agent`, `capability`, `stream`, `rule`)
- [x] LTL verification keywords (`proof`, `invariant`, `always`, `eventually`, `within`, `during`, `until`)
- [x] SMT solver keywords (`solver`, `satisfy`, `minimize`, `maximize`, `variable`)
- [x] Massive-parallel operator (`|||`)
- [x] Pipeline operator (`~>`)
- [x] 28 functional combinators (`map`, `filter`, `reduce`, `flatmap`, `scan`, `collect`, …)

**Status:** ✅ Delivered January 2026

---

### ✅ Milestone 1.2: Type System — COMPLETE

- [x] 14 AST type classes: Primitive, UserDefined, Pipeline, List, Map, Set, Stream, Future, Result, Option, Provenance, Function, Union, Optional
- [x] Type checker: assignability, subtyping, unification (Hindley-Milner)
- [x] Scoped symbol tables and type environment
- [x] Structured error reporting with span information
- [x] Zero-cost dimensional analysis (compile-time unit checking)

**Status:** ✅ Delivered February 2026

---

### ✅ Milestone 1.3–1.6: Rust Port & LLVM IR Generation — COMPLETE

Full rewrite from C++ / ANTLR4 to Rust:

- [x] Logos-based lexer (`src/lexer/`) — all tokens, underscore numeric separators, multiline strings
- [x] Hand-written recursive-descent parser (`src/parser/`) — full grammar, ~1,500 lines
- [x] Complete AST (`src/parser/ast.rs`) — all expression and statement forms
- [x] Inkwell LLVM 20 IR generator (`src/codegen/`) — opaque pointer support, `VarSlot<'ctx>` pattern
- [x] Semantic type checker and dimensional checker (`src/semantic/`)
- [x] Compiler driver CLI — `--emit-ast`, `--emit-ir`, `--verify-only`, `--opt`
- [x] Complex example parses and emits valid LLVM IR

**Status:** ✅ Delivered May 2026

---

## Phase 2: Orchestration & Backend (2027 — UC Davis)

### 📋 Milestone 2.1: Full Expression IR Lowering (Q1 2027)

- [ ] Control flow: `match` / pattern matching → LLVM branch/phi
- [ ] Closures and lambda capture
- [ ] Pipeline operator lowering
- [ ] LTL keyword lowering (`always`, `eventually`) → runtime assertion hooks
- [ ] LLVM optimisation passes

---

### 📋 Milestone 2.2: NVPTX Backend (`|||` Operator) (Q2 2027)

- [ ] GPU kernel generation for `|||` right-hand side
- [ ] Closure capture → PCIe host-device transfer
- [ ] Copy-on-write memory model
- [ ] Integration with Gillespie KMC kernel (`src/backend/cuda/kmc_kernel.cu`)
- [ ] Target: 1M+ parallel simulations per candidate edit

---

### 📋 Milestone 2.3: Agent Orchestration Runtime (Q3 2027)

- [ ] Agent lifecycle and message-passing
- [ ] Capability enforcement at runtime (RBAC bitmask checks)
- [ ] Pipeline execution engine and scheduler
- [ ] Event-driven reactive system for `stream` / `rule` blocks
- [ ] GPU offload for `|||` blocks

---

### 📋 Milestone 2.4: SMT Solver Integration (Q4 2027)

- [ ] Z3 / CVC5 integration for `solver` blocks
- [ ] Constraint satisfaction (`satisfy`)
- [ ] Single and multi-objective optimisation (`minimize`, `maximize`)
- [ ] T1DM edit candidate search via solver

---

## Phase 3: Validation & Synthesis (2028 — PhD Rotation)

### 📋 Milestone 3.1: Hardware Bridge — Executor Agent (Q1 2028)

- [ ] Physical lab equipment integration
- [ ] Safety interlocks and provenance tracking
- [ ] Audit logging for all PHYSICAL-capability actions
- [ ] CRISPR synthesis interface

---

### 📋 Milestone 3.2: End-to-End T1DM Pipeline (Q2 2028)

- [ ] Analyst Agent: ingest HPAP scRNA-seq data, build `IsletState` baseline
- [ ] Strategist Agent: SMT search over edit parameter space
- [ ] Simulator Agent: 1M+ parallel KMC simulations on GPU
- [ ] Verifier: LTL proof evaluation against all simulation results
- [ ] Executor Agent: physical synthesis of the approved edit
- [ ] Full wet-lab experiment

**Success criteria:** discover a viable edit, pass all safety invariants, synthesise and validate T-cell anergy in vitro.

---

### 📋 Milestone 3.3: Formal Verification & Publication (Q3 2028)

- [ ] LTL invariant validation via model checking
- [ ] Formal proof of type system soundness and RBAC correctness
- [ ] Academic publication
- [ ] PhD thesis chapter

---

## Progress summary

```
Phase 1 (Foundation):     100% ✅ Complete
Phase 2 (Orchestration):    0% (0/4 milestones)
Phase 3 (Validation):       0% (0/3 milestones)
─────────────────────────────────────────────
Overall:                   ~29% (4/11 milestones, Phase 1 done in full)
```

---

## Risk assessment

| Risk | Level | Mitigation |
|------|-------|-----------|
| LLVM / Inkwell API changes | Low | Pin inkwell version; LLVM 20 is stable |
| GPU programming (CUDA/PTX) | Medium | Existing KMC kernel as template |
| Academic timeline | Medium | Milestone planning; each phase delivers standalone value |
| Biological validation | High | Requires wet-lab access (Phase 3 contingent on PhD placement) |
| Hardware integration | High | Depends on facility access |
| Formal verification proof | High | Research novelty; no guaranteed result |

---

## Academic milestones

### Sierra College (2026)
- ✅ Milestones 1.1–1.6: Full compiler in Rust (January–May 2026)

### UC Davis Transfer (2027)
- Phase 2: Backend, runtime, SMT integration
- Begin research publication process
- Present at academic conferences (PLDI, OOPSLA, ASPLOS)

### PhD Program (2028)
- Phase 3: Validation & synthesis
- Wet-lab experiments
- Dissertation: *"Governance-as-Code for AI-Driven Biological Research"*

---

## Long-term vision (2029+)

- Expand to other autoimmune diseases (MS, RA, Crohn's)
- Open-source compiler for the computational biology community
- Peer-reviewed publications (PLDI, ASPLOS, Nature Methods)
- Regulatory-grade provenance tracking for FDA / EMA compliance

---

**Last Updated:** May 2026  
**Current Phase:** Phase 2 begins  
**Next Milestone:** 2.1 — Full expression IR lowering (Q1 2027)
