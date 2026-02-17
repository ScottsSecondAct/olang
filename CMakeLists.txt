cmake_minimum_required(VERSION 3.22)

# CUDA is Phase 2 only. Do NOT list it in LANGUAGES here.
# Enabled later via enable_language(CUDA) only when -DOLANG_ENABLE_CUDA=ON.
project(OLang VERSION 0.1.0 LANGUAGES CXX)

# =============================================================================
# C++ STANDARD
# =============================================================================
set(CMAKE_CXX_STANDARD          23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# =============================================================================
# COMPILER FLAGS  (interface target linked by every sub-target)
# =============================================================================
add_library(olang_flags INTERFACE)
target_compile_options(olang_flags INTERFACE
  -Wall -Wextra -Wpedantic
  -Wno-unused-parameter
  $<$<CONFIG:Debug>:          -O0 -g3>
  $<$<CONFIG:Release>:        -O3 -DNDEBUG -march=native>
  $<$<CONFIG:RelWithDebInfo>: -O2 -g -march=native>
)

# =============================================================================
# ANTLR4 C++ RUNTIME  (optional — needed only for olangc)
# Ubuntu 22.04:  sudo apt install libantlr4-runtime-dev   (installs 4.9.3)
# Ubuntu 24.04:  sudo apt install libantlr4-runtime-dev   (installs 4.13.1)
# From source:   see https://github.com/antlr/antlr4
# =============================================================================
find_library(ANTLR4_LIB NAMES antlr4-runtime
             PATHS /usr/local/lib /usr/lib/x86_64-linux-gnu)

if(ANTLR4_LIB)
  message(STATUS "ANTLR4 runtime: ${ANTLR4_LIB}")

  # Detect the runtime version from the installed headers
  find_path(ANTLR4_INCLUDE_DIR NAMES antlr4-runtime.h
            PATH_SUFFIXES antlr4-runtime
            PATHS /usr/local/include /usr/include)

  if(ANTLR4_INCLUDE_DIR)
    file(READ "${ANTLR4_INCLUDE_DIR}/Version.h" _ver_content)
    string(REGEX MATCH "ANTLRCPP_VERSION_MAJOR ([0-9]+)" _ ${_ver_content})
    set(_maj ${CMAKE_MATCH_1})
    string(REGEX MATCH "ANTLRCPP_VERSION_MINOR ([0-9]+)" _ ${_ver_content})
    set(_min ${CMAKE_MATCH_1})
    string(REGEX MATCH "ANTLRCPP_VERSION_PATCH ([0-9]+)" _ ${_ver_content})
    set(_pat ${CMAKE_MATCH_1})
    set(ANTLR4_RUNTIME_VERSION "${_maj}.${_min}.${_pat}")
    message(STATUS "ANTLR4 runtime version: ${ANTLR4_RUNTIME_VERSION}")
  else()
    set(ANTLR4_RUNTIME_VERSION "unknown")
    message(STATUS "ANTLR4 runtime version: unknown (Version.h not found)")
  endif()

  add_library(antlr4_runtime SHARED IMPORTED)
  set_target_properties(antlr4_runtime PROPERTIES
    IMPORTED_LOCATION             ${ANTLR4_LIB}
    INTERFACE_INCLUDE_DIRECTORIES ${ANTLR4_INCLUDE_DIR})
  set(HAVE_ANTLR4 TRUE)
else()
  message(STATUS "ANTLR4 NOT found -- olangc skipped. "
                 "sudo apt install libantlr4-runtime-dev")
  set(HAVE_ANTLR4 FALSE)
endif()

# =============================================================================
# LLVM 18  (optional — needed for IRGen in Phase 2)
# sudo apt install llvm-18-dev
# =============================================================================
find_package(LLVM 18 QUIET CONFIG PATHS /usr/lib/llvm-18/lib/cmake/llvm)

if(LLVM_FOUND)
  message(STATUS "LLVM ${LLVM_VERSION}: ${LLVM_DIR}")
  add_library(llvm_support INTERFACE)
  target_include_directories(llvm_support INTERFACE ${LLVM_INCLUDE_DIRS})
  target_compile_definitions(llvm_support INTERFACE ${LLVM_DEFINITIONS})
  target_link_libraries(llvm_support INTERFACE LLVM-18)
  target_compile_definitions(llvm_support INTERFACE OLANG_HAVE_LLVM)
  set(HAVE_LLVM TRUE)
else()
  message(STATUS "LLVM 18 NOT found -- stub allocator active. "
                 "sudo apt install llvm-18-dev")
  add_library(llvm_support INTERFACE)   # empty stub keeps targets linkable
  set(HAVE_LLVM FALSE)
endif()

# =============================================================================
# PHASE 1 HEADER-ONLY CORE LIBRARY
# Unit<T>, Capability RBAC, SourceLocation, Diagnostic — zero dependencies
# =============================================================================
add_library(olang_core INTERFACE)
target_include_directories(olang_core INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(olang_core INTERFACE olang_flags llvm_support)

# =============================================================================
# MILESTONE 1.2: TYPE SYSTEM LIBRARY
# AST Type nodes, Type Checker, Symbol Tables, Type Environment
# =============================================================================
add_library(olang_type_system STATIC
  src/frontend/ASTType.cpp              # ← CORRECTED PATH
  src/semantic/TypeChecker.cpp
  src/semantic/SymbolTable.cpp
  src/semantic/TypeEnvironment.cpp
  src/semantic/ErrorReporter.cpp
)

target_include_directories(olang_type_system PUBLIC
  ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(olang_type_system PUBLIC
  olang_core
  olang_flags
)

target_compile_features(olang_type_system PUBLIC cxx_std_23)

message(STATUS "Target: olang_type_system (Milestone 1.2)")

# =============================================================================
# ANTLR4 GRAMMAR CODE GENERATION
#
# We look for the tool JAR in this order:
#   1. ${ANTLR4_JAR}  — user override via cmake -DANTLR4_JAR=...
#   2. tools/antlr4-complete.jar  — checked-in copy (preferred)
#   3. Any antlr-*-complete.jar in PATH
#   4. The system `antlr4` wrapper (/usr/bin/antlr4)
#
# Generated files land in src/frontend/generated/ and are committed to git
# so that a Java runtime is NOT required for a plain build.
# =============================================================================
set(ANTLR_GEN_DIR ${CMAKE_SOURCE_DIR}/src/frontend/generated)

# ── Locate the ANTLR4 tool ──────────────────────────────────────────────────
if(NOT ANTLR4_JAR)
  # Checked-in copy (recommended path for the repo)
  if(EXISTS "${CMAKE_SOURCE_DIR}/tools/antlr4-complete.jar")
    set(ANTLR4_JAR "${CMAKE_SOURCE_DIR}/tools/antlr4-complete.jar")
  endif()
endif()

# Build the command list for running the tool
if(ANTLR4_JAR AND EXISTS "${ANTLR4_JAR}")
  set(ANTLR4_CMD java -jar "${ANTLR4_JAR}")
  message(STATUS "ANTLR4 tool JAR: ${ANTLR4_JAR}")
else()
  find_program(ANTLR4_EXE antlr4)
  if(ANTLR4_EXE)
    set(ANTLR4_CMD ${ANTLR4_EXE})
    message(STATUS "ANTLR4 tool: ${ANTLR4_EXE}")
  else()
    set(ANTLR4_CMD "")
    message(STATUS "ANTLR4 tool NOT found -- grammar will not be regenerated. "
                   "Provide: cmake -DANTLR4_JAR=/path/to/antlr-X.Y.Z-complete.jar")
  endif()
endif()

# ── Auto-generate at CONFIGURE TIME if sources are missing ──────────────────
# We use execute_process (runs immediately during cmake) rather than
# add_custom_command (runs at build time) because file(GLOB ANTLR_SRCS)
# below must see the generated .cpp files during the same configure pass.
set(ANTLR4_PATCH_SCRIPT ${CMAKE_SOURCE_DIR}/scripts/patch_antlr4_generated.cmake)
set(_LEXER_CPP ${ANTLR_GEN_DIR}/OLangLexer.cpp)

if(ANTLR4_CMD AND NOT EXISTS "${_LEXER_CPP}")
  message(STATUS "ANTLR4: generating C++ sources from grammar/ ...")
  file(MAKE_DIRECTORY ${ANTLR_GEN_DIR})

  execute_process(
    COMMAND ${ANTLR4_CMD}
      -Dlanguage=Cpp
      -visitor
      -listener
      -o ${ANTLR_GEN_DIR}
      ${CMAKE_SOURCE_DIR}/grammar/OLangLexer.g4
      ${CMAKE_SOURCE_DIR}/grammar/OLangParser.g4
    RESULT_VARIABLE _antlr_result
    OUTPUT_VARIABLE _antlr_out
    ERROR_VARIABLE  _antlr_err
  )

  if(NOT _antlr_result EQUAL 0)
    message(WARNING "ANTLR4 generation failed (exit ${_antlr_result}):\n${_antlr_err}")
  else()
    message(STATUS "ANTLR4: generation succeeded")
    # Apply runtime compatibility patch
    execute_process(
      COMMAND ${CMAKE_COMMAND} -P ${ANTLR4_PATCH_SCRIPT} ${ANTLR_GEN_DIR}
      RESULT_VARIABLE _patch_result
    )
    if(NOT _patch_result EQUAL 0)
      message(WARNING "ANTLR4 patch script failed (exit ${_patch_result})")
    endif()
  endif()
elseif(EXISTS "${_LEXER_CPP}")
  message(STATUS "ANTLR4: using existing generated sources")
endif()

# Rebuild-on-grammar-change custom target (incremental builds only)
if(ANTLR4_CMD)
  add_custom_command(
    OUTPUT  ${_LEXER_CPP}   # sentinel — if deleted, this reruns
    COMMAND ${ANTLR4_CMD}
              -Dlanguage=Cpp -visitor -listener
              -o ${ANTLR_GEN_DIR}
              ${CMAKE_SOURCE_DIR}/grammar/OLangLexer.g4
              ${CMAKE_SOURCE_DIR}/grammar/OLangParser.g4
    COMMAND ${CMAKE_COMMAND} -P ${ANTLR4_PATCH_SCRIPT} ${ANTLR_GEN_DIR}
    DEPENDS
      ${CMAKE_SOURCE_DIR}/grammar/OLangLexer.g4
      ${CMAKE_SOURCE_DIR}/grammar/OLangParser.g4
    COMMENT "Regenerating ANTLR4 C++ sources (grammar changed)"
    VERBATIM
  )
  add_custom_target(olang_generate_grammar DEPENDS ${_LEXER_CPP})
endif()

# ── Build the grammar library from generated sources ────────────────────────
file(GLOB ANTLR_SRCS ${ANTLR_GEN_DIR}/*.cpp)

if(ANTLR_SRCS AND HAVE_ANTLR4)
  add_library(olang_grammar STATIC ${ANTLR_SRCS})
  target_include_directories(olang_grammar PUBLIC
    ${ANTLR_GEN_DIR}
    ${ANTLR4_INCLUDE_DIR})
  target_link_libraries(olang_grammar PUBLIC antlr4_runtime olang_flags)
  # Generated code produces warnings we cannot fix upstream
  target_compile_options(olang_grammar PRIVATE
    -Wno-attributes -Wno-unused-parameter -Wno-extra
    -Wno-unused-function -Wno-parentheses)
  if(TARGET olang_generate_grammar)
    add_dependencies(olang_grammar olang_generate_grammar)
  endif()
  set(HAVE_GRAMMAR TRUE)
  message(STATUS "ANTLR4 grammar library: ${ANTLR_SRCS}")
else()
  set(HAVE_GRAMMAR FALSE)
  if(NOT ANTLR_SRCS)
    message(STATUS "Grammar sources not found in ${ANTLR_GEN_DIR}")
    message(STATUS "  -> Provide a JAR: cmake -DANTLR4_JAR=/path/to/antlr-complete.jar")
    message(STATUS "  -> Or copy tools/antlr4-complete.jar from Scott's setup notes")
  endif()
endif()

# =============================================================================
# CUDA / NVPTX BACKEND  (Phase 2 — OFF by default, no nvcc search unless ON)
# Enable: cmake -DOLANG_ENABLE_CUDA=ON ...
# =============================================================================
option(OLANG_ENABLE_CUDA "Enable CUDA backend (Phase 2)" OFF)
if(OLANG_ENABLE_CUDA)
  find_package(CUDAToolkit 12 REQUIRED)
  enable_language(CUDA)
  set(CMAKE_CUDA_STANDARD      20)
  set(CMAKE_CUDA_ARCHITECTURES "80;86;89;90")
  add_library(olang_cuda STATIC src/backend/cuda/kmc_kernel.cu)
  target_link_libraries(olang_cuda PRIVATE CUDA::cudart olang_flags)
endif()

# =============================================================================
# TESTS  (Catch2 v3.7.1 fetched automatically — no system package needed)
# =============================================================================
enable_testing()

include(FetchContent)
FetchContent_Declare(Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1
  GIT_SHALLOW    TRUE)
FetchContent_MakeAvailable(Catch2)
list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)

# ── Phase 1 Tests (existing) ─────────────────────────────────────────────────
add_executable(test_units
  tests/unit/middle/test_unit_dimensional_analysis.cpp)
target_link_libraries(test_units PRIVATE olang_core Catch2::Catch2WithMain)
catch_discover_tests(test_units)

add_executable(test_rbac
  tests/unit/runtime/test_capability_rbac.cpp)
target_link_libraries(test_rbac PRIVATE olang_core Catch2::Catch2WithMain)
catch_discover_tests(test_rbac)

# ── Milestone 1.2 Tests (Type System) ────────────────────────────────────────
# NOTE: test_type_system.cpp needs to be converted to Catch2 format
# Uncomment when ready:
# add_executable(test_type_system
#   tests/unit/test_type_system.cpp)
# target_link_libraries(test_type_system PRIVATE
#   olang_type_system
#   olang_core
#   Catch2::Catch2WithMain)
# catch_discover_tests(test_type_system)
# message(STATUS "Test: test_type_system (Milestone 1.2 - 24 tests)")

# =============================================================================
# olangc COMPILER DRIVER
# =============================================================================
if(HAVE_GRAMMAR)
  add_executable(olangc
    tools/olangc/main.cpp
    src/frontend/Diagnostic.cpp
    src/frontend/ASTBuilder.cpp)
  
  target_link_libraries(olangc PRIVATE 
    olang_grammar 
    olang_type_system  # Link the type system
    olang_core)
  
  target_compile_options(olangc PRIVATE 
    -Wall -Wextra -Wpedantic -Wno-unused-parameter -O0 -g3)
  
  message(STATUS "Target: olangc")
endif()

# =============================================================================
# CONFIGURATION SUMMARY
# =============================================================================
message(STATUS "")
message(STATUS "=== OLang Phase 1 Configuration ===")
message(STATUS "  C++ standard  : ${CMAKE_CXX_STANDARD}")
message(STATUS "  Compiler      : ${CMAKE_CXX_COMPILER_ID} ${CMAKE_CXX_COMPILER_VERSION}")
message(STATUS "  ANTLR4 found  : ${HAVE_ANTLR4}")
if(HAVE_ANTLR4)
message(STATUS "  ANTLR4 ver    : ${ANTLR4_RUNTIME_VERSION}")
endif()
message(STATUS "  LLVM 18 found : ${HAVE_LLVM}")
message(STATUS "  Grammar srcs  : ${HAVE_GRAMMAR}")
message(STATUS "  Type system   : olang_type_system (M1.2)")
message(STATUS "  CUDA backend  : ${OLANG_ENABLE_CUDA}")
message(STATUS "  Build type    : ${CMAKE_BUILD_TYPE}")
message(STATUS "====================================")
message(STATUS "")