#pragma once

#include <cstdint>
#include <vector>

#include "nyx/core/base.h"
#include "nyx/math/vec3.h"
#include "nyx/math/quaternion.h"
#include "nyx/math/mat3.h"

namespace nyx {

struct RigidbodyData {
    RigidbodyData();
    ~RigidbodyData() = default;

    NYX_FORCEINLINE const std::vector<Vec3>& getPositions() const { return Positions; }
    NYX_FORCEINLINE const std::vector<Vec3>& getVelocities() const { return Velocities; }
    NYX_FORCEINLINE const std::vector<Vec3>& getAngularVelocities() const { return AngularVelocities; }
    NYX_FORCEINLINE const std::vector<Quaternion>& getOrientations() const { return Orientations; }
    NYX_FORCEINLINE const std::vector<Mat3>& getInvInertias() const { return InvInertias; }

    NYX_FORCEINLINE std::vector<Vec3>& accessPositions() { return Positions; }
    NYX_FORCEINLINE std::vector<Vec3>& accessVelocities() { return Velocities; }
    NYX_FORCEINLINE std::vector<Vec3>& accessAngularVelocities() { return AngularVelocities; }
    NYX_FORCEINLINE std::vector<Quaternion>& accessOrientations() { return Orientations; }

private:
    static constexpr size_t kInitialEntityCount = 10'000;

    NYX_ALIGNAS_CACHE std::vector<Vec3> Positions;
    NYX_ALIGNAS_CACHE std::vector<Vec3> Velocities;
    NYX_ALIGNAS_CACHE std::vector<Vec3> AngularVelocities;
    NYX_ALIGNAS_CACHE std::vector<Quaternion> Orientations;

    NYX_ALIGNAS_CACHE std::vector<real_t> Masses;
    NYX_ALIGNAS_CACHE std::vector<real_t> InvMasses;
    NYX_ALIGNAS_CACHE std::vector<Mat3> Inertias;      // local space
    NYX_ALIGNAS_CACHE std::vector<Mat3> InvInertias;   // local space

    NYX_ALIGNAS_CACHE std::vector<uint32_t> Active;

    friend class RigidbodySystem;
};

class RigidbodySystem {
public:
    RigidbodySystem();
    ~RigidbodySystem() = default;

    size_t addRigidbody(const Vec3& pos, const Vec3& vel, real_t mass, const Mat3& inertia);
    void update(real_t dt);
    void applyImpulse(size_t index, const Vec3& impulse, const Vec3& contactVector);

    NYX_FORCEINLINE const RigidbodyData& getData() const { return Data; }
    NYX_FORCEINLINE RigidbodyData& accessData() { return Data; }

private:
    void integrate(real_t dt);
    void clearForces();

    RigidbodyData Data;
};

}  // namespace nyx
