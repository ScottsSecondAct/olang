# Roadmap

**Project:** OLang — Agentic Orchestration Architecture  
**Principal Architect:** Scott Eugene Davis  
**Mission:** A working compiler that orchestrates the #BETA-7-X experiment end-to-end by the conclusion of Phase 3

Three phases, three institutions, one compounding build. Each phase delivers something independently useful; each phase is also the foundation the next one stands on.

---

## Phase 1 — Foundation
**2026 · Sierra College**

The goal of Phase 1 is a compiler that can parse every valid OLang program, construct a well-typed AST, enforce dimensional analysis at compile time, enforce RBAC at load time, and report every violation with a precise source location. No machine code is generated. The deliverable is a deterministic, memory-safe frontend.

This phase runs on a standard development workstation. No GPU, no LLVM installation required.

---

### Milestone 1.1 — ANTLR4 Frontend
**Status: complete**

The grammar is the contract. Before any other layer can exist, the lexer and parser must handle every token and production in `OLangLexer.g4` and `OLangParser.g4`.

- ANTLR4 C++ runtime targets generated from both grammar files and validated against fixture programs covering all 7 statement forms and all 9 declaration forms.
- `OLangParserBaseVisitor` and `OLangParserBaseListener` establish the traversal infrastructure all subsequent compiler passes inherit from.
- CMake `execute_process` auto-generates sources at configure time when `tools/antlr4-complete.jar` is present; a `add_custom_command` sentinel reruns on grammar file changes. No manual step needed for a plain build.
- Compatibility patch (`scripts/patch_antlr4_generated.cmake`) resolves the ANTLR4 tool v4.11.1 / runtime v4.10.0 mismatch; idempotent, applied automatically.
- `olangc` reads a `.olang` file, runs the lexer and parser, and reports syntax errors in clang-compatible `file:line:col: error:` format via `DiagnosticEngine`.

---

### Milestone 1.2 — AST and Memory Model
**Status: in progress**

Raw ANTLR4 parse trees are unsuitable for compiler analysis — they are untyped, ephemeral, and tied to ANTLR4 internals. This milestone produces a typed, compact, arena-allocated AST that all subsequent passes consume.

- Full `ASTNode` hierarchy in `include/olang/frontend/AST.h`. Every node carries a `NodeKind` tag and a `SourceLocation`. Construction through raw `new` is forbidden.
- `ASTContext::make<T>()` allocates nodes from a `llvm::BumpPtrAllocator` arena (or the stdlib slab fallback from `support/llvm_fwd.h` when LLVM is absent). The entire AST is freed in O(1) when `ASTContext` goes out of scope — no per-node destructors.
- `ASTBuilder` visitor traverses the ANTLR4 CST and populates the arena with typed nodes. Covers all expression forms including the full 28-operator `functionalExpression` set, all pattern variants, all declaration forms.
- `PipelineExprNode` carries an `isParallel` flag: `false` for `~>`, `true` for `|||`. The Phase 2 NVPTX lowering pass keys on this flag to decide whether to emit a CUDA kernel.
- `TemporalExprNode` represents `always` and `eventually` at the AST level; the LTL Rewriter in Milestone 1.4 expands these into `AssertStmt` sequences.
- `olangc --emit-ast` dumps the typed AST in a human-readable form and exits.

---

### Milestone 1.3 — `Unit<T>` Dimensional Analysis
**Status: complete**

The `Unit<T>` library in `include/olang/middle/units/Unit.h` is the biological safety layer at the type system level. It is header-only and has no dependencies beyond the C++ standard library.

- 7-component SI dimension vector `Dim<Mass, Time, Length, Amount, Temperature, Current, Intensity>` encoded as a template parameter. `DimMul` and `DimDiv` metafunctions produce the correct result dimension at compile time.
- `operator+` and `operator-` require identical dimension types — no implicit conversion. `operator*` and `operator/` produce a new `Unit` with the combined dimension. Scalar multiply and divide preserve the dimension.
- Named types for the T1DM domain: `Seconds` (time), `Molarity_d` (amount·length⁻³), `Kelvin` (temperature), `MolarRate` (amount·length⁻³·time⁻¹).
- User-defined literals: `30.0_s`, `500.0_ms`, `5.0_mM`, `500.0_uM`, `310.15_K`.
- Zero-cost guarantee: `sizeof(Molarity_d) == sizeof(double)`, `alignof(Molarity_d) == alignof(double)`. In Release builds, unit-typed arithmetic compiles to the same LLVM IR as raw `double` arithmetic.
- 8 Catch2 tests passing, including compile-time `static_assert` checks on result types.

---

### Milestone 1.4 — Semantic Analyser
**Status: pending**

The semantic analyser produces a fully type-annotated AST that IRGen in Phase 2 can lower without further analysis.

- **Pass 1 — Symbol collection.** Traverse all declarations and populate a hierarchical `SymbolTable`, scoped by agent, block, and module. Every `ID` token in the source resolves to a `SymbolTable` entry or produces a diagnostic.
- **Pass 2 — Type inference and checking.** Walk all expressions bottom-up, infer `const types::Type*` for each `Expr` node, and check against declared types. Pipeline operator type compatibility is enforced: the output type of stage *n* must unify with the input type of stage *n+1*.
- **Pass 3 — `Unit<T>` integration.** Every arithmetic expression involving a biological quantity is checked at compile time. A dimensional mismatch emits a diagnostic naming both the actual and expected dimension vectors and pointing to the offending source location.
- **Pass 4 — RBAC validation.** For each `agentDeclaration`, verify that every capability in the `capability` list is a valid `Capability` enumerator, that no `VIRTUAL`-kind agent lists Physical capabilities, and that `signal` statements only target agents that hold the required Physical capability.
- **Pass 5 — LTL well-formedness.** For each `proofDeclaration`, verify that all `invariantDeclaration` bodies contain only temporally-valid expressions: no side-effecting calls, no mutation operators, no `signal` or `emit` statements.
- `olangc --verify-only` runs passes 1–5 and reports all violations without generating code.

---

### Milestone 1.5 — LTL Rewriter
**Status: pending**

The LTL Rewriter transforms `proof` / `invariant` blocks — which are declarative specifications — into imperative `AssertStmt` sequences the IRGen pass can lower to LLVM IR.

- `always(φ)` → a loop invariant `AssertStmt` inserted before each state transition point that could falsify `φ`.
- `eventually(φ) within T` → a deadline assertion that checks whether `φ` becomes true within `T` simulation seconds; if not, emits a `GovernanceSignal`.
- `during` and `until` → co-routine-style guard pairs wrapping the affected expression region.
- The rewritten AST is the input to Phase 2 IRGen. The LTL Rewriter is the last semantic-level pass.

---

### Milestone 1.6 — Test Coverage
**Status: ongoing**

- Unit tests for `Unit<T>`: 8 tests passing.
- Unit tests for RBAC `Capability`: 9 tests passing.
- Integration tests: parse round-trip for every grammar construct appearing in `examples/t1dm/beta7x_proof_of_concept.olang`.
- Negative tests: confirmed compile-time rejection of dimensional mismatches and RBAC violations.
- Target: `olangc --verify-only examples/t1dm/beta7x_proof_of_concept.olang` exits 0 with zero diagnostics before Phase 1 ends.

---

## Phase 2 — Backend
**2027 · UC Davis**

Phase 2 produces machine code. The two compilation targets are the x86-64 host binary (agent orchestration, RBAC enforcement, LTL monitoring at runtime) and the NVPTX PTX kernel (the `|||` parallel simulation block). This phase requires LLVM 18 and an NVIDIA GPU.

---

### Milestone 2.1 — LLVM IR Generation

The `IRGen` visitor traverses the type-annotated, LTL-rewritten AST and emits `llvm::Value*` nodes using `llvm::IRBuilder<>`.

- All OLang primitive types map to LLVM types: `string` → `{ptr, i64}`, `bool` → `i1`, `int` → `i32`, `double` → `double`.
- `Unit<T>` types erase to their underlying scalar type in IR — `Molarity_d` becomes `double`. No unit metadata survives into the binary.
- All 28 functional combinators lower to higher-order call patterns, passing lambda closures as captured struct pointers.
- `matchExpression` lowers to `switch` + branch instructions. The LLVM optimiser generates jump tables where density permits.
- `pipelineExpression` with `~>` lowers to `olang_rt_queue_push` / `olang_rt_queue_pop` calls into `olang-rt`. `assertStatement` lowers to the LTL monitor call.
- `pipelineExpression` with `|||` is detected by the `isParallel` flag and handed to Milestone 2.2 instead.
- `olangc --emit-ir` prints the LLVM IR for the host module and exits.

---

### Milestone 2.2 — NVPTX Backend for `|||`

The architectural centrepiece of the compiler.

- `ParallelOpLowering` pass identifies every `PipelineExprNode` with `isParallel == true`.
- Closure analysis determines which variables are captured across the `|||` boundary. Captured state is serialised into a flat struct, pinned as read-only in GPU global memory via `cudaMemcpyAsync`.
- The body of the `|||` expression is emitted into a separate `llvm::Module` targeting NVPTX. Compile flags: `-arch=sm_86 -O3 --use_fast_math`. The `kmc_kernel.cu` Gillespie kernel is the Phase 1 prototype of this output.
- The host-side stub emits: `cudaMalloc` for baseline and delta arrays, `kmc_init_rng` kernel launch, `kmc_gillespie_step` kernel launch, `cudaMemcpy` of `IsletDelta` results back to host, delta merge into result collection.
- Copy-on-write paged memory model: the `IsletState` baseline is read-only in global memory; each thread writes only the fields that diverge from baseline into a private `IsletDelta`. Unchanged fields are never copied.
- `olangc --emit-ptx` prints the PTX for the `|||` module and exits.

---

### Milestone 2.3 — `olang-rt` Runtime Library

The runtime library that compiled OLang programs link against.

- **Agent scheduler** — manages `initialize()` / `shutdown()` lifecycle for the agent fleet; routes `~>` messages through a lock-free MPSC queue; enforces per-agent capability masks at dispatch time.
- **LTL monitor** — a state machine running on the host that evaluates the `AssertStmt` sequences produced by the LTL Rewriter after each pipeline step. A failed assertion triggers `EmitGovernanceSignal`, which calls `std::terminate` after logging the violated invariant, the step number, and the provenance hash of the result that caused it.
- **RBAC enforcer** — `requireCapability` guards in every privileged operation. At runtime, `PHYSICAL` capability checks additionally verify that the calling agent's `AgentKind == PHYSICAL`; a `VIRTUAL`-kind agent with a spoofed capability mask cannot reach hardware.
- **SMT bridge** — wraps the Z3 or CVC5 C++ API. `solver` blocks compile to initialisation calls into this bridge; `satisfy` constraints become Z3 assertions; `minimize` becomes a Z3 optimisation objective. The solver runs at program start before the pipeline executes.

---

### Milestone 2.4 — End-to-End Compilation

- `olangc examples/t1dm/beta7x_proof_of_concept.olang -o beta7x` produces a working binary.
- The binary runs the KMC simulation with 1,000,000 threads per candidate on a single GPU.
- The `Beta7XSafety` LTL monitor halts the pipeline if any invariant is violated before `signal ExecutorAgent` is reached.
- Benchmark target: 1 million Gillespie steps complete in under 100 ms on RTX 3090 (revised once hardware access is confirmed).

---

## Phase 3 — Validation
**2028 · PhD Rotation Lab**

Phase 3 closes the loop between digital and physical. The Executor Agent — blocked by RBAC throughout Phases 1 and 2 — is connected to real lab hardware and given real HPAP data.

This phase is contingent on lab placement. Hardware targets are indicative.

---

### Milestone 3.1 — Hardware Bridge

The `PHYSICAL`-kind Executor Agent receives concrete implementations of its three capabilities.

- `SynthesizeCRISPR` — communicates with the CRISPR oligo synthesizer (Twist Bioscience API or in-house instrument). Accepts the approved `CrisprEdit` from the pipeline, validates its provenance hash and `generationId`, submits the synthesis order.
- `ControlLabRobotics` — commands the liquid handling robot for transfection plate preparation.
- `ReadLabSensor` — polls bioreactor optical density and pH sensors; feeds live data back into the `IsletState` stream for the Analyst Agent.

All three entry points call `requireCapability` before any hardware interaction. A `VIRTUAL` agent with a fabricated mask cannot reach them.

The governance invariant established in Phase 1 — that the Executor is unreachable unless all LTL proofs hold — remains structurally enforced: `signal ExecutorAgent` can only be reached in the compiled binary after the three `assert()` calls in the OLang source pass.

---

### Milestone 3.2 — HPAP Dataset Integration

The Analyst Agent is connected to the Human Pancreas Analysis Program (HPAP) scRNA-seq data portal rather than the synthetic `IsletState` defaults used in simulation.

- `ReadScrnaSeq` handler parses donor-specific islet cell profiling data and initialises `betaCells[].surface` with real measured protein expression values (PD-L1, MHC-I, insulin, GLUT-2).
- T-cell affinity distributions are drawn from HPAP TCR sequencing data for the same donor.
- `provenanceHash` records the HPAP donor ID and sequencing run; `generationId` increments with each simulation batch. Every result in the output carries a complete audit trail to its source data.

---

### Milestone 3.3 — Formal Proof of #BETA-7-X

`examples/t1dm/beta7x_proof_of_concept.olang` compiles and runs end-to-end with real HPAP donor data.

- `Beta7XOptimiser` finds the minimum-perturbation `(pdl1Delta, mhc1Delta)` pair satisfying the anergy and metabolic constraints.
- KMC simulation of the immunological synapse with `pdl1Delta` applied: target outcome is that greater than 70% of simulated T-cell interactions result in `Anergic` state within 3600 simulated seconds.
- FBA verifies that the edited Beta-cell maintains glucose-stimulated insulin secretion (GSIS) steady-state flux after the edit.
- All three `Beta7XSafety` invariants (`NoInsulinLoss`, `TCellAnergy`, `NoOffTargetEdits`) hold against the simulation results. The LTL monitor does not halt the pipeline.
- `signal ExecutorAgent.approvedEdit` is reached. The physical synthesis order is issued.

---

### Milestone 3.4 — Thesis and Release

- Results are documented in the PhD thesis with OLang source listings as reproducibility artifacts.
- `olangc --verify-only` on the reference `.olang` file is a zero-configuration reproduction test.
- The compiler, runtime, and reference `.olang` programs are released as open-source software.
- A preprint or paper describes the #BETA-7-X result; OLang is the mechanism by which the claim is reproducible.

---

## Dependency timeline

```
                  2026            2027            2028
                  Phase 1         Phase 2         Phase 3

GCC/Clang 23      ████████████████████████████████████████
CMake + Ninja     ████████████████████████████████████████
ANTLR4 runtime    ████████████████████████████████████████
Catch2            ████████████████████████████████████████ (FetchContent)
ANTLR4 tool JAR   ████ committed — generate once
LLVM 18           ────────────────████████████████████████
CUDA 12 + nvcc    ────────────────████████████████████████
Z3 / CVC5         ────────────────────────────████████████
HPAP data access  ────────────────────────────████████████
Lab hardware      ────────────────────────────────────████
```

---

## What is out of scope

**A general-purpose language.** OLang is a DSL for one class of problem. Constructs that are not needed for the #BETA-7-X orchestration problem are not implemented.

**Distributed multi-machine execution.** The `|||` operator targets a single GPU node. Multi-node distribution is a post-PhD extension.

**IDE / language-server integration.** The clang-compatible diagnostic format means VS Code and CLion surface errors without custom plugins. A full LSP server is not a Phase 1–3 deliverable.

**Support for other target organs or diseases.** The compiler and language are general. The runtime structs (`IsletState`, `ProteinPanel`, `TCellState`) and KMC rate constants are specific to the pancreatic islet / T-cell system. Adapting to a different biological target requires new domain structs but no language or compiler changes.