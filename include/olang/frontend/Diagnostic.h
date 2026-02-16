#pragma once
#include <string>
#include <vector>
#include "olang/frontend/SourceLocation.h"

namespace olang {

enum class DiagSeverity : uint8_t { Note, Warning, Error, Fatal };

struct Diagnostic {
  DiagSeverity severity;
  SourceLocation loc;
  std::string message;
  std::string hint;
};

class DiagnosticEngine {
public:
  void emit(DiagSeverity sev, SourceLocation loc, std::string msg, std::string hint = {}) {
    if (sev >= DiagSeverity::Error) hasErrors_ = true;
    diags_.push_back({sev, loc, std::move(msg), std::move(hint)});
  }
  void error  (SourceLocation loc, std::string msg) { emit(DiagSeverity::Error,   loc, std::move(msg)); }
  void warning(SourceLocation loc, std::string msg) { emit(DiagSeverity::Warning, loc, std::move(msg)); }
  void note   (SourceLocation loc, std::string msg) { emit(DiagSeverity::Note,    loc, std::move(msg)); }
  void fatal  (SourceLocation loc, std::string msg) { emit(DiagSeverity::Fatal,   loc, std::move(msg)); }

  [[nodiscard]] bool hasErrors() const noexcept { return hasErrors_; }
  [[nodiscard]] const std::vector<Diagnostic>& all() const noexcept { return diags_; }
  void printAll(std::string_view sourceFile) const;

private:
  std::vector<Diagnostic> diags_;
  bool hasErrors_ = false;
};

} // namespace olang
