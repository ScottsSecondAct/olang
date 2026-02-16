#include <catch2/catch_test_macros.hpp>
#include <catch2/catch_approx.hpp>
#include "olang/middle/units/Unit.h"

using namespace olang::units;
using namespace olang::units::literals;

static_assert(sizeof(Seconds)    == sizeof(double));
static_assert(sizeof(Molarity_d) == sizeof(double));

TEST_CASE("UDL literals produce correct raw values", "[unit]") {
  REQUIRE((30.0_s).raw()   == Catch::Approx(30.0));
  REQUIRE((500.0_ms).raw() == Catch::Approx(0.5));
  REQUIRE((5.0_mM).raw()   == Catch::Approx(5.0));
  REQUIRE((500.0_uM).raw() == Catch::Approx(0.5));
  REQUIRE((310.15_K).raw() == Catch::Approx(310.15));
}

TEST_CASE("Same-dimension addition", "[unit]") {
  auto t = 10.0_s + 20.0_s;
  static_assert(std::is_same_v<decltype(t), Seconds>);
  REQUIRE(t.raw() == Catch::Approx(30.0));
}

TEST_CASE("Cross-dimension multiply yields new type", "[unit]") {
  auto p = Molarity_d{2.0} * Seconds{10.0};
  using E = Unit<double, DimMul<DimMolarity, DimTime>>;
  static_assert(std::is_same_v<decltype(p), E>);
  REQUIRE(p.raw() == Catch::Approx(20.0));
}

TEST_CASE("Molarity / time = MolarRate", "[unit]") {
  auto r = Molarity_d{0.5} / Seconds{2.0};
  static_assert(std::is_same_v<decltype(r), MolarRate>);
  REQUIRE(r.raw() == Catch::Approx(0.25));
}

TEST_CASE("Comparison operators", "[unit]") {
  REQUIRE(10.0_s <  20.0_s);
  REQUIRE(20.0_s >  10.0_s);
  REQUIRE(10.0_s == 10.0_s);
}
