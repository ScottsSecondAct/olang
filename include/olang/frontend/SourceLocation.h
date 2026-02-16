#pragma once
#include <cstdint>

namespace olang {

class SourceLocation {
public:
  constexpr SourceLocation() noexcept = default;

  [[nodiscard]] static constexpr SourceLocation
  from(uint32_t line, uint32_t col, uint16_t fileId = 0) noexcept {
    SourceLocation sl; sl.line_ = line; sl.col_ = col; sl.fileId_ = fileId;
    return sl;
  }

  [[nodiscard]] constexpr uint32_t line()    const noexcept { return line_;   }
  [[nodiscard]] constexpr uint32_t col()     const noexcept { return col_;    }
  [[nodiscard]] constexpr uint16_t fileId()  const noexcept { return fileId_; }
  [[nodiscard]] constexpr bool     isValid() const noexcept { return line_ != 0; }

private:
  uint32_t line_=0, col_=0;
  uint16_t fileId_=0, pad_=0;
};

static_assert(sizeof(SourceLocation) <= 12);
} // namespace olang
