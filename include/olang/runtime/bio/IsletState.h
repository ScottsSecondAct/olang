#pragma once
#include <array>
#include <cstdint>
#include "olang/middle/units/Unit.h"

namespace olang::runtime::bio {

using namespace olang::units;
using namespace olang::units::literals;

struct ProteinPanel {
  Molarity_d pdl1, mhc1, ins, glut2, atp, adp;
};

enum class TCellState : uint8_t { Naive, Primed, Engaged, Anergic, Exhausted };

struct TCell {
  TCellState state{TCellState::Naive};
  Molarity_d tcr_affinity;
  Seconds    engagementTime;
};

struct BetaCell {
  ProteinPanel surface;
  Molarity_d   glucoseIntracellular;
  bool         isSecreting{false};
  bool         isEdited{false};
  uint32_t     editSitePosition{0};
  uint32_t     editAlleleHash{0};
};

struct IsletState {
  static constexpr uint32_t kMaxBetaCells = 1'000;
  static constexpr uint32_t kMaxTCells    = 10'000;

  std::array<BetaCell, kMaxBetaCells> betaCells;
  std::array<TCell,    kMaxTCells>    tCells;

  Kelvin   temperature{310.15_K};
  Seconds  simTime{0.0_s};
  uint32_t activeBetaCells{0};
  uint32_t activeTCells{0};
  uint64_t provenanceHash{0};
  uint32_t generationId{0};
};

static_assert(std::is_trivially_copyable_v<IsletState>);

} // namespace olang::runtime::bio
