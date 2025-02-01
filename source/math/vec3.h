#pragma once

#include <cmath>

#ifdef USE_DOUBLE_PRECISION
using real_t = double;
#else
using real_t = float;
#endif

namespace nyx::math
{

    class vec3
    {
      public:
        real_t x, y, z;

        vec3(real_t x = 0, real_t y = 0, real_t z = 0) : x(x), y(y), z(z)
        {}

        vec3 operator+(const vec3& other) const
        {
            return vec3(x + other.x, y + other.y, z + other.z);
        }

        real_t length() const
        {
            return std::sqrt(x * x + y * y + z * z);
        }

        vec3 normalized() const
        {
            real_t len = length();
            return vec3(x / len, y / len, z / len);
        }
    };

    inline vec3 operator*(const vec3& v, real_t scalar)
    {
        return vec3(v.x * scalar, v.y * scalar, v.z * scalar);
    }

    inline real_t dot(const vec3& a, const vec3& b) {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    inline vec3 cross(const vec3& a, const vec3& b) {
        return {a.y * b.z - a.z * b.y,
                a.z * b.x - a.x * b.z,
                a.x * b.y - a.y * b.x};
    }

} // namespace math
