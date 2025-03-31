#pragma once

#include <cstdint>
#include <vector>

#include "core/base.h"
#include "math/vec3.h"

namespace nyx {

constexpr size_t kInitialEntityCount = 10'000;

struct RigidbodyData {
    NYX_ALIGNAS_CACHE std::vector<Vec3> Positions;
    NYX_ALIGNAS_CACHE std::vector<Vec3> Velocities;
    NYX_ALIGNAS_CACHE std::vector<Vec3> Forces;
    NYX_ALIGNAS_CACHE std::vector<real_t> Masses;
    NYX_ALIGNAS_CACHE std::vector<real_t> InvMasses;
    NYX_ALIGNAS_CACHE std::vector<uint32_t> Active;

    RigidbodyData() {
        Positions.reserve(kInitialEntityCount);
        Velocities.reserve(kInitialEntityCount);
        Forces.reserve(kInitialEntityCount);
        Masses.reserve(kInitialEntityCount);
        InvMasses.reserve(kInitialEntityCount);
        Active.reserve(kInitialEntityCount);
    }
};

class PhysicsWorld {
public:
    PhysicsWorld() = default;

    NYX_FORCEINLINE size_t addRigidbody(Vec3 pos, Vec3 vel, real_t mass) {
        size_t id = RigidbodyData.Positions.size();
        RigidbodyData.Positions.push_back(pos);
        RigidbodyData.Velocities.push_back(vel);
        RigidbodyData.Forces.push_back(Vec3{0, 0, 0});
        RigidbodyData.Masses.push_back(mass);
        RigidbodyData.InvMasses.push_back(mass > 0 ? 1.0f / mass : 0.0f);
        RigidbodyData.Active.push_back(1);
        return id;
    }

    NYX_FORCEINLINE void update(real_t dt) {
        updateRigidbodies(dt);
        // updateFluids(dt);
        // updateSoftbodies(dt);
    }

    // Readonly
    NYX_FORCEINLINE const RigidbodyData& getRigidbodyData() const { return RigidbodyData; }

    // Mutable
    NYX_FORCEINLINE RigidbodyData& accessRigidbodyData() { return RigidbodyData; }

private:
    NYX_FORCEINLINE void updateRigidbodies(real_t dt) {
        size_t count = RigidbodyData.Positions.size();
        for (size_t i = 0; i < count; ++i) {
            if (!RigidbodyData.Active[i]) continue;
            Vec3 accel = RigidbodyData.Forces[i] * RigidbodyData.InvMasses[i];
            RigidbodyData.Velocities[i] += accel * dt;
            RigidbodyData.Positions[i] += RigidbodyData.Velocities[i] * dt;
        }
        // resolveRigidbodyCollisions();
        clearRigidbodyForces();
    }

    NYX_FORCEINLINE void clearRigidbodyForces() {
        size_t count = RigidbodyData.Forces.size();
        for (size_t i = 0; i < count; ++i) {
            if (RigidbodyData.Active[i]) {
                RigidbodyData.Forces[i] = Vec3{0, 0, 0};
            }
        }
    }

private:
    RigidbodyData RigidbodyData;
    // FluidData FluidData;
    // SoftbodyData SoftbodyData;
};

} // namespace nyx