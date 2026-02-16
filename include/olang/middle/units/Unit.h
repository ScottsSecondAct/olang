#pragma once
#include <concepts>
#include <type_traits>

namespace olang::units {

template <int Mass, int Time, int Length, int Amount,
          int Temperature, int Current, int Intensity>
struct Dim {
  static constexpr int mass=Mass, time=Time, length=Length, amount=Amount;
  static constexpr int temperature=Temperature, current=Current, intensity=Intensity;
};

template <typename D1, typename D2>
using DimMul = Dim<D1::mass+D2::mass, D1::time+D2::time, D1::length+D2::length,
                   D1::amount+D2::amount, D1::temperature+D2::temperature,
                   D1::current+D2::current, D1::intensity+D2::intensity>;

template <typename D1, typename D2>
using DimDiv = Dim<D1::mass-D2::mass, D1::time-D2::time, D1::length-D2::length,
                   D1::amount-D2::amount, D1::temperature-D2::temperature,
                   D1::current-D2::current, D1::intensity-D2::intensity>;

template <typename T, typename D>
  requires std::floating_point<T>
class Unit {
public:
  using value_type = T; using dimension_type = D;
  constexpr explicit Unit(T v = T{}) noexcept : val_(v) {}
  [[nodiscard]] constexpr T raw() const noexcept { return val_; }

  [[nodiscard]] constexpr Unit operator+(Unit r) const noexcept { return Unit{val_+r.val_}; }
  [[nodiscard]] constexpr Unit operator-(Unit r) const noexcept { return Unit{val_-r.val_}; }
  [[nodiscard]] constexpr Unit operator-()       const noexcept { return Unit{-val_}; }

  template<typename D2>
  [[nodiscard]] constexpr Unit<T,DimMul<D,D2>> operator*(Unit<T,D2> r) const noexcept {
    return Unit<T,DimMul<D,D2>>{val_*r.raw()};
  }
  template<typename D2>
  [[nodiscard]] constexpr Unit<T,DimDiv<D,D2>> operator/(Unit<T,D2> r) const noexcept {
    return Unit<T,DimDiv<D,D2>>{val_/r.raw()};
  }
  [[nodiscard]] constexpr Unit operator*(T s) const noexcept { return Unit{val_*s}; }
  [[nodiscard]] constexpr Unit operator/(T s) const noexcept { return Unit{val_/s}; }

  [[nodiscard]] constexpr bool operator< (Unit r) const noexcept { return val_< r.val_; }
  [[nodiscard]] constexpr bool operator<=(Unit r) const noexcept { return val_<=r.val_; }
  [[nodiscard]] constexpr bool operator> (Unit r) const noexcept { return val_> r.val_; }
  [[nodiscard]] constexpr bool operator>=(Unit r) const noexcept { return val_>=r.val_; }
  [[nodiscard]] constexpr bool operator==(Unit r) const noexcept { return val_==r.val_; }

private:
  T val_;
};

using DimScalar      = Dim<0,0,0,0,0,0,0>;
using DimTime        = Dim<0,1,0,0,0,0,0>;
using DimMolarity    = Dim<0,0,-3,1,0,0,0>;
using DimMass        = Dim<1,0,0,0,0,0,0>;
using DimTemperature = Dim<0,0,0,0,1,0,0>;
using DimLength      = Dim<0,0,1,0,0,0,0>;

using Scalar_d   = Unit<double, DimScalar>;
using Seconds    = Unit<double, DimTime>;
using Molarity_d = Unit<double, DimMolarity>;
using Kelvin     = Unit<double, DimTemperature>;
using Meters     = Unit<double, DimLength>;
using MolarRate  = Unit<double, DimDiv<DimMolarity,DimTime>>;

namespace literals {
  [[nodiscard]] constexpr Seconds    operator""_s  (long double v) { return Seconds   {static_cast<double>(v)};       }
  [[nodiscard]] constexpr Seconds    operator""_ms (long double v) { return Seconds   {static_cast<double>(v)*1e-3};  }
  [[nodiscard]] constexpr Molarity_d operator""_mM (long double v) { return Molarity_d{static_cast<double>(v)};       }
  [[nodiscard]] constexpr Molarity_d operator""_uM (long double v) { return Molarity_d{static_cast<double>(v)*1e-3};  }
  [[nodiscard]] constexpr Kelvin     operator""_K  (long double v) { return Kelvin    {static_cast<double>(v)};       }
}

} // namespace olang::units
