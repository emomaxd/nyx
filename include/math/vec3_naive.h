#pragma once

#include <bit>
#include <cmath>

#include "math/base.h"



namespace nyx::math {

constexpr size_t vec3ElementCount = 3;
constexpr size_t vec3Alignment = vec3ElementCount * alignmentMultiplier;

/* (C++20) std::bit_ceil() -> The smallest integral power of two that is not smaller than x. */
constexpr size_t nextPowerOfTwo = std::bit_ceil(vec3Alignment);

class alignas(nextPowerOfTwo) Vec3 {
public:
  real_t X, Y, Z;

  Vec3(real_t x = 0, real_t y = 0, real_t z = 0) : X(x), Y(y), Z(z) {}

  inline Vec3 operator+(const Vec3 &other) const {
    return Vec3{X + other.X, Y + other.Y, Z + other.Z};
  }

  inline real_t length() const { return std::sqrt(X * X + Y * Y + Z * Z); }

  inline Vec3 normalized() const {
    real_t len = length();
    return Vec3(X / len, Y / len, Z / len);
  }
};

inline auto operator*(const Vec3 &v, real_t scalar) -> Vec3 {
  return Vec3(v.X * scalar, v.Y * scalar, v.Z * scalar);
}

inline auto dot(const Vec3 &a, const Vec3 &b) -> real_t {
  return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}

inline auto cross(const Vec3 &a, const Vec3 &b) -> Vec3 {
  return Vec3{a.Y * b.Z - a.Z * b.Y, a.Z * b.X - a.X * b.Z,
              a.X * b.Y - a.Y * b.X};
}

} // namespace nyx::math