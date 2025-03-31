#pragma once

#include <smmintrin.h>

#include "core/base.h"

namespace nyx {

constexpr size_t kVec2ElementCount = 2;
constexpr size_t kVec2BaseSize = kVec2ElementCount * sizeof(real_t);

class alignas(16) Vec2 {
public:
    NYX_FORCEINLINE Vec2() : Value(_mm_setzero_ps()) {}
    NYX_FORCEINLINE Vec2(float x, float y) 
        : Value(_mm_set_ps(0, 0, y, x)) {}
    NYX_FORCEINLINE Vec2(__m128 m) : Value(m) {}

    // arithmetic operators with Vec2
    NYX_FORCEINLINE Vec2 operator+(const Vec2& b) const {
        return _mm_add_ps(Value, b.Value);
    }
    NYX_FORCEINLINE Vec2 operator-(const Vec2& b) const {
        return _mm_sub_ps(Value, b.Value);
    }
    NYX_FORCEINLINE Vec2 operator*(const Vec2& b) const {
        return _mm_mul_ps(Value, b.Value);
    }
    NYX_FORCEINLINE Vec2 operator/(const Vec2& b) const {
        return _mm_div_ps(Value, b.Value);
    }

    // op= operators with Vec2
    NYX_FORCEINLINE Vec2& operator+=(const Vec2& b) {
        Value = _mm_add_ps(Value, b.Value);
        return *this;
    }
    NYX_FORCEINLINE Vec2& operator-=(const Vec2& b) {
        Value = _mm_sub_ps(Value, b.Value);
        return *this;
    }
    NYX_FORCEINLINE Vec2& operator*=(const Vec2& b) {
        Value = _mm_mul_ps(Value, b.Value);
        return *this;
    }
    NYX_FORCEINLINE Vec2& operator/=(const Vec2& b) {
        Value = _mm_div_ps(Value, b.Value);
        return *this;
    }

    // arithmetic operators with float
    NYX_FORCEINLINE Vec2 operator+(float b) const {
        return _mm_add_ps(Value, _mm_set1_ps(b));
    }
    NYX_FORCEINLINE Vec2 operator-(float b) const {
        return _mm_sub_ps(Value, _mm_set1_ps(b));
    }
    NYX_FORCEINLINE Vec2 operator*(float b) const {
        return _mm_mul_ps(Value, _mm_set1_ps(b));
    }
    NYX_FORCEINLINE Vec2 operator/(float b) const {
        return _mm_div_ps(Value, _mm_set1_ps(b));
    }

    // op= operators with float
    NYX_FORCEINLINE Vec2& operator+=(float b) {
        Value = _mm_add_ps(Value, _mm_set1_ps(b));
        return *this;
    }
    NYX_FORCEINLINE Vec2& operator-=(float b) {
        Value = _mm_sub_ps(Value, _mm_set1_ps(b));
        return *this;
    }
    NYX_FORCEINLINE Vec2& operator*=(float b) {
        Value = _mm_mul_ps(Value, _mm_set1_ps(b));
        return *this;
    }
    NYX_FORCEINLINE Vec2& operator/=(float b) {
        Value = _mm_div_ps(Value, _mm_set1_ps(b));
        return *this;
    }

    // dot product with another vector
    NYX_FORCEINLINE float dot(const Vec2& b) const {
        return _mm_cvtss_f32(_mm_dp_ps(Value, b.Value, 0x31));  // Mask changed for 2 components
    }

    // length of the vector
    NYX_FORCEINLINE float length() const {
        return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(Value, Value, 0x31)));
    }

    // 1/length() of the vector
    NYX_FORCEINLINE float rlength() const {
        return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_dp_ps(Value, Value, 0x31)));
    }

    // returns the vector scaled to unit length
    NYX_FORCEINLINE Vec2 normalize() const {
        return _mm_mul_ps(Value, _mm_rsqrt_ps(_mm_dp_ps(Value, Value, 0x3F)));
    }

    // overloaded operators that ensure alignment
#ifdef WIN32
    NYX_FORCEINLINE void* operator new[](size_t x) {
        return _aligned_malloc(x, 16);
    }
    NYX_FORCEINLINE void operator delete[](void* x) {
        if (x)
            _aligned_free(x);
    }
#endif

#ifdef __APPLE__
    NYX_FORCEINLINE void* operator new[](size_t x) { return _mm_malloc(x, 16); }
    NYX_FORCEINLINE void operator delete[](void* x) {
        if (x)
            _mm_free(x);
    }
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
    // Member variables
    union {
        struct {
            float X, Y;
        };
        __m128 Value;
    };
#pragma GCC diagnostic pop
};

NYX_FORCEINLINE Vec2 operator+(float a, const Vec2& b) { return b + a; }
NYX_FORCEINLINE Vec2 operator-(float a, const Vec2& b) {
    return Vec2(_mm_set1_ps(a)) - b;
}
NYX_FORCEINLINE Vec2 operator*(float a, const Vec2& b) { return b * a; }
NYX_FORCEINLINE Vec2 operator/(float a, const Vec2& b) {
    return Vec2(_mm_set1_ps(a)) / b;
}

} /* namespace nyx */