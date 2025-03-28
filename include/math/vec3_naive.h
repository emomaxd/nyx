#pragma once

#include <bit>
#include <cmath>

#include "math/base.h"

constexpr size_t element_count = 3;
constexpr size_t alignment = element_count * alignment_multiplier;
constexpr size_t next_power_of_two = std::bit_ceil(alignment);

namespace nyx::math
{

    class alignas(next_power_of_two) vec3
    {
      public:
        real_t x, y, z;

        vec3(real_t x = 0, real_t y = 0, real_t z = 0) : x(x), y(y), z(z) {}

        inline vec3 operator+(const vec3& other) const
        {
            return vec3{x + other.x, y + other.y, z + other.z};
        }

        inline real_t length() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        inline vec3 normalized() const
        {
            real_t len = length();
            return vec3(x / len, y / len, z / len);
        }
    };

    inline auto operator*(const vec3& v, real_t scalar) -> vec3
    {
        return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
    }

    inline auto dot(const vec3& a, const vec3& b) -> real_t {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    inline auto cross(const vec3& a, const vec3& b) -> vec3 {
        return vec3{a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x};
    }

} // namespace math
