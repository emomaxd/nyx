#pragma once

#include "nyx/core/base.h"
#include "nyx/math/vec3.h"

namespace nyx {

class Mat3 {
public:
    real_t m[3][3];

    Mat3() {
        m[0][0] = 1.0f; m[0][1] = 0.0f; m[0][2] = 0.0f;
        m[1][0] = 0.0f; m[1][1] = 1.0f; m[1][2] = 0.0f;
        m[2][0] = 0.0f; m[2][1] = 0.0f; m[2][2] = 1.0f;
    }

    Mat3(real_t m00, real_t m01, real_t m02,
         real_t m10, real_t m11, real_t m12,
         real_t m20, real_t m21, real_t m22) {
        m[0][0] = m00; m[0][1] = m01; m[0][2] = m02;
        m[1][0] = m10; m[1][1] = m11; m[1][2] = m12;
        m[2][0] = m20; m[2][1] = m21; m[2][2] = m22;
    }

    Vec3 operator*(const Vec3& v) const {
        return Vec3(
            m[0][0] * v.X + m[0][1] * v.Y + m[0][2] * v.Z,
            m[1][0] * v.X + m[1][1] * v.Y + m[1][2] * v.Z,
            m[2][0] * v.X + m[2][1] * v.Y + m[2][2] * v.Z
        );
    }

    Mat3 inverse() const {
        real_t det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
                     m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
                     m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);

        if (std::abs(det) < 1e-6f) {
            return Mat3(); // Return identity if non-invertible
        }

        real_t invDet = 1.0f / det;
        Mat3 result;
        result.m[0][0] = (m[1][1] * m[2][2] - m[1][2] * m[2][1]) * invDet;
        result.m[0][1] = (m[0][2] * m[2][1] - m[0][1] * m[2][2]) * invDet;
        result.m[0][2] = (m[0][1] * m[1][2] - m[0][2] * m[1][1]) * invDet;
        result.m[1][0] = (m[1][2] * m[2][0] - m[1][0] * m[2][2]) * invDet;
        result.m[1][1] = (m[0][0] * m[2][2] - m[0][2] * m[2][0]) * invDet;
        result.m[1][2] = (m[0][2] * m[1][0] - m[0][0] * m[1][2]) * invDet;
        result.m[2][0] = (m[1][0] * m[2][1] - m[1][1] * m[2][0]) * invDet;
        result.m[2][1] = (m[0][1] * m[2][0] - m[0][0] * m[2][1]) * invDet;
        result.m[2][2] = (m[0][0] * m[1][1] - m[0][1] * m[1][0]) * invDet;

        return result;
    }

    bool isValid() const {
        real_t det = m[0][0] * (m[1][1] * m[2][2] - m[1][2] * m[2][1]) -
                     m[0][1] * (m[1][0] * m[2][2] - m[1][2] * m[2][0]) +
                     m[0][2] * (m[1][0] * m[2][1] - m[1][1] * m[2][0]);
        return std::abs(det) > 1e-6f;
    }
};

} // namespace nyx