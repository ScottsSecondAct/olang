# OLang Project Structure

**Last Updated:** February 17, 2026  
**Current Milestone:** 1.2 (Type System) — COMPLETE ✅

---

## Directory Layout

```
olang/
├── cmake/                      # CMake utility modules
├── examples/t1dm/              # Example OLang programs for T1DM
├── grammar/                    # ANTLR4 grammar definitions
│   ├── OLangLexer.g4          # Lexical grammar
│   └── OLangParser.g4         # Syntactic grammar
├── include/olang/              # Public headers
│   ├── ast/                   # Abstract Syntax Tree
│   ├── backend/               # Code generation backends
│   ├── frontend/              # Lexer, Parser, AST (Milestone 1.2)
│   ├── middle/                # Optimization passes
│   ├── runtime/               # Runtime system
│   ├── semantic/              # Type checker, Symbol tables (Milestone 1.2)
│   ├── stdlib/                # Standard library
│   ├── support/               # Utility headers
│   └── type/                  # Dimensional analysis (Milestone 1.2)
├── scripts/                   # Build and utility scripts
├── src/                       # Implementation files
│   ├── ast/                   # AST implementation
│   ├── backend/               # LLVM IR, NVPTX, CUDA
│   ├── frontend/              # Parser, AST builder (Milestone 1.2)
│   ├── middle/                # Optimization passes
│   ├── runtime/               # Agent runtime, concurrency
│   ├── semantic/              # Type checking (Milestone 1.2)
│   └── stdlib/                # Standard library implementation
├── tests/unit/                # Unit tests (Catch2)
├── tools/                     # Compiler driver and utilities
│   ├── olangc/                # Main compiler executable
│   └── antlr4-complete.jar    # ANTLR4 tool JAR
├── CMakeLists.txt             # Root build configuration
├── PROJECT_STRUCTURE.md       # This file
├── README.md                  # Project overview
└── ROADMAP.md                 # Development timeline
```

---

## Core Components

### Frontend (`include/olang/frontend/` & `src/frontend/`)

**Purpose:** Lexical analysis, parsing, and AST construction

#### Headers:
- **`AST.h`** - Base AST node infrastructure
- **`ASTBuilder.h`** - ANTLR4 parse tree → AST converter
- **`ASTContext.h`** - AST memory management and allocation
- **`ASTType.hpp`** ✅ **[M1.2]** - Type AST nodes (14 type classes, 373 lines)
- **`Diagnostic.h`** - Error and warning messages
- **`SourceLocation.h`** - Line/column position tracking

#### Implementation:
- **`src/frontend/ASTType.cpp`** ✅ **[M1.2]** - Type implementations (402 lines)
- **`src/frontend/ASTBuilder.cpp`** - Parse tree visitor
- **`src/frontend/Diagnostic.cpp`** - Error formatting
- **`src/frontend/generated/`** - ANTLR4-generated C++ sources
  - `OLangLexer.cpp/h`
  - `OLangParser.cpp/h`
  - Visitor and Listener base classes

**Status:** Parser operational, AST type nodes complete (M1.2)

---

### Semantic Analysis (`include/olang/semantic/` & `src/semantic/`)

**Purpose:** Type checking, symbol resolution, semantic validation

#### Headers:
- **`TypeChecker.hpp`** ✅ **[M1.2]** - Type checker infrastructure (122 lines)
- **`SymbolTable.hpp`** ✅ **[M1.2]** - Scoped symbol management (45 lines)
- **`TypeEnvironment.hpp`** ✅ **[M1.2]** - Global type registry (43 lines)
- **`ErrorReporter.hpp`** ✅ **[M1.2]** - Structured error reporting (44 lines)

#### Implementation:
- **`src/semantic/TypeChecker.cpp`** ✅ **[M1.2]** - Type checking algorithms (454 lines)
  - Assignability checking
  - Type unification (Hindley-Milner)
  - Subtyping rules
  - Dimensional consistency validation
- **`src/semantic/SymbolTable.cpp`** ✅ **[M1.2]** - Symbol table operations (60 lines)
- **`src/semantic/TypeEnvironment.cpp`** ✅ **[M1.2]** - Built-in type registration (82 lines)
- **`src/semantic/ErrorReporter.cpp`** ✅ **[M1.2]** - Error formatting and output (45 lines)

**Status:** Complete type system infrastructure (M1.2)

**Milestone 1.2 Metrics:**
- Total type system code: **2,011 lines**
- Headers: **968 lines** (6 files)
- Implementation: **1,043 lines** (5 files)
- 100% namespace consistency (`olang::frontend`, `olang::semantic`)

---

### Type System (`include/olang/type/`)

**Purpose:** Zero-cost dimensional analysis for biological safety

#### Headers:
- **`Unit.hpp`** ✅ **[M1.2]** - Compile-time dimensional analysis (341 lines)
  - Template metaprogramming for dimension checking
  - SI base units (Meter, Kilogram, Second, Kelvin, etc.)
  - Biological units (Cell, Molecule, Gene)
  - User-defined literals (`5.0_m`, `2.0_kg`, `100_cells`)
  - Zero runtime overhead in release builds

**Key Features:**
```cpp
// Compile-time dimension checking
Length distance = 5.0_m;
Time duration = 2.0_s;
Velocity speed = distance / duration;  // ✅ Valid

// auto invalid = distance + duration;  // ❌ COMPILE ERROR
```

**Status:** Production-ready, zero-cost abstraction (M1.2)

---

### Middle-End (`include/olang/middle/` & `src/middle/`)

**Purpose:** Optimization passes, type transformations

#### Headers:
- **`middle/units/Unit.h`** - Middle-end unit representation
- **`middle/types/`** - Type system transformations

#### Implementation:
- **`src/middle/passes/`** - Optimization passes
- **`src/middle/types/`** - Type lowering
- **`src/middle/units/`** - Unit normalization

**Status:** Stub infrastructure, awaiting Phase 2

---

### Runtime (`include/olang/runtime/` & `src/runtime/`)

**Purpose:** Agent orchestration, concurrency, RBAC

#### Agent System:
- **`runtime/agents/Agent.h`** - Base agent interface
- **`runtime/agents/Capability.h`** ✅ - RBAC capability system (9 tests passing)
- **`src/runtime/agents/`** - Agent implementations

#### Biological Models:
- **`runtime/bio/IsletState.h`** ✅ - Pancreatic islet digital twin
- **`src/runtime/bio/`** - Biological state representations

#### Concurrency:
- **`src/runtime/concurrency/`** - Thread pool, task scheduling
- **`src/runtime/frp/`** - Functional Reactive Programming primitives
- **`src/runtime/memory/`** - Memory management

**Status:** Core RBAC complete, runtime TBD (Phase 2)

---

### Backend (`include/olang/backend/` & `src/backend/`)

**Purpose:** LLVM IR generation, CUDA kernel compilation

#### LLVM Backend:
- **`src/backend/llvm/`** - LLVM IR generation (Phase 2)

#### NVPTX Backend (`|||` operator):
- **`src/backend/nvptx/`** - PTX kernel generation (Phase 2)
- **`src/backend/cuda/kmc_kernel.cu`** ✅ - Gillespie KMC kernel (written, awaiting link)

**Status:** Kernels written, backend integration Phase 2

---

### Standard Library (`include/olang/stdlib/` & `src/stdlib/`)

**Purpose:** Built-in functions and biological primitives

#### Modules:
- **`stdlib/bio/`** - Biological utility functions
- **`stdlib/collections/`** - Container operations
- **`stdlib/math/`** - Mathematical functions

**Status:** Stub, awaits type system integration

---

### Testing (`tests/unit/`)

**Framework:** Catch2 v3.7.1 (auto-fetched)

#### Current Tests:
- **`middle/test_unit_dimensional_analysis.cpp`** ✅ - Unit<T> tests (8 passing)
- **`runtime/test_capability_rbac.cpp`** ✅ - RBAC tests (9 passing)
- **`test_type_system.cpp`** 🔧 **[M1.2 TODO]** - Type system tests (needs Catch2 conversion)

**Test Command:**
```bash
ctest --test-dir build --output-on-failure
```

**Expected Output:**
```
100% tests passed, 0 tests failed out of 2
```

**Pending:** Convert M1.2's 24 type system tests to Catch2 format

---

### Build System

#### Root Configuration:
- **`CMakeLists.txt`** ✅ **[M1.2 Updated]** - Main build configuration
  - Adds `olang_type_system` static library
  - Links type system to `olangc` compiler
  - Configured for C++23, Catch2 testing
  - ANTLR4 auto-generation at configure time
  - Optional LLVM 18 and CUDA support

#### Libraries Built:
1. **`olang_core`** (INTERFACE) - Header-only core (Unit<T>, Capability, etc.)
2. **`olang_type_system`** (STATIC) ✅ **[M1.2]** - Type checking infrastructure
3. **`olang_grammar`** (STATIC) - ANTLR4-generated parser
4. **`olangc`** (EXECUTABLE) - Compiler driver

---

## File Count Summary

| Category | Files | Lines of Code |
|----------|-------|---------------|
| Grammar | 2 | ~450 |
| Frontend Headers (M1.2) | 6 | ~968 |
| Frontend Implementation (M1.2) | 1 | ~402 |
| Semantic Headers (M1.2) | 4 | ~254 |
| Semantic Implementation (M1.2) | 4 | ~641 |
| Type System (M1.2) | 1 | ~341 |
| Runtime Headers | 3 | ~200 |
| Tests | 2 | ~300 |
| **Milestone 1.2 Total** | **16** | **~2,606** |
| **Project Total (Phase 1)** | **~40** | **~5,000+** |

---

## Namespace Organization

```cpp
namespace olang {
  namespace frontend {     // AST, Parser, Type nodes
    class Type;
    class PrimitiveType;
    class UserDefinedType;
    // ... 14 type classes
  }
  
  namespace semantic {     // Type checking, symbols
    class TypeChecker;
    class SymbolTable;
    class TypeEnvironment;
    class ErrorReporter;
  }
  
  namespace type {         // Dimensional analysis
    template<typename T, typename... Dims>
    class Unit;
    // SI units + biological extensions
  }
  
  namespace runtime {      // Agents, concurrency
    namespace agents {
      class Agent;
      class Capability;
    }
    namespace bio {
      class IsletState;
    }
  }
  
  namespace backend {      // Code generation
    namespace llvm { }
    namespace nvptx { }
  }
}
```

---

## Key Design Patterns

### Visitor Pattern (AST Traversal)
```cpp
class TypeVisitor {
  virtual void visit(const PrimitiveType& type) = 0;
  virtual void visit(const UserDefinedType& type) = 0;
  // ... all type classes
};
```

### RAII (Memory Management)
- All AST nodes use `std::unique_ptr`
- No raw pointers, no manual `delete`
- Exception-safe resource management

### Template Metaprogramming (Zero-Cost Abstraction)
```cpp
template <typename T, typename... Dims>
class Unit {
  // Compile-time dimension checking
  // Erases to raw T in release builds
};
```

### Double Dispatch (Type-Specific Operations)
```cpp
void Type::accept(TypeVisitor& visitor) const {
  visitor.visit(*this);  // Polymorphic dispatch
}
```

---

## Build Targets

```bash
# Core libraries
make olang_core          # Header-only utilities
make olang_type_system   # Type checker (M1.2)
make olang_grammar       # ANTLR4 parser

# Executables
make olangc              # Compiler driver

# Tests
make test_units          # Dimensional analysis tests
make test_rbac           # RBAC capability tests
make test_type_system    # Type system tests (when converted)

# All
make -j$(nproc)          # Build everything in parallel
```

---

## Development Workflow

### 1. Grammar Changes
```bash
# Edit grammar files
vim grammar/OLangLexer.g4
vim grammar/OLangParser.g4

# Regenerate (automatic on next build)
cmake --build build
```

### 2. Type System Changes
```bash
# Edit headers
vim include/olang/frontend/ASTType.hpp
vim include/olang/semantic/TypeChecker.hpp

# Edit implementation
vim src/frontend/ASTType.cpp
vim src/semantic/TypeChecker.cpp

# Rebuild type system library
cmake --build build --target olang_type_system
```

### 3. Running Tests
```bash
# Run all tests
ctest --test-dir build --output-on-failure

# Run specific test
./build/test_units
./build/test_rbac
```

---

## Milestone Progress

### ✅ Milestone 1.1: Grammar Definition (January 2026)
- ANTLR4 lexer and parser grammars
- Agent orchestration keywords
- LTL verification syntax
- SMT solver syntax

### ✅ Milestone 1.2: Type System Foundation (February 2026)
- Complete AST type hierarchy (14 classes)
- Type checker with symbol tables
- Zero-cost dimensional analysis
- 2,011 lines of production code
- 100% namespace consistency

### 🔄 Milestone 1.3: Expression Type Checking (March 2026)
- AST-to-Type mapping
- Expression type inference
- Constraint solving
- Integration tests with .olang files

### 📋 Milestone 1.4: RBAC Capability System (April 2026)
- Agent capability enforcement
- Runtime capability checks
- Integration with type checker

### 📋 Milestone 1.5: LTL Verification Framework (May 2026)
- LTL formula parser
- Temporal logic evaluator
- Proof obligation generator

### 📋 Milestone 1.6: Basic LLVM Integration (June 2026)
- LLVM IR generation
- Type lowering
- Simple expression compilation

---

## Next Steps

1. **Convert type system tests to Catch2** - Milestone 1.2 completion
2. **Begin Milestone 1.3** - Expression type checking
3. **ANTLR4 integration** - Wire parser to type system
4. **Update documentation** - API docs with Doxygen

---

**Last Updated:** February 17, 2026  
**Maintainer:** Scott Eugene Davis  
**Status:** Phase 1 in progress, on track for Sierra College → UC Davis transition (2027)