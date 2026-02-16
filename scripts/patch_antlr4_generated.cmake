# scripts/patch_antlr4_generated.cmake
#
# Fixes ANTLR4 tool version > runtime version mismatches.
# Specifically: ANTLR4 >= 4.11 generates antlr4::internal::OnceFlag /
# antlr4::internal::call_once, but the 4.10 runtime does not have the
# antlr4::internal namespace.  We replace these with std::once_flag /
# std::call_once, which is semantically identical.
#
# Called by CMake add_custom_command after code generation:
#   cmake -P scripts/patch_antlr4_generated.cmake <generated_dir>
#
# Safe to run multiple times (idempotent — skips files that don't need it).

# CMake passes the directory as CMAKE_ARGV3
set(GEN_DIR "${CMAKE_ARGV3}")

if(NOT GEN_DIR OR NOT EXISTS "${GEN_DIR}")
  message(FATAL_ERROR "patch_antlr4_generated.cmake: directory not provided or missing: '${GEN_DIR}'")
endif()

set(FILES_TO_PATCH
  "${GEN_DIR}/OLangLexer.cpp"
  "${GEN_DIR}/OLangParser.cpp"
)

foreach(F ${FILES_TO_PATCH})
  if(NOT EXISTS "${F}")
    continue()
  endif()

  file(READ "${F}" CONTENT)

  # Check if patch is needed
  if(NOT CONTENT MATCHES "antlr4::internal")
    message(STATUS "patch_antlr4: no patch needed: ${F}")
    continue()
  endif()

  # Add #include <mutex> after the first existing #include if not already present
  if(NOT CONTENT MATCHES "#include <mutex>")
    string(REPLACE "#include " "#include <mutex>\n#include " CONTENT "${CONTENT}")
    # Only replace the FIRST occurrence
    string(FIND "${CONTENT}" "#include <mutex>\n#include <mutex>" DOUBLE_POS)
    if(NOT DOUBLE_POS EQUAL -1)
      # We doubled up — remove the extra one we just added
      string(REPLACE "#include <mutex>\n#include <mutex>" "#include <mutex>" CONTENT "${CONTENT}")
    endif()
  endif()

  # Replace antlr4::internal symbols with std equivalents
  string(REPLACE "::antlr4::internal::OnceFlag" "std::once_flag"  CONTENT "${CONTENT}")
  string(REPLACE "::antlr4::internal::call_once" "std::call_once" CONTENT "${CONTENT}")

  file(WRITE "${F}" "${CONTENT}")
  message(STATUS "patch_antlr4: patched ${F}")
endforeach()