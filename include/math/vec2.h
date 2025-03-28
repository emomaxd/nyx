#pragma once

#include <cmath>

#include "math/base.h"

constexpr size_t element_count = 2;
constexpr size_t alignment = element_count * alignment_multiplier;

namespace nyx::math
{

    class alignas(alignment) vec2
    {
      public:
        real_t x, y;

        vec2(real_t x = 0, real_t y = 0) : x(x), y(y) {}

        inline vec2 operator+(const vec2& other) const
        {
            return vec2{x + other.x, y + other.y};
        }

        inline real_t length() const
        {
            return std::sqrt(x * x + y * y);
        }

        inline vec2 normalized() const
        {
            real_t len = length();
            return vec2(x / len, y / len);
        }
    };

    inline auto operator*(const vec2& v, real_t scalar) -> vec2
    {
        return vec2{v.x * scalar, v.y * scalar};
    }

    inline auto dot(const vec2& a, const vec2& b) -> vec2
    {
        return a.x * b.x + a.y * b.y;
    }

} // namespace math
