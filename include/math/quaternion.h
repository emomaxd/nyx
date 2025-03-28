#ifndef QUATERNION_H
#define QUATERNION_H

#include "math/vec3.h"

constexpr size_t element_count = 4;
constexpr size_t alignment = element_count * alignment_multiplier;

struct alignas(alignment) Quaternion {
    real_t x, y, z, w;

    Quaternion() : x(0.0f), y(0.0f), z(0.0f), w(1.0f) {}

    Quaternion(float x, float y, float z, float w) : x(x), y(y), z(z), w(w) {}

    // Normalize the quaternion
    void normalize() {
        float len = x * x + y * y + z * z + w * w;
        if (len > 0.0f) {
            float invLen = 1.0f / sqrt(len);
            x *= invLen;
            y *= invLen;
            z *= invLen;
            w *= invLen;
        }
    }

    // Multiply two quaternions
    Quaternion operator*(const Quaternion& q) const {
        return Quaternion(
            w * q.x + x * q.w + y * q.z - z * q.y,
            w * q.y - x * q.z + y * q.w + z * q.x,
            w * q.z + x * q.y - y * q.x + z * q.w,
            w * q.w - x * q.x - y * q.y - z * q.z
        );
    }

    // Quaternion-vector multiplication for rotating a vector
    Vec3 rotate(const Vec3& v) const {
        Quaternion qv(0.0f, v.x, v.y, v.z);
        Quaternion qConjugate = conjugate();
        Quaternion qResult = *this * qv * qConjugate;
        return Vec3(qResult.x, qResult.y, qResult.z);
    }

    // Conjugate of a quaternion (for rotation inverse)
    Quaternion conjugate() const {
        return Quaternion(-x, -y, -z, w);
    }

    // Static function for creating a quaternion from axis and angle
    static Quaternion fromAxisAngle(const Vec3& axis, float angle) {
        float halfAngle = angle * 0.5f;
        float s = sin(halfAngle);
        return Quaternion(axis.x * s, axis.y * s, axis.z * s, cos(halfAngle));
    }
};

#endif
