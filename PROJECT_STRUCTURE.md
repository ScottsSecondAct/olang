# Project Structure

A file-by-file reference. The layout follows LLVM conventions: public interfaces live in `include/`, implementations in `src/`, executables in `tools/`, grammars in `grammar/`.

```
olang/
├── grammar/                        ANTLR4 source grammars (source of truth for syntax)
├── include/olang/
│   ├── frontend/                   Compiler frontend interfaces
│   │   ├── AST.h                   Arena-allocated AST node hierarchy
│   │   ├── ASTContext.h            BumpPtrAllocator arena for all nodes
│   │   ├── Diagnostic.h            Structured error / warning engine
│   │   └── SourceLocation.h        Compact 12-byte source position
│   ├── middle/
│   │   ├── types/Type.h            Type system base (Phase 1 stub)
│   │   └── units/Unit.h            Zero-cost dimensional analysis library
│   ├── runtime/
│   │   ├── agents/Agent.h          Abstract base class for all runtime agents
│   │   ├── agents/Capability.h     32-bit RBAC capability bitmasks and role masks
│   │   └── bio/IsletState.h        Pancreatic islet digital twin (GPU-copyable)
│   └── support/
│       └── llvm_fwd.h              LLVM portability shim (stdlib fallback if absent)
├── src/
│   ├── frontend/
│   │   ├── Diagnostic.cpp          DiagnosticEngine::printAll() implementation
│   │   └── generated/              ANTLR4-generated C++ (committed; auto-regenerated)
│   └── backend/cuda/
│       └── kmc_kernel.cu           Gillespie KMC CUDA kernel — target of ||| lowering
├── tools/olangc/
│   └── main.cpp                    Compiler driver executable
├── tests/unit/
│   ├── middle/test_unit_dimensional_analysis.cpp
│   └── runtime/test_capability_rbac.cpp
├── examples/t1dm/
│   └── beta7x_proof_of_concept.olang
├── scripts/
│   ├── generate_grammar.sh         Manual grammar regeneration helper
│   └── patch_antlr4_generated.cmake  ANTLR4 tool/runtime version compatibility fix
├── cmake/
│   └── OLangCompilerFlags.cmake    Shared compiler warning / sanitiser flags
├── tools/
│   └── antlr4-complete.jar         ANTLR4 tool JAR (committed; used at configure time)
└── CMakeLists.txt
```

---

## grammar/

The ANTLR4 grammar files are the authoritative specification of OLang syntax. Every keyword, operator, and production rule is defined here first; all other layers are derived from them.

### `OLangLexer.g4`

Tokenises raw UTF-8 source into a typed token stream. Defines:

- **Core keywords** — `let`, `def`, `type`, `import`, `from`, `as`, `with`, `match`, `when`, `where`, `in`
- **Agent/orchestration keywords** — `agent`, `capability`, `stream`, `rule`, `emit`, `signal`
- **LTL verification keywords** — `proof`, `invariant`, `assert`, `always`, `eventually`, `during`, `until`, `within`
- **Solver keywords** — `solver`, `satisfy`, `minimize`, `maximize`, `variable`
- **Functional operators** — all 28 combinators: `map`, `filter`, `reduce`, `foreach`, `group_by`, `flatmap`, `zip`, `partition`, `take`, `drop`, `take_while`, `drop_while`, `sort_by`, `distinct`, `count`, `find`, `any`, `all`, `join`, `window`, `chunk`, `scan`, `collect`, and more
- **Type system tokens** — `int`, `long`, `float`, `double`, `bool`, `string`, `List`, `Map`, `Set`, `Pipeline`, `Stream`, `Future`, `Result`, `Option`, `Provenance`
- **Special operators** — `↦` / `~>` (pipeline), `|||` (massive-parallel GPU boundary), `=>` (lambda), `??` (null-coalesce), `@` (biological mutation site), `→` / `-->` (biological transformation), `..` / `..=` / `..<` (range)
- **Unicode identifier rules** — `ID_START` and `ID_CONTINUE` use `\p{L}` Unicode letter properties; identifiers can begin with any Unicode letter or `_`

### `OLangParser.g4`

Full recursive-descent grammar producing a concrete syntax tree (CST). Major sections:

- **Program structure** — `program`, `statementList`, `statement` (7 forms)
- **Declarations** (9 forms) — `importDeclaration`, `bindingDeclaration`, `functionDeclaration`, `pipelineDeclaration`, `typeDeclaration`, `annotationTypeDeclaration`, `agentDeclaration`, `solverDeclaration`, `proofDeclaration`
- **Expression hierarchy** — `lambdaExpression` → `functionalExpression` → `pipelineExpression` (supports both `~>` and `|||`) → `nullCoalesceExpression` → `ternaryExpression` → `logicalOrExpression` → … → `unaryExpression` (LTL prefix operators `always`, `eventually` inserted here) → `postfixExpression`
- **LTL infix operators** — `within`, `during`, `until` appear in `relationalExpression`, giving them lower precedence than arithmetic but higher than logical operators
- **Pattern matching** — `wildcardPattern`, `literalPattern`, `identifierPattern`, `destructurePattern` (object, list, tuple, named), `rangePattern`, `typePattern`, `guardPattern`
- **Biological constructs** — `mutationExpression` with `mutationSite` (position or range) and `mutationChange` (allele substitution via `→`)
- **Agent members** — `CAPABILITY idList`, `STREAM ID : type`, `RULE … WHEN expression → blockExpression`, nested declarations
- **Solver members** — `VARIABLE ID : type (IN expression)?`, `SATISFY { ... }`, `MINIMIZE expression`
- **Proof members** — `INVARIANT ID { expressionStatement* }`

### `grammar/README.md`

Style conventions for modifying the grammar: new operator tokens go in the Lexer; new productions in the Parser; keep the Lexer free of parser-level semantics.

---

## include/olang/frontend/

### `SourceLocation.h`

A compact, 12-byte `(line, col, fileId)` value type stored in every `ASTNode`. Inspired by Clang's `SourceLocation` but simplified for Phase 1's single-file model. Construction is constexpr; `isValid()` returns false for default-constructed instances. The `static_assert(sizeof(SourceLocation) <= 12)` is a regression guard.

```cpp
auto loc = SourceLocation::from(42, 7);
loc.line();    // 42
loc.col();     // 7
loc.isValid(); // true
```

### `Diagnostic.h`

Structured diagnostic collection. Four severity levels: `Note`, `Warning`, `Error`, `Fatal`. Any `Error` or `Fatal` sets `hasErrors() == true`, which the compiler driver checks between passes. Each `Diagnostic` carries a `SourceLocation`, a message string, and an optional hint (fix-it suggestion).

```cpp
DiagnosticEngine diags;
diags.error(loc, "undefined variable 'pdl1Delta'");
diags.warning(loc, "Unit<T> mismatch: expected Seconds, found Molarity_d",
                   "did you mean 2.0_s instead of 2.0_mM?");
diags.printAll("beta7x.olang");   // → stderr in clang format
if (diags.hasErrors()) return 1;
```

### `AST.h`

The immutable, arena-allocated AST node hierarchy. All nodes inherit from `ASTNode`, carrying a `NodeKind` tag and a `SourceLocation`. Construction through raw `new` is forbidden — all nodes are created via `ASTContext::make<T>()`.

Key design points:
- `Expr` nodes carry a `const types::Type*` resolved during semantic analysis; null until then.
- `Decl` nodes carry an interned `llvm::StringRef` name (stable pointer into the arena).
- `PipelineExprNode` carries an `isParallel` flag (`false` → `~>`, `true` → `|||`). The NVPTX lowering pass in Phase 2 keys on this flag.
- `TemporalExprNode` covers `always` and `eventually`; the LTL Rewriter expands these into `AssertStmt` sequences.

Node categories:

| Category | Representative nodes |
|---|---|
| Declarations | `AgentDeclNode`, `SolverDeclNode`, `ProofDeclNode`, `InvariantDeclNode`, `BindingDeclNode`, `FunctionDeclNode` |
| Statements | `EmitStmt`, `SignalStmt`, `AssertStmt`, `AssignStmt` |
| Expressions | `PipelineExprNode` (`~>` / `|||`), `TemporalExprNode` (`always`, `eventually`), `NullCoalesceExpr`, `BinaryExpr`, `CallExpr` |
| Patterns | `WildcardPat`, `ObjectDestructPat`, `ListDestructPat`, `RangePat`, `TypePat`, `GuardPat` |
| Types | `PrimitiveType`, `PipelineType`, `StreamType`, `FutureType`, `ProvenanceType`, `FunctionType`, `UnionType` |

### `ASTContext.h`

The arena that owns the entire AST for one compilation unit. Backed by `llvm::BumpPtrAllocator` when LLVM 18 is installed; falls back to the stdlib slab allocator in `support/llvm_fwd.h` otherwise. The `intern()` method copies a `string_view` into the arena and returns a stable `llvm::StringRef`. All memory is freed in O(1) when the `ASTContext` goes out of scope.

---

## include/olang/middle/

### `units/Unit.h`

Zero-cost dimensional analysis for biological quantities. The 7-component SI dimension vector `[mass, time, length, amount, temperature, current, intensity]` is encoded as a template parameter `Dim<M,T,L,A,Θ,I,J>`. Arithmetic operators use `DimMul` and `DimDiv` metafunctions to produce the correct result type at compile time. Same-dimension addition and subtraction are allowed; mixed-dimension addition is a compile error.

```cpp
Molarity_d c{5.0_mM};   // Dim<0,0,-3,1,0,0,0>
Seconds    t{2.0_s};    // Dim<0,1,0,0,0,0,0>
MolarRate  r = c / t;   // Dim<0,-1,-3,1,0,0,0> — correct, compiles
auto bad = c + t;       // error: no matching operator+ — caught at compile time
```

Named types:

| Type | Dimension | Literals |
|---|---|---|
| `Seconds` | time¹ | `30.0_s`, `500.0_ms` |
| `Molarity_d` | amount¹ · length⁻³ | `5.0_mM`, `500.0_uM` |
| `Kelvin` | temperature¹ | `310.15_K` |
| `MolarRate` | amount¹ · length⁻³ · time⁻¹ | derived by division |

`static_assert(sizeof(Seconds) == sizeof(double))` — the wrapper is layout-identical to its underlying scalar in all build modes.

### `types/Type.h`

Phase 1 stub. Declares the `olang::ast::types::Type` virtual base class. The full hierarchy — `PrimitiveType`, `PipelineType<A,B>`, `ProvenanceType<T>`, union types, generic parameter instantiation — is built during the Phase 1 semantic analyser milestone.

---

## include/olang/runtime/

### `agents/Capability.h`

The RBAC capability system. Each capability is a named bit in a `uint32_t`. Bits 0–15 (`VirtualMask = 0x0000FFFF`) cover computation and data; bits 16–31 (`PhysicalMask = 0xFFFF0000`) cover lab hardware and are exclusive to `PHYSICAL`-kind agents.

```
Bit  0  ReadScrnaSeq           Parse HPAP / scRNA-seq logs
Bit  1  WriteSimulationResult  Persist KMC / FBA output
Bit  2  ReadGenomicIndex       Query CRISPR target database
Bit  3  RunKMCSimulation       Gillespie KMC (VIRTUAL)
Bit  4  RunFBASimulation       Flux Balance Analysis (VIRTUAL)
Bit  5  RunParallelKernel      Launch ||| CUDA kernels
Bit  6  EvaluateLTLProof       Runtime LTL monitor
Bit  7  EmitGovernanceSignal   Halt pipeline on invariant violation
Bit  8  InvokeSMTSolver        Call Z3 / CVC5
Bit 16  SynthesizeCRISPR       Talk to oligo synthesizer  (PHYSICAL)
Bit 17  ControlLabRobotics     Move liquid handler          (PHYSICAL)
Bit 18  ReadLabSensor          Poll bioreactor sensors      (PHYSICAL)
```

Pre-defined role masks in `namespace olang::runtime::roles`:

| Role | Capabilities granted |
|---|---|
| `Analyst` | `ReadScrnaSeq`, `ReadGenomicIndex` |
| `Strategist` | `InvokeSMTSolver`, `ReadGenomicIndex` |
| `Simulator` | `RunKMCSimulation`, `RunFBASimulation`, `RunParallelKernel`, `WriteSimulationResult` |
| `Verifier` | `EvaluateLTLProof`, `EmitGovernanceSignal` |
| `Executor` | `SynthesizeCRISPR`, `ControlLabRobotics`, `ReadLabSensor` |

`requireCapability(granted, required, opName)` throws `std::runtime_error` if the agent's mask does not include the required capability. Called at the entry point of every privileged operation in every agent implementation.

### `agents/Agent.h`

Abstract base class for all OLang runtime agents. Non-copyable (agents own resources and hardware connections). Pure-virtual `initialize()` and `shutdown()` define the lifecycle; the `require()` convenience method wraps `requireCapability` using the agent's own capability mask. `AgentKind` is one of `VIRTUAL`, `PHYSICAL`, or `ATOMIC`.

### `bio/IsletState.h`

The canonical digital twin of the pancreatic islet microenvironment. This is the struct pinned in GPU global memory when `|||` fires. `static_assert(std::is_trivially_copyable_v<IsletState>)` is a hard requirement for `cudaMemcpy`.

```
IsletState
 ├── betaCells[1000]
 │    ├── surface: ProteinPanel
 │    │    ├── pdl1   Molarity_d   PD-L1 surface density (immune checkpoint)
 │    │    ├── mhc1   Molarity_d   MHC class-I density
 │    │    ├── ins    Molarity_d   Intracellular insulin
 │    │    ├── glut2  Molarity_d   GLUT-2 transporter
 │    │    ├── atp    Molarity_d   ATP
 │    │    └── adp    Molarity_d   ADP
 │    ├── glucoseIntracellular  Molarity_d
 │    ├── isSecreting  bool
 │    ├── isEdited     bool
 │    ├── editSitePosition  uint32_t
 │    └── editAlleleHash    uint32_t
 ├── tCells[10000]
 │    ├── state: TCellState { Naive, Primed, Engaged, Anergic, Exhausted }
 │    ├── tcr_affinity    Molarity_d
 │    └── engagementTime  Seconds
 ├── temperature  Kelvin   (default 310.15_K = 37 °C)
 ├── simTime      Seconds
 ├── activeBetaCells  uint32_t
 ├── activeTCells     uint32_t
 ├── provenanceHash   uint64_t   (which agent / donor produced this snapshot)
 └── generationId     uint32_t
```

Child simulations produced by `|||` store only an `IsletDelta` — the fields that diverge from this baseline. Reads fall back to the shared baseline until a field is written (copy-on-write paged memory model).

---

## include/olang/support/

### `llvm_fwd.h`

A portability shim. When `OLANG_HAVE_LLVM` is defined (set by CMake when `llvm-18-dev` is found), this header is a no-op and the real LLVM types are used. Without LLVM, it provides drop-in stdlib replacements:

| LLVM type | Stdlib replacement |
|---|---|
| `llvm::StringRef` | `std::string_view` |
| `llvm::ArrayRef<T>` | `std::span<const T>` |
| `llvm::BumpPtrAllocator` | 64 KiB slab allocator backed by `std::malloc` |

Frontend and middle headers include only this shim — never LLVM headers directly. No source changes are required when LLVM is added.

---

## src/frontend/

### `Diagnostic.cpp`

Implements `DiagnosticEngine::printAll()`. Iterates the diagnostic list and writes each entry to `stderr` in clang-compatible format:

```
beta7x.olang:47:12: error: undefined variable 'pdl1Delta'
  hint: did you mean 'pdl1' declared on line 23?
```

IDEs with clang error parsing (VS Code C/C++, CLion) will link directly to the source location.

### `generated/`

ANTLR4-generated C++ committed to the repository so that a Java runtime is not required for a plain build. Regenerated automatically during CMake configure when `tools/antlr4-complete.jar` is present, or manually via `scripts/generate_grammar.sh`.

| File | Role |
|---|---|
| `OLangLexer.cpp/.h` | Lexer state machine |
| `OLangParser.cpp/.h` | Recursive-descent parser; one method per grammar rule |
| `OLangParserVisitor.h` | Pure-virtual visitor — implemented by `ASTBuilder` |
| `OLangParserBaseVisitor.h` | Default no-op visitor — override only the rules you need |
| `OLangParserListener.h` | Event listener interface for tooling passes |
| `OLangParserBaseListener.h` | Default no-op listener |

The committed files include a two-line compatibility patch (`scripts/patch_antlr4_generated.cmake`) that replaces `antlr4::internal::OnceFlag` with `std::once_flag` — required because the ANTLR4 tool JAR (v4.11.1) generates code that the Ubuntu-packaged runtime (v4.10.0) does not recognise. Semantically identical; zero behavioural change.

---

## src/backend/cuda/

### `kmc_kernel.cu`

The Gillespie Kinetic Monte Carlo CUDA kernel. This is the direct compilation target of the `|||` operator — one thread per independent simulation, all reading a shared read-only `IsletState` baseline from global memory and writing a private `IsletDelta`.

**Algorithm (one thread = one simulation step):**

1. Read `pdl1`, `mhc1`, `tcr_affinity` from the global baseline (no divergent write yet — free under the CoW model).
2. Compute three reaction propensities: TCR binding (`kTCR_on × mhc1 × affinity`), TCR unbinding (`kTCR_off`), PD-1/PD-L1 binding (`kPDL1_on × pdl1`).
3. Draw Δt from Exp(a_total) using `curand_uniform`; select reaction proportional to its propensity.
4. If TCR binding fires and `pdl1 > kAnergyThreshold (0.7)`, transition T-cell to `Anergic`; otherwise to `Engaged`.
5. Write changed fields to the thread-local `IsletDelta` (first write triggers copy-on-write page allocation on the host side).

Host-side entry point: `launch_kmc_step(d_baseline, d_deltas, d_rng, nSims, betaCellIdx, tCellIdx, stream)`. Called from `SimulatorAgent.cpp` in Phase 2.

Compile target: `sm_86` (RTX 30-series / A-series). Flags: `-O3 --use_fast_math -lineinfo`.

---

## tools/olangc/

### `main.cpp`

The `olangc` compiler driver. Parses flags, reads source, runs the ANTLR4 lexer and parser, checks for syntax errors, constructs the `ASTContext`, and calls each compiler pass in order. Phase 1 passes (semantic analysis, LTL rewriting) are integrated; Phase 2 passes (IRGen, NVPTX lowering) are stubbed with `// TODO Phase 2` at the precise call sites.

Full pipeline when complete:

```
source.olang
  → Lexer           (ANTLR4)
  → Parser          (ANTLR4)
  → ASTBuilder      (Phase 1)
  → SemanticAnalyser (Phase 1)
  → LTLRewriter     (Phase 1)
  → IRGen           (Phase 2, LLVM IRBuilder)
  → NVPTXBackend    (Phase 2, ||| blocks → PTX)
  → x86Backend      (Phase 2, orchestration → ELF)
  → linker
```

---

## tests/unit/

### `middle/test_unit_dimensional_analysis.cpp`

Eight Catch2 tests for `Unit<T>`. Covers:
- Layout guarantee: `sizeof(Seconds) == sizeof(double)`, `alignof` matching.
- User-defined literals: `30.0_s`, `500.0_ms`, `5.0_mM`, `500.0_uM`, `310.15_K`.
- Same-dimension arithmetic: add, subtract, negate, scalar multiply — with `static_assert` on result type.
- Cross-dimension arithmetic: division of `Molarity_d / Seconds` produces `MolarRate` (checked at compile time via `static_assert(std::is_same_v<decltype(r), MolarRate>)`).
- Commented-out negative tests confirm `1.0_s + 1.0_mM` fails to compile.

### `runtime/test_capability_rbac.cpp`

Nine Catch2 tests for the RBAC system. Covers:
- Role mask correctness: Analyst has no physical caps; Executor has no virtual compute caps.
- Cross-role isolation: Simulator cannot `EvaluateLTLProof`; Verifier cannot `SynthesizeCRISPR`.
- `requireCapability` — no-throw when capability is present; `std::runtime_error` when absent.
- Bitwise OR combines capabilities correctly.
- `PhysicalMask` correctly partitions the Executor role into the upper 16 bits.

**17 tests total, 0 failures.**

---

## examples/

### `t1dm/beta7x_proof_of_concept.olang`

The reference OLang program for the #BETA-7-X experiment. Every major language feature appears: `agent` declarations with `stream` and `rule`, the `proof` / `invariant` / `always` / `eventually` / `within` LTL block, the `solver` / `satisfy` / `minimize` SMT block, the `~>` pipeline operator, and the `|||` massive-parallel operator. Heavily annotated. This is the program `olangc` is ultimately built to compile.

---

## scripts/

| File | Purpose |
|---|---|
| `generate_grammar.sh` | Runs the ANTLR4 JAR and applies the compatibility patch. CMake does this automatically at configure time; this script is for manual regeneration after grammar edits. |
| `patch_antlr4_generated.cmake` | Replaces `antlr4::internal::OnceFlag` / `call_once` with `std::once_flag` / `std::call_once` in the two generated `.cpp` files. Idempotent. |

---

## cmake/

### `OLangCompilerFlags.cmake`

Shared compiler flag interface target (`olang_compiler_flags`). Applied with `target_link_libraries(tgt PRIVATE olang_compiler_flags)`.

- **Debug** — `-O0 -g3 -fsanitize=address,undefined` (ASan + UBSan always on in debug builds)
- **Release** — `-O3 -DNDEBUG -march=native`
- **RelWithDebInfo** — `-O2 -g -march=native`
- Warnings: `-Wall -Wextra -Wpedantic -Werror -Wno-unused-parameter -Wno-missing-field-initializers`

---

## CMakeLists.txt

Key design decisions in the root build file:

**CUDA excluded from `project(LANGUAGES ...)`** — listing `CUDA` in `project()` forces an immediate `nvcc` search before any `if()` logic can run. OLang declares only `CXX` and calls `enable_language(CUDA)` later, inside the `if(OLANG_ENABLE_CUDA)` guard. Phase 1 machines never see an nvcc error.

**ANTLR4 auto-generation at configure time** — uses `execute_process` (runs immediately during `cmake`) rather than `add_custom_command` (runs at build time), because `file(GLOB ANTLR_SRCS)` must see the generated `.cpp` files in the same configure pass. A separate `add_custom_command` sentinel reruns generation incrementally when `.g4` files change.

**All three external dependencies optional** — LLVM 18, ANTLR4 runtime, and CUDA each produce a `message(STATUS ...)` and skip the affected targets if absent. The `Unit<T>` and RBAC test suites always build.

**Catch2 via FetchContent** — pinned to v3.7.1, the earliest tag known-good with GCC 13 + CMake 3.22. No system package required.