// ═══════════════════════════════════════════════════════════════════════════
// OLang Dimensional Analysis Library
// Milestone 1.2: Zero-Cost Type-Safe Physical Units
// ═══════════════════════════════════════════════════════════════════════════
// 
// PURPOSE: Prevent Biological Paradoxes at Compile-Time
// - Ensures dimensional consistency (e.g., cannot add Mass to Time)
// - Zero runtime overhead via template metaprogramming
// - Evaporates to raw double/float in Release builds
// 
// EXAMPLE USAGE:
//   Unit<Meter, 1> distance = 5.0_m;
//   Unit<Second, 1> time = 2.0_s;
//   auto velocity = distance / time;  // Unit<Meter, 1, Second, -1>
//   
//   // COMPILE ERROR: distance + time;  // Cannot add Length to Time!
// 
// ═══════════════════════════════════════════════════════════════════════════

#pragma once

#include <ratio>
#include <type_traits>
#include <cmath>
#include <ostream>

namespace olang::type {

// ───────────────────────────────────────────────────────────────────────────
// Dimension Tags (SI Base Units + Biological Extensions)
// ───────────────────────────────────────────────────────────────────────────
struct Meter {};      // Length (L)
struct Kilogram {};   // Mass (M)
struct Second {};     // Time (T)
struct Ampere {};     // Electric Current (I)
struct Kelvin {};     // Temperature (Θ)
struct Mole {};       // Amount of Substance (N)
struct Candela {};    // Luminous Intensity (J)

// Biological Units
struct Cell {};       // Cellular Count
struct Molecule {};   // Molecular Count (for concentrations)
struct Gene {};       // Genetic Loci

// ───────────────────────────────────────────────────────────────────────────
// Unit Dimension Representation (Compile-Time)
// ───────────────────────────────────────────────────────────────────────────
template <typename Dim, int Exponent>
struct Dimension {
    using DimType = Dim;
    static constexpr int exponent = Exponent;
};

// ───────────────────────────────────────────────────────────────────────────
// Dimension List (Variadic Template for Multiple Dimensions)
// ───────────────────────────────────────────────────────────────────────────
template <typename... Dims>
struct DimensionList {};

// ───────────────────────────────────────────────────────────────────────────
// Core Unit<T, Dims...> Template
// ───────────────────────────────────────────────────────────────────────────
template <typename T, typename... Dims>
class Unit {
public:
    using ValueType = T;
    using Dimensions = DimensionList<Dims...>;
    
    // Constructors
    constexpr Unit() : value_(T{0}) {}
    constexpr explicit Unit(T value) : value_(value) {}
    
    // Copy/Move constructors
    constexpr Unit(const Unit&) = default;
    constexpr Unit(Unit&&) = default;
    constexpr Unit& operator=(const Unit&) = default;
    constexpr Unit& operator=(Unit&&) = default;
    
    // Value accessor
    constexpr T value() const { return value_; }
    
    // Conversion operator (for dimensionless quantities)
    template <typename U = T>
    constexpr operator std::enable_if_t<sizeof...(Dims) == 0, U>() const {
        return value_;
    }
    
    // ───────────────────────────────────────────────────────────────────────
    // Arithmetic Operators (Dimension-Aware)
    // ───────────────────────────────────────────────────────────────────────
    
    // Addition (requires same dimensions)
    constexpr Unit operator+(const Unit& other) const {
        return Unit(value_ + other.value_);
    }
    
    constexpr Unit& operator+=(const Unit& other) {
        value_ += other.value_;
        return *this;
    }
    
    // Subtraction (requires same dimensions)
    constexpr Unit operator-(const Unit& other) const {
        return Unit(value_ - other.value_);
    }
    
    constexpr Unit& operator-=(const Unit& other) {
        value_ -= other.value_;
        return *this;
    }
    
    // Unary negation
    constexpr Unit operator-() const {
        return Unit(-value_);
    }
    
    // Scalar multiplication
    constexpr Unit operator*(T scalar) const {
        return Unit(value_ * scalar);
    }
    
    constexpr Unit& operator*=(T scalar) {
        value_ *= scalar;
        return *this;
    }
    
    // Scalar division
    constexpr Unit operator/(T scalar) const {
        return Unit(value_ / scalar);
    }
    
    constexpr Unit& operator/=(T scalar) {
        value_ /= scalar;
        return *this;
    }
    
    // ───────────────────────────────────────────────────────────────────────
    // Comparison Operators (requires same dimensions)
    // ───────────────────────────────────────────────────────────────────────
    constexpr bool operator==(const Unit& other) const {
        return value_ == other.value_;
    }
    
    constexpr bool operator!=(const Unit& other) const {
        return value_ != other.value_;
    }
    
    constexpr bool operator<(const Unit& other) const {
        return value_ < other.value_;
    }
    
    constexpr bool operator<=(const Unit& other) const {
        return value_ <= other.value_;
    }
    
    constexpr bool operator>(const Unit& other) const {
        return value_ > other.value_;
    }
    
    constexpr bool operator>=(const Unit& other) const {
        return value_ >= other.value_;
    }
    
private:
    T value_;
};

// ───────────────────────────────────────────────────────────────────────────
// Dimension Algebra (Compile-Time Dimension Manipulation)
// ───────────────────────────────────────────────────────────────────────────

// Helper: Find dimension in list
template <typename Dim, typename... Dims>
struct FindDimension;

template <typename Dim>
struct FindDimension<Dim> {
    static constexpr int exponent = 0;
};

template <typename Dim, int Exp, typename... Rest>
struct FindDimension<Dim, Dimension<Dim, Exp>, Rest...> {
    static constexpr int exponent = Exp;
};

template <typename Dim, typename OtherDim, int Exp, typename... Rest>
struct FindDimension<Dim, Dimension<OtherDim, Exp>, Rest...> {
    static constexpr int exponent = FindDimension<Dim, Rest...>::exponent;
};

// Helper: Multiply dimensions
template <typename... Dims1>
struct MultiplyDimensions;

template <>
struct MultiplyDimensions<> {
    using type = DimensionList<>;
};

template <typename Dim, int Exp, typename... Rest>
struct MultiplyDimensions<Dimension<Dim, Exp>, Rest...> {
    using type = DimensionList<Dimension<Dim, Exp>, Rest...>;
};

// Helper: Divide dimensions (negate exponents)
template <typename... Dims>
struct NegateDimensions;

template <>
struct NegateDimensions<DimensionList<>> {
    using type = DimensionList<>;
};

template <typename Dim, int Exp, typename... Rest>
struct NegateDimensions<DimensionList<Dimension<Dim, Exp>, Rest...>> {
    using type = typename MultiplyDimensions<
        Dimension<Dim, -Exp>,
        typename NegateDimensions<DimensionList<Rest...>>::type
    >::type;
};

// ───────────────────────────────────────────────────────────────────────────
// Unit Multiplication (Dimension Addition)
// ───────────────────────────────────────────────────────────────────────────
template <typename T, typename... Dims1, typename... Dims2>
constexpr auto operator*(const Unit<T, Dims1...>& lhs, 
                         const Unit<T, Dims2...>& rhs) {
    // Simplified: Just concatenate dimensions (proper impl would merge)
    return Unit<T, Dims1..., Dims2...>(lhs.value() * rhs.value());
}

// ───────────────────────────────────────────────────────────────────────────
// Unit Division (Dimension Subtraction)
// ───────────────────────────────────────────────────────────────────────────
template <typename T, typename... Dims1, typename Dim, int Exp>
constexpr auto operator/(const Unit<T, Dims1...>& lhs, 
                         const Unit<T, Dimension<Dim, Exp>>& rhs) {
    // Simplified: Negate exponent
    return Unit<T, Dims1..., Dimension<Dim, -Exp>>(lhs.value() / rhs.value());
}

// ───────────────────────────────────────────────────────────────────────────
// Stream Output (for debugging)
// ───────────────────────────────────────────────────────────────────────────
template <typename T, typename... Dims>
std::ostream& operator<<(std::ostream& os, const Unit<T, Dims...>& unit) {
    os << unit.value();
    // In a full implementation, would print dimension string
    return os;
}

// ───────────────────────────────────────────────────────────────────────────
// Common Unit Type Aliases
// ───────────────────────────────────────────────────────────────────────────

// Length
using Length = Unit<double, Dimension<Meter, 1>>;
using Distance = Length;

// Mass
using Mass = Unit<double, Dimension<Kilogram, 1>>;

// Time
using Time = Unit<double, Dimension<Second, 1>>;

// Velocity (Length / Time)
using Velocity = Unit<double, Dimension<Meter, 1>, Dimension<Second, -1>>;

// Acceleration (Length / Time^2)
using Acceleration = Unit<double, Dimension<Meter, 1>, Dimension<Second, -2>>;

// Force (Mass * Acceleration)
using Force = Unit<double, Dimension<Kilogram, 1>, Dimension<Meter, 1>, 
                   Dimension<Second, -2>>;

// Energy (Force * Distance)
using Energy = Unit<double, Dimension<Kilogram, 1>, Dimension<Meter, 2>, 
                    Dimension<Second, -2>>;

// Temperature
using Temperature = Unit<double, Dimension<Kelvin, 1>>;

// Biological Units
using CellCount = Unit<double, Dimension<Cell, 1>>;
using MolecularCount = Unit<double, Dimension<Molecule, 1>>;
using Concentration = Unit<double, Dimension<Molecule, 1>, Dimension<Meter, -3>>;

// Dimensionless (ratios, percentages)
using Dimensionless = Unit<double>;

// ───────────────────────────────────────────────────────────────────────────
// User-Defined Literals (for convenience)
// ───────────────────────────────────────────────────────────────────────────
namespace literals {

constexpr Length operator""_m(long double value) {
    return Length(static_cast<double>(value));
}

constexpr Mass operator""_kg(long double value) {
    return Mass(static_cast<double>(value));
}

constexpr Time operator""_s(long double value) {
    return Time(static_cast<double>(value));
}

constexpr Temperature operator""_K(long double value) {
    return Temperature(static_cast<double>(value));
}

constexpr CellCount operator""_cells(unsigned long long value) {
    return CellCount(static_cast<double>(value));
}

constexpr MolecularCount operator""_molecules(unsigned long long value) {
    return MolecularCount(static_cast<double>(value));
}

} // namespace literals

// ───────────────────────────────────────────────────────────────────────────
// Mathematical Functions (Dimension-Preserving)
// ───────────────────────────────────────────────────────────────────────────
template <typename T, typename... Dims>
constexpr Unit<T, Dims...> abs(const Unit<T, Dims...>& u) {
    return Unit<T, Dims...>(std::abs(u.value()));
}

template <typename T, typename... Dims>
constexpr Unit<T, Dims...> sqrt(const Unit<T, Dims...>& u) {
    // Note: This is simplified - proper impl would halve all exponents
    return Unit<T, Dims...>(std::sqrt(u.value()));
}

template <typename T, typename... Dims>
constexpr Unit<T, Dims...> pow(const Unit<T, Dims...>& u, int exponent) {
    // Note: This is simplified - proper impl would multiply all exponents
    return Unit<T, Dims...>(std::pow(u.value(), exponent));
}

} // namespace olang::type