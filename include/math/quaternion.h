#ifndef QUATERNION_H
#define QUATERNION_H

#include "math/vec3.h"



namespace nyx {

constexpr size_t quaternionElementCount = 4;
constexpr size_t quaternionAlignment = quaternionElementCount * alignmentMultiplier;

struct alignas(quaternionAlignment) Quaternion {
  real_t X, Y, Z, W;

  Quaternion() : X(0.0f), Y(0.0f), Z(0.0f), W(1.0f) {}

  Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

  // Normalize the quaternion
  void normalize() {
    float len = X * X + Y * Y + Z * Z + W * W;
    if (len > 0.0f) {
      float invLen = 1.0f / sqrt(len);
      X *= invLen;
      Y *= invLen;
      Z *= invLen;
      W *= invLen;
    }
  }

  // Multiply two quaternions
  Quaternion operator*(const Quaternion &q) const {
    return Quaternion(W * q.X + X * q.W + Y * q.Z - Z * q.Y,
                      W * q.Y - X * q.Z + Y * q.W + Z * q.X,
                      W * q.Z + X * q.Y - Y * q.X + Z * q.W,
                      W * q.W - X * q.X - Y * q.Y - Z * q.Z);
  }

  // Quaternion-vector multiplication for rotating a vector
  Vec3 rotate(const Vec3 &v) const {
    Quaternion qv(0.0f, v.X, v.Y, v.Z);
    Quaternion qConjugate = conjugate();
    Quaternion qResult = *this * qv * qConjugate;
    return Vec3(qResult.X, qResult.Y, qResult.Z);
  }

  // Conjugate of a quaternion (for rotation inverse)
  Quaternion conjugate() const { return Quaternion(-X, -Y, -Z, W); }

  // Static function for creating a quaternion from axis and angle
  static Quaternion fromAxisAngle(const Vec3 &axis, float angle) {
    float halfAngle = angle * 0.5f;
    float s = sin(halfAngle);
    return Quaternion(axis.X * s, axis.Y * s, axis.Z * s, cos(halfAngle));
  }
};

} /* namespace nyx */
#endif
