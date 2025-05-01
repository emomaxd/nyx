#pragma once

#include <cstddef> // size_t

#include "nyx/core/base.h" // NYX_ALIGNAS_CACHE, NYX_FORCEINLINE, real_t
#include "nyx/math/math.h"

namespace nyx {

constexpr size_t kVec2ElementCount = 2;
constexpr size_t kVec2BaseSize = kVec2ElementCount * sizeof(real_t);

class alignas(kVec2BaseSize) Vec2 {
public:
    real_t X, Y;

    NYX_FORCEINLINE Vec2(real_t x = 0, real_t y = 0) : X(x), Y(y) {}
    NYX_FORCEINLINE Vec2(const Vec2& other) : X(other.X), Y(other.Y) {}

    NYX_FORCEINLINE Vec2& operator=(const Vec2& other) {
        X = other.X; Y = other.Y;
        return *this;
    }

    NYX_FORCEINLINE Vec2 operator+(const Vec2& other) const {
        return Vec2{X + other.X, Y + other.Y};
    }

    NYX_FORCEINLINE Vec2 operator-(const Vec2& other) const {
        return Vec2{X - other.X, Y - other.Y};
    }

    NYX_FORCEINLINE Vec2 operator*(real_t scalar) const {
        return Vec2{X * scalar, Y * scalar};
    }

    NYX_FORCEINLINE Vec2 operator/(real_t scalar) const {
        real_t inv = 1.0f / scalar;
        return Vec2{X * inv, Y * inv};
    }

    NYX_FORCEINLINE Vec2& operator+=(const Vec2& other) {
        X += other.X; Y += other.Y;
        return *this;
    }

    NYX_FORCEINLINE Vec2& operator-=(const Vec2& other) {
        X -= other.X; Y -= other.Y;
        return *this;
    }

    NYX_FORCEINLINE Vec2& operator*=(real_t scalar) {
        X *= scalar; Y *= scalar;
        return *this;
    }

    NYX_FORCEINLINE Vec2& operator/=(real_t scalar) {
        real_t inv = 1.0f / scalar;
        X *= inv; Y *= inv;
        return *this;
    }

    NYX_FORCEINLINE bool operator==(const Vec2& other) const {
        return X == other.X && Y == other.Y;
    }

    NYX_FORCEINLINE bool operator!=(const Vec2& other) const {
        return !(*this == other);
    }

    NYX_FORCEINLINE Vec2 operator-() const {
        return Vec2{-X, -Y};
    }

    NYX_FORCEINLINE real_t length() const {
        const real_t len = nyx::sqrt( X*X + Y*Y);
        return nyx::sqrt(len);
    }

    NYX_FORCEINLINE Vec2 normalized() const {
        real_t len = length();
        if (len > 0) {
            real_t inv = 1.0f / len;
            return Vec2{X * inv, Y * inv};
        }
        return *this;
    }

    NYX_FORCEINLINE void normalize() {
        real_t len = length();
        if (len > 0) {
            real_t inv = 1.0f / len;
            X *= inv; Y *= inv;
        }
    }
};

NYX_FORCEINLINE Vec2 operator*(real_t scalar, const Vec2& v) {
    return v * scalar;
}

NYX_FORCEINLINE Vec2 operator/(real_t scalar, const Vec2& v) {
    return Vec2{scalar / v.X, scalar / v.Y};
}

NYX_FORCEINLINE real_t dot(const Vec2& a, const Vec2& b) {
    return a.X * b.X + a.Y * b.Y;
}

} // namespace nyx
