#pragma once

#include <cstdint>
#include <vector>

#include "core/base.h"
#include "math/vec3.h"

namespace nyx {

struct RigidbodyData {
    RigidbodyData();
    ~RigidbodyData() = default;

    const std::vector<Vec3>& getPositions() const { return Positions; }
    const std::vector<Vec3>& getVelocities() const { return Velocities; }
    const std::vector<Vec3>& getForces() const { return Forces; }
    const std::vector<real_t>& getMasses() const { return Masses; }
    const std::vector<real_t>& getInvMasses() const { return InvMasses; }
    const std::vector<uint32_t>& getActiveFlags() const { return Active; }

    std::vector<Vec3>& accessPositions() { return Positions; }
    std::vector<Vec3>& accessVelocities() { return Velocities; }
    std::vector<Vec3>& accessForces() { return Forces; }

private:
    static constexpr size_t kInitialEntityCount = 10'000;

    alignas(64) std::vector<Vec3> Positions;
    alignas(64) std::vector<Vec3> Velocities;
    alignas(64) std::vector<Vec3> Forces;
    alignas(64) std::vector<real_t> Masses;
    alignas(64) std::vector<real_t> InvMasses;
    alignas(64) std::vector<uint32_t> Active;

    friend class RigidbodySystem;
};

class RigidbodySystem {
public:
    RigidbodySystem();
    ~RigidbodySystem() = default;

    size_t addRigidbody(const Vec3& pos, const Vec3& vel, real_t mass);
    void update(real_t dt);
    const RigidbodyData& getData() const { return Data; }
    RigidbodyData& accessData() { return Data; }

private:
    void updateRigidbodies(real_t dt);
    void clearForces();

    RigidbodyData Data;
};

}  // namespace nyx