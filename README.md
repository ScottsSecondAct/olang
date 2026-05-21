# OLang
[![Open Source](https://img.shields.io/badge/Open%20Source-Yes-green.svg)](https://github.com/ScottsSecondAct/some) [![License: MIT](https://img.shields.io/badge/License-MIT-blue.svg)](https://opensource.org/licenses/MIT) ![AI Assisted](https://img.shields.io/badge/AI%20Assisted-Claude-blue?logo=anthropic)

**Agentic Orchestration Architecture for Computational Immunology**

OLang is a compiled, statically-typed domain-specific language for orchestrating fleets of AI agents that discover, simulate, formally verify, and physically synthesize genetic edits. Its first application targets **Type 1 Diabetes (T1DM)** — computationally discovering and formally verifying CRISPR edits that may induce immune tolerance of pancreatic Beta-cells.

The language is built around a single architectural guarantee: **no physical lab action can execute unless every Linear Temporal Logic invariant in the governing `proof` block holds**. That constraint is enforced by the compiler, the runtime, and the RBAC capability system simultaneously.

---

## Language sample

```olang
// Agents declare typed capability masks — enforced at binary level
agent SimulatorAgent {
  capability RunKMCSimulation, RunFBASimulation, RunParallelKernel
  stream isletIn : Stream<IsletState>
}

// Formal proofs compiled into runtime LTL assertions
proof T1DMSafety {
  invariant NoInsulinLoss {
    always(
      when BetaCell.isEdited == true ->
        eventually(BetaCell.isSecreting == true)
    )
  }
  invariant TCellAnergy {
    always(
      when TCell.state == Engaged ->
        eventually(TCell.state == Anergic) within 3600.0
    )
  }
}

// SMT solver: declare the goal, not the search loop
solver EditOptimiser {
  variable pdl1Delta : float in 0.0 ..= 5.0
  variable mhc1Delta : float in 0.0 ..= 1.0
  satisfy  { pdl1Delta > 1.5; mhc1Delta < 0.6; }
  minimize   pdl1Delta + (1.0 - mhc1Delta)
}

// ||| is the massive-parallel operator — each side becomes a PTX kernel
let results =
  editCandidates
  ~> filter(c  => c.safetyScore > 0.95)
  ~> map(c     => baseline ||| SimulatorAgent.runKMC(c, 1_000_000))
  ~> filter(r  => r.proofResult == "VERIFIED")
  ~> sort_by(r => r.anergicFraction)

// All invariants must hold before the signal reaches the Executor
assert(T1DMSafety.NoInsulinLoss.holds(results[0]))
assert(T1DMSafety.TCellAnergy.holds(results[0]))
signal ExecutorAgent.approvedEdit results[0]
```

---

## Core language features

### `|||` — Massive-Parallel Operator

The architectural centrepiece. Defines a hardware compilation boundary: the LLVM NVPTX backend lowers the right-hand expression into a PTX kernel. Closure capture ships state across the PCIe bus. The Gillespie KMC kernel in `src/backend/cuda/kmc_kernel.cu` is the direct target of this operator — one CUDA thread per independent islet simulation, one million threads per candidate edit.

### `~>` — Pipeline Operator

Type-safe, asynchronous data flow between agents. Composed with 28 functional combinators (`map`, `filter`, `reduce`, `flatmap`, `scan`, `collect`, and more) into a lazy evaluation graph the runtime schedules across the agent mesh.

### `proof` / `invariant` — LTL Verification

`always`, `eventually`, `within`, `during`, and `until` are first-class keywords compiled by the LTL Rewriter into branching `AssertStmt` nodes. The Governance Agent evaluates them at runtime after each pipeline step. A violated invariant emits a `GovernanceSignal` that halts the pipeline before the Executor Agent can act.

### `solver` / `satisfy` / `minimize` — Declarative SMT

State the constraints and the objective; the runtime calls Z3 or CVC5. No hand-written optimisation loop. Variable domains (`in 0.0 ..= 5.0`) become bound constraints; `satisfy` blocks become assertions; `minimize` becomes the optimisation objective.

### `agent` / `capability` — RBAC at Binary Level

Every agent holds a 32-bit capability bitmask. Bits 0–15 are Virtual (computation, data); bits 16–31 are Physical (lab hardware). Capability checks run before every privileged operation. An Analyst agent cannot synthesise a CRISPR edit even if the source code asks it to.

### Zero-cost Dimensional Analysis

Dimensional types are validated at compile time. Adding molarity to time is a type error, not a runtime surprise. In Release builds the type system vanishes entirely from the generated code — no overhead, no branches, no metadata.

---

## Build status

| Component | Status |
| --- | --- |
| Logos lexer | ✅ Complete |
| Recursive-descent parser | ✅ Complete |
| AST (14 type classes, full expression set) | ✅ Complete |
| Type system infrastructure | ✅ Complete |
| Symbol tables & type environment | ✅ Complete |
| Inkwell LLVM 20 IR generation | ✅ Operational |
| **Rust port (from C++ / ANTLR4)** | ✅ **COMPLETE** |
| LTL runtime verification | 🔧 Phase 2 |
| NVPTX `\|\|\|` lowering | 🔧 Phase 2 |
| SMT solver integration | 🔧 Phase 2 |
| Agent orchestration runtime | 🔧 Phase 2 |
| Hardware bridge (Executor) | ⬜ Phase 3 |

---

## Quick start

```bash
git clone https://github.com/ScottsSecondAct/olang2.git
cd olang2

# Requires Rust toolchain and LLVM 20
cargo build --release

# Parse an OLang source file and dump the AST
./target/release/olangc --emit-ast examples/t1dm/t1dm_proof_of_concept.olang

# Emit LLVM IR
./target/release/olangc --emit-ir examples/t1dm/t1dm_proof_of_concept.olang
```

### Compiler flags

```
olangc [options] <source.olang>

  --emit-ast       Print the parsed AST and stop
  --emit-ir        Emit LLVM IR and stop
  --verify-only    Run semantic checks; do not generate code
  --opt <0-3>      Optimisation level (default: 2)
  -o <file>        Output file
```

### Dependencies

| Dependency | Required for | Install |
| --- | --- | --- |
| Rust ≥ 1.75 | Everything | `curl https://sh.rustup.rs -sSf \| sh` |
| LLVM 20 + clang-20 | IR generation | `sudo apt install llvm-20 llvm-20-dev clang-20` |
| CUDA Toolkit 12 | `\|\|\|` operator (Phase 2) | NVIDIA installer |
| Z3 / CVC5 | SMT solver (Phase 3) | `sudo apt install z3` |

---

## Domain: Type 1 Diabetes

Type 1 Diabetes is an autoimmune disease. Cytotoxic T-cells identify pancreatic Beta-cells as foreign and destroy them, eliminating insulin production. OLang's T1DM application explores whether targeted genetic edits to Beta-cells can induce T-cell anergy — immune tolerance — without disrupting glucose-stimulated insulin secretion. The specific edit hypothesis is an open research question.

OLang runs this experiment computationally before any physical synthesis occurs:

1. **Analyst Agent** — ingests HPAP scRNA-seq data; builds the `IsletState` baseline from real donor protein expression values.
2. **Strategist Agent** — calls the SMT solver to generate candidate edit parameters satisfying anergy and metabolic constraints.
3. **Simulator Agent** — runs one million parallel Gillespie simulations per candidate on the GPU; runs Flux Balance Analysis on the metabolic network.
4. **Verifier** — evaluates the `T1DMSafety` LTL proof against every simulation result. Any result that fails `NoInsulinLoss` or `TCellAnergy` is filtered before it can reach the Executor.
5. **Executor Agent** — the only `PHYSICAL`-kind agent; synthesises the approved CRISPR oligo and directs the liquid handler. Unreachable unless every `assert()` in the OLang source passes.

---

## Project structure

See [`PROJECT_STRUCTURE.md`](PROJECT_STRUCTURE.md) for a file-by-file reference.  
See [`ROADMAP.md`](ROADMAP.md) for the development plan.

---

## Recent progress

### May 2026: Rust port complete ✅

Full rewrite from C++ (ANTLR4 + CMake + LLVM C++ API) to Rust:

- Logos-based lexer with all OLang tokens (underscore numeric separators, multiline strings, priority disambiguation)
- Hand-written recursive-descent parser covering the full grammar
- Complete AST: 14 type classes, all expression and statement forms
- Inkwell-based LLVM 20 IR generator with opaque-pointer support
- Semantic type checker, symbol tables, and dimensional checker
- Compiler driver CLI (clap): `--emit-ast`, `--emit-ir`, `--verify-only`, `--opt`

---

*Principal Architect: Scott Eugene Davis — Sierra College → UC Davis → PhD (2026–2028)*
