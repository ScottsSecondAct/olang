#include "olang/frontend/Diagnostic.h"
#include <iostream>

namespace olang {

void DiagnosticEngine::printAll(std::string_view sourceFile) const {
  for (const auto& d : diags_) {
    const char* label = "";
    switch (d.severity) {
      case DiagSeverity::Note:    label = "note";    break;
      case DiagSeverity::Warning: label = "warning"; break;
      case DiagSeverity::Error:   label = "error";   break;
      case DiagSeverity::Fatal:   label = "fatal";   break;
    }
    if (d.loc.isValid())
      std::cerr << sourceFile << ':' << d.loc.line() << ':' << d.loc.col() << ": ";
    else
      std::cerr << sourceFile << ": ";
    std::cerr << label << ": " << d.message << '\n';
    if (!d.hint.empty())
      std::cerr << "  hint: " << d.hint << '\n';
  }
}

} // namespace olang
