#pragma once

#include <assert.h>

#include "nyx/core/base.h"
#include "nyx/math/vec3.h"

namespace nyx {

class Quaternion {
public:
  real_t w, x, y, z;

  Quaternion() : w(1.0f), x(0.0f), y(0.0f), z(0.0f) {}
  Quaternion(real_t w, real_t x, real_t y, real_t z) : w(w), x(x), y(y), z(z) {}
  Quaternion(real_t w, const Vec3& v) : w(w), x(v.X), y(v.Y), z(v.Z) {}

  static Quaternion identity() { return Quaternion(1.0f, 0.0f, 0.0f, 0.0f); }

  Quaternion operator*(const Quaternion& other) const {
    return Quaternion(
        w * other.w - x * other.x - y * other.y - z * other.z,
        w * other.x + x * other.w + y * other.z - z * other.y,
        w * other.y - x * other.z + y * other.w + z * other.x,
        w * other.z + x * other.y - y * other.x + z * other.w
    );
  }

  Quaternion operator*(real_t scalar) const {
    return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
  }

  Quaternion operator+(const Quaternion& other) const {
    return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
  }

  Vec3 operator*(const Vec3& v) const {
    Quaternion qv(0.0f, v);
    Quaternion qConj(w, -x, -y, -z);
    Quaternion result = (*this) * qv * qConj;
    return Vec3(result.x, result.y, result.z);
  }


  Quaternion& operator+=(const Quaternion& other) {
    w += other.w;
    x += other.x;
    y += other.y;
    z += other.z;
    return *this;
  }
  void normalize() {
    real_t mag = std::sqrt(w * w + x * x + y * y + z * z);
    if (mag > 0.0f) {
      real_t invMag = 1.0f / mag;
      w *= invMag;
      x *= invMag;
      y *= invMag;
      z *= invMag;
    }
  }
  Quaternion inverse() const {
    real_t normSq = w*w + x*x + y*y + z*z;
    if (normSq == 0.0f) {
      assert(false);
      return Quaternion(0.0f, 0.0f, 0.0f, 0.0f);
    }
    return Quaternion(w, -x, -y, -z) * (1.0f / normSq);
  }

};

// Non-member operator for float * Quaternion
inline Quaternion operator*(real_t scalar, const Quaternion& q) {
  return q * scalar; // Reuse the member operator
}

} // namespace nyx