# OLang

**Agentic Orchestration Architecture for Computational Immunology**

OLang is a compiled, statically-typed domain-specific language for orchestrating fleets of AI agents that discover, simulate, formally verify, and physically synthesize genetic edits. Its first application is **#BETA-7-X** — a CRISPR strategy for inducing immune tolerance of pancreatic Beta-cells in Type 1 Diabetes (T1DM).

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
proof Beta7XSafety {
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
solver Beta7XOptimiser {
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

// All three invariants must hold before signal reaches the Executor
assert(Beta7XSafety.NoInsulinLoss.holds(results[0]))
assert(Beta7XSafety.TCellAnergy.holds(results[0]))
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
Every agent holds a 32-bit capability bitmask. Bits 0–15 are Virtual (computation, data); bits 16–31 are Physical (lab hardware). `requireCapability()` is called before every privileged operation and throws `std::runtime_error` on violation. An Analyst agent cannot synthesise a CRISPR edit even if the source code asks it to.

### Zero-cost Dimensional Analysis
`Unit<T, Dim<...>>` is a header-only C++23 template library. Adding molarity to time is a `static_assert` failure at compile time, not a runtime surprise. In Release builds, `sizeof(Molarity_d) == sizeof(double)` and the type system vanishes entirely from the generated PTX — no overhead, no branches, no metadata.

---

## Build status

| Component | Status |
|---|---|
| ANTLR4 grammar (`OLangLexer.g4`, `OLangParser.g4`) | ✅ Complete |
| `olangc` frontend (lex + parse) | ✅ Operational |
| `Unit<T>` dimensional analysis library | ✅ Complete, 8 tests passing |
| RBAC `Capability` system | ✅ Complete, 9 tests passing |
| `IsletState` digital twin | ✅ Complete |
| Gillespie KMC CUDA kernel | ✅ Written (Phase 2 link) |
| `ASTBuilder` visitor | 🔧 Phase 1 in progress |
| Semantic analyser | 🔧 Phase 1 in progress |
| LTL Rewriter | 🔧 Phase 1 in progress |
| LLVM IRGen | ⬜ Phase 2 |
| NVPTX `\|\|\|` lowering | ⬜ Phase 2 |
| `olang-rt` scheduler | ⬜ Phase 2 |
| Hardware bridge (Executor) | ⬜ Phase 3 |

---

## Quick start

```bash
git clone https://github.com/yourusername/olang.git
cd olang

# CMake auto-generates ANTLR4 C++ sources at configure time
# if tools/antlr4-complete.jar is present — no manual step needed
cmake -B build -DCMAKE_BUILD_TYPE=Debug -G Ninja
cmake --build build
ctest --test-dir build --output-on-failure
```

Expected output on a Phase 1 machine (no LLVM, no GPU):

```
=== OLang Phase 1 Configuration ===
  C++ standard  : 23
  Compiler      : GNU 13.3.0
  ANTLR4 found  : TRUE
  ANTLR4 ver    : 4.10.0
  LLVM 18 found : FALSE
  Grammar srcs  : TRUE
  CUDA backend  : OFF
====================================
100% tests passed, 0 tests failed out of 17
```

### Optional dependencies

| Dependency | Required for | Install |
|---|---|---|
| GCC ≥ 13 or Clang ≥ 16 | Everything | `sudo apt install build-essential` |
| CMake ≥ 3.22, Ninja | Build system | `sudo apt install cmake ninja-build` |
| ANTLR4 C++ runtime 4.10+ | `olangc` frontend | `sudo apt install libantlr4-runtime-dev` |
| Java 11+ | Grammar regeneration | `sudo apt install default-jre` |
| LLVM 18 | IRGen (Phase 2) | `sudo apt install llvm-18-dev` |
| CUDA Toolkit 12 | `\|\|\|` operator (Phase 2) | NVIDIA installer |
| Z3 / CVC5 | SMT solver (Phase 3) | `sudo apt install z3` |

### Compiler flags

```
olangc [options] <source.olang> -o <out>

  --emit-ast         Print the typed AST and stop
  --emit-ir          Print LLVM IR and stop
  --emit-ptx         Print PTX for ||| blocks and stop
  --verify-only      Run semantic + LTL checks; do not generate code
  --opt <0-3>        Optimisation level (default: 2)
  --target <triple>  LLVM target triple (default: host)
```

Enable the Phase 2 CUDA backend:

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Release -DOLANG_ENABLE_CUDA=ON -G Ninja
```

---

## Domain: #BETA-7-X

Type 1 Diabetes is an autoimmune disease. Cytotoxic T-cells identify pancreatic Beta-cells as foreign and destroy them, eliminating insulin production. The hypothesis underlying #BETA-7-X is that a minimal CRISPR edit — upregulating the immune checkpoint ligand PD-L1 and downregulating MHC class-I surface density on Beta-cells — can induce T-cell anergy (tolerisation) without disrupting glucose-stimulated insulin secretion.

OLang runs this experiment computationally before any physical synthesis occurs:

1. **Analyst Agent** — ingests HPAP scRNA-seq data; builds the `IsletState` baseline from real donor protein expression values (PD-L1, MHC-I, GLUT-2, insulin, ATP/ADP).
2. **Strategist Agent** — calls the SMT solver to find `(pdl1Delta, mhc1Delta)` candidates satisfying the anergy and metabolic constraints.
3. **Simulator Agent** — runs one million parallel Gillespie simulations per candidate on the GPU; runs Flux Balance Analysis on the metabolic network.
4. **Verifier** — evaluates the `Beta7XSafety` LTL proof against every simulation result. Any result that fails `NoInsulinLoss` or `TCellAnergy` is filtered before it can reach the Executor.
5. **Executor Agent** — the only `PHYSICAL`-kind agent; synthesises the approved CRISPR oligo and directs the liquid handler. Unreachable unless every `assert()` in the OLang source passes.

---

## Project structure

See [`PROJECT_STRUCTURE.md`](PROJECT_STRUCTURE.md) for a file-by-file reference.  
See [`ROADMAP.md`](ROADMAP.md) for the three-phase development plan.

---

*Principal Architect: Scott Eugene Davis — Sierra College → UC Davis → PhD (2026–2028)*