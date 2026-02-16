add_library(olang_compiler_flags INTERFACE)
target_compile_options(olang_compiler_flags INTERFACE
  $<$<CXX_COMPILER_ID:Clang,GNU>:
    -Wall -Wextra -Wpedantic -Werror
    -Wno-unused-parameter
    -Wno-missing-field-initializers
  >
  $<$<CONFIG:Release>:        -O3 -DNDEBUG -march=native>
  $<$<CONFIG:RelWithDebInfo>: -O2 -g       -march=native>
  $<$<CONFIG:Debug>:          -O0 -g3 -fsanitize=address,undefined>
)
target_link_options(olang_compiler_flags INTERFACE
  $<$<AND:$<CONFIG:Debug>,$<CXX_COMPILER_ID:Clang,GNU>>:
    -fsanitize=address,undefined>
)
