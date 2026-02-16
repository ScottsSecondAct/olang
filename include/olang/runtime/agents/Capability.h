#pragma once
#include <cstdint>
#include <stdexcept>
#include <string_view>

namespace olang::runtime {

enum class Capability : uint32_t {
  ReadScrnaSeq          = 1u <<  0,
  WriteSimulationResult = 1u <<  1,
  ReadGenomicIndex      = 1u <<  2,
  RunKMCSimulation      = 1u <<  3,
  RunFBASimulation      = 1u <<  4,
  RunParallelKernel     = 1u <<  5,
  EvaluateLTLProof      = 1u <<  6,
  EmitGovernanceSignal  = 1u <<  7,
  InvokeSMTSolver       = 1u <<  8,
  SynthesizeCRISPR      = 1u << 16,
  ControlLabRobotics    = 1u << 17,
  ReadLabSensor         = 1u << 18,
  VirtualMask           = 0x0000FFFFu,
  PhysicalMask          = 0xFFFF0000u,
};

inline constexpr Capability operator|(Capability a, Capability b) noexcept {
  return static_cast<Capability>(uint32_t(a)|uint32_t(b));
}
inline constexpr Capability operator&(Capability a, Capability b) noexcept {
  return static_cast<Capability>(uint32_t(a)&uint32_t(b));
}
inline constexpr bool has(Capability mask, Capability cap) noexcept {
  return (uint32_t(mask) & uint32_t(cap)) != 0;
}

namespace roles {
  inline constexpr Capability Analyst    = Capability::ReadScrnaSeq | Capability::ReadGenomicIndex;
  inline constexpr Capability Strategist = Capability::InvokeSMTSolver | Capability::ReadGenomicIndex;
  inline constexpr Capability Simulator  = Capability::RunKMCSimulation | Capability::RunFBASimulation
                                         | Capability::RunParallelKernel | Capability::WriteSimulationResult;
  inline constexpr Capability Verifier   = Capability::EvaluateLTLProof | Capability::EmitGovernanceSignal;
  inline constexpr Capability Executor   = Capability::SynthesizeCRISPR | Capability::ControlLabRobotics
                                         | Capability::ReadLabSensor;
}

inline void requireCapability(Capability granted, Capability required, std::string_view op) {
  if (!has(granted, required))
    throw std::runtime_error("RBAC violation: agent lacks capability for '" + std::string(op) + "'");
}

} // namespace olang::runtime
