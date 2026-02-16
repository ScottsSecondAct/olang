#include <catch2/catch_test_macros.hpp>
#include <stdexcept>
#include "olang/runtime/agents/Capability.h"

using namespace olang::runtime;
using namespace olang::runtime::roles;

TEST_CASE("Analyst: correct virtual caps", "[rbac]") {
  REQUIRE( has(Analyst, Capability::ReadScrnaSeq));
  REQUIRE( has(Analyst, Capability::ReadGenomicIndex));
  REQUIRE(!has(Analyst, Capability::SynthesizeCRISPR));
  REQUIRE(!has(Analyst, Capability::RunKMCSimulation));
}

TEST_CASE("Simulator: compute but not hardware", "[rbac]") {
  REQUIRE( has(Simulator, Capability::RunParallelKernel));
  REQUIRE(!has(Simulator, Capability::SynthesizeCRISPR));
}

TEST_CASE("Executor: physical only", "[rbac]") {
  REQUIRE( has(Executor, Capability::SynthesizeCRISPR));
  REQUIRE(!has(Executor, Capability::RunKMCSimulation));
}

TEST_CASE("requireCapability: no throw when granted", "[rbac]") {
  REQUIRE_NOTHROW(requireCapability(Simulator, Capability::RunKMCSimulation, "runKMC"));
}

TEST_CASE("requireCapability: throws when absent", "[rbac]") {
  REQUIRE_THROWS_AS(
    requireCapability(Analyst, Capability::SynthesizeCRISPR, "synth"),
    std::runtime_error);
}
