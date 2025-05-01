#pragma once

#include <bit> // std::bit_ceil
#include <smmintrin.h>

#include "nyx/core/base.h"

namespace nyx {

  constexpr size_t kVec3ElementCount = 3;
  constexpr size_t kVec3BaseSize = kVec3ElementCount * sizeof(real_t);
  constexpr size_t kVec3Alignment = std::bit_ceil(kVec3BaseSize);

class alignas(kVec3Alignment) Vec3
{
public:
  NYX_FORCEINLINE Vec3() : Value(_mm_setzero_ps()) {}
  NYX_FORCEINLINE Vec3(float x, float y, float z)
      : Value(_mm_set_ps(0, z, y, x)) {}
  NYX_FORCEINLINE Vec3(__m128 m) : Value(m) {}

  // arithmetic operators with vector3
  NYX_FORCEINLINE Vec3 operator+(const Vec3 &b) const {
    return _mm_add_ps(Value, b.Value);
  }
  NYX_FORCEINLINE Vec3 operator-(const Vec3 &b) const {
    return _mm_sub_ps(Value, b.Value);
  }
  NYX_FORCEINLINE Vec3 operator*(const Vec3 &b) const {
    return _mm_mul_ps(Value, b.Value);
  }
  NYX_FORCEINLINE Vec3 operator/(const Vec3 &b) const {
    return _mm_div_ps(Value, b.Value);
  }

  // op= operators
  NYX_FORCEINLINE Vec3 &operator+=(const Vec3 &b) {
    Value = _mm_add_ps(Value, b.Value);
    return *this;
  }
  NYX_FORCEINLINE Vec3 &operator-=(const Vec3 &b) {
    Value = _mm_sub_ps(Value, b.Value);
    return *this;
  }
  NYX_FORCEINLINE Vec3 &operator*=(const Vec3 &b) {
    Value = _mm_mul_ps(Value, b.Value);
    return *this;
  }
  NYX_FORCEINLINE Vec3 &operator/=(const Vec3 &b) {
    Value = _mm_div_ps(Value, b.Value);
    return *this;
  }

  // arithmetic operators with float
  NYX_FORCEINLINE Vec3 operator+(float b) const {
    return _mm_add_ps(Value, _mm_set1_ps(b));
  }
  NYX_FORCEINLINE Vec3 operator-(float b) const {
    return _mm_sub_ps(Value, _mm_set1_ps(b));
  }
  NYX_FORCEINLINE Vec3 operator*(float b) const {
    return _mm_mul_ps(Value, _mm_set1_ps(b));
  }
  NYX_FORCEINLINE Vec3 operator/(float b) const {
    return _mm_div_ps(Value, _mm_set1_ps(b));
  }

  // op= operators with float
  NYX_FORCEINLINE Vec3 &operator+=(float b) {
    Value = _mm_add_ps(Value, _mm_set1_ps(b));
    return *this;
  }
  NYX_FORCEINLINE Vec3 &operator-=(float b) {
    Value = _mm_sub_ps(Value, _mm_set1_ps(b));
    return *this;
  }
  NYX_FORCEINLINE Vec3 &operator*=(float b) {
    Value = _mm_mul_ps(Value, _mm_set1_ps(b));
    return *this;
  }
  NYX_FORCEINLINE Vec3 &operator/=(float b) {
    Value = _mm_div_ps(Value, _mm_set1_ps(b));
    return *this;
  }

  // cross product
  NYX_FORCEINLINE Vec3 cross(const Vec3 &b) const {
    return _mm_sub_ps(
        _mm_mul_ps(
            _mm_shuffle_ps(Value, Value, _MM_SHUFFLE(3, 0, 2, 1)),
            _mm_shuffle_ps(b.Value, b.Value, _MM_SHUFFLE(3, 1, 0, 2))),
        _mm_mul_ps(
            _mm_shuffle_ps(Value, Value, _MM_SHUFFLE(3, 1, 0, 2)),
            _mm_shuffle_ps(b.Value, b.Value, _MM_SHUFFLE(3, 0, 2, 1))));
  }

  // dot product with another vector
  NYX_FORCEINLINE float dot(const Vec3 &b) const {
    return _mm_cvtss_f32(_mm_dp_ps(Value, b.Value, 0x71));
  }
  // length of the vector
  NYX_FORCEINLINE float length() const {
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(Value, Value, 0x71)));
  }
  // 1/length() of the vector
  NYX_FORCEINLINE float rlength() const {
    return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_dp_ps(Value, Value, 0x71)));
  }
  // returns the vector scaled to unit length
  NYX_FORCEINLINE Vec3 normalize() const {
    return _mm_mul_ps(Value, _mm_rsqrt_ps(_mm_dp_ps(Value, Value, 0x7F)));
  }

  // overloaded operators that ensure alignment
#ifdef WIN32
  NYX_FORCEINLINE void *operator new[](size_t X) {
    return _aligned_malloc(X, 16);
  }
  NYX_FORCEINLINE void operator delete[](void *X) {
    if (X)
      _aligned_free(X);
  }
#endif

#ifdef __APPLE__
  NYX_FORCEINLINE void *operator new[](size_t X) { return _mm_malloc(X, 16); }
  NYX_FORCEINLINE void operator delete[](void *X) {
    if (X)
      _mm_free(X);
  }
#endif

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpedantic"
  // Member variables
  union {
    struct {
      float X, Y, Z;
    };
    __m128 Value;
  };
};
#pragma GCC diagnostic pop

NYX_FORCEINLINE Vec3 operator+(float a, const Vec3 &b) { return b + a; }
NYX_FORCEINLINE Vec3 operator-(float a, const Vec3 &b) {
  return Vec3(_mm_set1_ps(a)) - b;
}
NYX_FORCEINLINE Vec3 operator*(float a, const Vec3 &b) { return b * a; }
NYX_FORCEINLINE Vec3 operator/(float a, const Vec3 &b) {
  return Vec3(_mm_set1_ps(a)) / b;
}

} /* namespace nyx */
