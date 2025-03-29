#pragma once

#include <cmath>

#include "math/base.h"


namespace nyx {

constexpr size_t elementCount = 2;
constexpr size_t alignment = elementCount * alignmentMultiplier;


class alignas(alignment) Vec2 {
public:
  real_t X, Y;

  Vec2(real_t x = 0, real_t y = 0) : X(x), Y(y) {}

  inline Vec2 operator+(const Vec2 &other) const {
    return Vec2{X + other.X, Y + other.Y};
  }

  inline real_t length() const { return std::sqrt(X * X + Y * Y); }

  inline Vec2 normalized() const {
    real_t len = length();
    return Vec2(X / len, Y / len);
  }
};

inline auto operator*(const Vec2 &v, real_t scalar) -> Vec2 {
  return Vec2{v.X * scalar, v.Y * scalar};
}

inline auto dot(const Vec2 &a, const Vec2 &b) -> Vec2 {
  return a.X * b.X + a.Y * b.Y;
}

} /* namespace nyx */
