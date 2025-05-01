#pragma once

#include <bit> // std::bit_ceil
#include <cmath>
#include <cstddef> // size_t

#include "nyx/core/base.h" // NYX_ALIGNAS_CACHE, NYX_FORCEINLINE, real_t
#include "nyx/math/math.h"

namespace nyx {

constexpr size_t kVec3ElementCount = 3;
constexpr size_t kVec3BaseSize = kVec3ElementCount * sizeof(real_t);
constexpr size_t kVec3Alignment = std::bit_ceil(kVec3BaseSize);

class alignas(kVec3Alignment) Vec3 {
public:
    real_t X, Y, Z;

    NYX_FORCEINLINE Vec3(real_t x = 0, real_t y = 0, real_t z = 0) : X(x), Y(y), Z(z) {}
    NYX_FORCEINLINE Vec3(const Vec3& other) : X(other.X), Y(other.Y), Z(other.Z) {}

    NYX_FORCEINLINE Vec3& operator=(const Vec3& other) {
        X = other.X; Y = other.Y; Z = other.Z;
        return *this;
    }

    NYX_FORCEINLINE Vec3 operator+(const Vec3& other) const {
        return Vec3{X + other.X, Y + other.Y, Z + other.Z};
    }

    NYX_FORCEINLINE Vec3 operator-(const Vec3& other) const {
        return Vec3{X - other.X, Y - other.Y, Z - other.Z};
    }

    NYX_FORCEINLINE Vec3 operator*(real_t scalar) const {
        return Vec3{X * scalar, Y * scalar, Z * scalar};
    }

    NYX_FORCEINLINE Vec3 operator/(real_t scalar) const {
        real_t inv = 1.0f / scalar;
        return Vec3{X * inv, Y * inv, Z * inv};
    }

    NYX_FORCEINLINE Vec3& operator+=(const Vec3& other) {
        X += other.X; Y += other.Y; Z += other.Z;
        return *this;
    }

    NYX_FORCEINLINE Vec3& operator-=(const Vec3& other) {
        X -= other.X; Y -= other.Y; Z -= other.Z;
        return *this;
    }

    NYX_FORCEINLINE Vec3& operator*=(real_t scalar) {
        X *= scalar; Y *= scalar; Z *= scalar;
        return *this;
    }

    NYX_FORCEINLINE Vec3& operator/=(real_t scalar) {
        real_t inv = 1.0f / scalar;
        X *= inv; Y *= inv; Z *= inv;
        return *this;
    }

    NYX_FORCEINLINE bool operator==(const Vec3& other) const {
        return X == other.X && Y == other.Y && Z == other.Z;
    }

    NYX_FORCEINLINE bool operator!=(const Vec3& other) const {
        return !(*this == other);
    }

    NYX_FORCEINLINE Vec3 operator-() const {
        return Vec3{-X, -Y, -Z};
    }

    NYX_FORCEINLINE real_t length() const {
        const real_t len = nyx::sqrt(X*X + Y*Y + Z*Z); 
        return len;
    }

    NYX_FORCEINLINE Vec3 normalize() {
        real_t len = length();
        if (len <= 0) 
        {
            return Vec3{0};
        }
        
        Vec3 result{0, 0, 0};
        real_t inv = 1.0f / len;
        result *= inv;
        return result;    
    }
};

NYX_FORCEINLINE Vec3 operator*(real_t scalar, const Vec3& v) {
    return v * scalar;
}

NYX_FORCEINLINE Vec3 operator/(real_t scalar, const Vec3& v) {
    return Vec3{scalar / v.X, scalar / v.Y, scalar / v.Z};
}

NYX_FORCEINLINE real_t dot(const Vec3& a, const Vec3& b) {
    return a.X * b.X + a.Y * b.Y + a.Z * b.Z;
}

NYX_FORCEINLINE Vec3 cross(const Vec3& a, const Vec3& b) {
    return Vec3{
        a.Y * b.Z - a.Z * b.Y,
        a.Z * b.X - a.X * b.Z,
        a.X * b.Y - a.Y * b.X
    };
}

} // namespace nyx
