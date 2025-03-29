#ifndef VECTOR3_H
#define VECTOR3_H

#include <smmintrin.h>

namespace nyx {

#if !defined(__forceinline)
#define __forceinline inline __attribute__((always_inline))
#endif

#ifdef __GNUC__
class __attribute__((aligned(16))) Vec3
#else
_MM_ALIGN16 class Vec3
#endif
{
public:
  __forceinline Vec3() : Value(_mm_setzero_ps()) {}
  __forceinline Vec3(float x, float y, float z)
      : Value(_mm_set_ps(0, z, y, x)) {}
  __forceinline Vec3(__m128 m) : Value(m) {}

  // arithmetic operators with vector3
  __forceinline Vec3 operator+(const Vec3 &b) const {
    return _mm_add_ps(Value, b.Value);
  }
  __forceinline Vec3 operator-(const Vec3 &b) const {
    return _mm_sub_ps(Value, b.Value);
  }
  __forceinline Vec3 operator*(const Vec3 &b) const {
    return _mm_mul_ps(Value, b.Value);
  }
  __forceinline Vec3 operator/(const Vec3 &b) const {
    return _mm_div_ps(Value, b.Value);
  }

  // op= operators
  __forceinline Vec3 &operator+=(const Vec3 &b) {
    Value = _mm_add_ps(Value, b.Value);
    return *this;
  }
  __forceinline Vec3 &operator-=(const Vec3 &b) {
    Value = _mm_sub_ps(Value, b.Value);
    return *this;
  }
  __forceinline Vec3 &operator*=(const Vec3 &b) {
    Value = _mm_mul_ps(Value, b.Value);
    return *this;
  }
  __forceinline Vec3 &operator/=(const Vec3 &b) {
    Value = _mm_div_ps(Value, b.Value);
    return *this;
  }

  // arithmetic operators with float
  __forceinline Vec3 operator+(float b) const {
    return _mm_add_ps(Value, _mm_set1_ps(b));
  }
  __forceinline Vec3 operator-(float b) const {
    return _mm_sub_ps(Value, _mm_set1_ps(b));
  }
  __forceinline Vec3 operator*(float b) const {
    return _mm_mul_ps(Value, _mm_set1_ps(b));
  }
  __forceinline Vec3 operator/(float b) const {
    return _mm_div_ps(Value, _mm_set1_ps(b));
  }

  // op= operators with float
  __forceinline Vec3 &operator+=(float b) {
    Value = _mm_add_ps(Value, _mm_set1_ps(b));
    return *this;
  }
  __forceinline Vec3 &operator-=(float b) {
    Value = _mm_sub_ps(Value, _mm_set1_ps(b));
    return *this;
  }
  __forceinline Vec3 &operator*=(float b) {
    Value = _mm_mul_ps(Value, _mm_set1_ps(b));
    return *this;
  }
  __forceinline Vec3 &operator/=(float b) {
    Value = _mm_div_ps(Value, _mm_set1_ps(b));
    return *this;
  }

  // cross product
  __forceinline Vec3 cross(const Vec3 &b) const {
    return _mm_sub_ps(
        _mm_mul_ps(
            _mm_shuffle_ps(Value, Value, _MM_SHUFFLE(3, 0, 2, 1)),
            _mm_shuffle_ps(b.Value, b.Value, _MM_SHUFFLE(3, 1, 0, 2))),
        _mm_mul_ps(
            _mm_shuffle_ps(Value, Value, _MM_SHUFFLE(3, 1, 0, 2)),
            _mm_shuffle_ps(b.Value, b.Value, _MM_SHUFFLE(3, 0, 2, 1))));
  }

  // dot product with another vector
  __forceinline float dot(const Vec3 &b) const {
    return _mm_cvtss_f32(_mm_dp_ps(Value, b.Value, 0x71));
  }
  // length of the vector
  __forceinline float length() const {
    return _mm_cvtss_f32(_mm_sqrt_ss(_mm_dp_ps(Value, Value, 0x71)));
  }
  // 1/length() of the vector
  __forceinline float rlength() const {
    return _mm_cvtss_f32(_mm_rsqrt_ss(_mm_dp_ps(Value, Value, 0x71)));
  }
  // returns the vector scaled to unit length
  __forceinline Vec3 normalize() const {
    return _mm_mul_ps(Value, _mm_rsqrt_ps(_mm_dp_ps(Value, Value, 0x7F)));
  }

  // overloaded operators that ensure alignment
#ifdef WIN32
  __forceinline void *operator new[](size_t X) {
    return _aligned_malloc(X, 16);
  }
  __forceinline void operator delete[](void *X) {
    if (X)
      _aligned_free(X);
  }
#endif

#ifdef __APPLE__
  __forceinline void *operator new[](size_t X) { return _mm_malloc(X, 16); }
  __forceinline void operator delete[](void *X) {
    if (X)
      _mm_free(X);
  }
#endif

  // Member variables
  union {
    struct {
      float X, Y, Z;
    };
    __m128 Value;
  };
};

__forceinline Vec3 operator+(float a, const Vec3 &b) { return b + a; }
__forceinline Vec3 operator-(float a, const Vec3 &b) {
  return Vec3(_mm_set1_ps(a)) - b;
}
__forceinline Vec3 operator*(float a, const Vec3 &b) { return b * a; }
__forceinline Vec3 operator/(float a, const Vec3 &b) {
  return Vec3(_mm_set1_ps(a)) / b;
}

} /* namespace nyx */

#endif // VECTOR3_H
