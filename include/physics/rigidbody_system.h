#pragma once

#include <cstdint>
#include <vector>

#include "core/base.h"
#include "math/vec3.h"

namespace nyx {

struct RigidbodyData {
    RigidbodyData();
    ~RigidbodyData() = default;

    NYX_FORCEINLINE const std::vector<Vec3>& getPositions() const { return Positions; }
    NYX_FORCEINLINE const std::vector<Vec3>& getPrevPositions() const { return PrevPositions; }
    NYX_FORCEINLINE const std::vector<Vec3>& getVelocities() const { return Velocities; }
    NYX_FORCEINLINE const std::vector<Vec3>& getForces() const { return Forces; }
    NYX_FORCEINLINE const std::vector<real_t>& getMasses() const { return Masses; }
    NYX_FORCEINLINE const std::vector<real_t>& getInvMasses() const { return InvMasses; }
    NYX_FORCEINLINE const std::vector<uint32_t>& getActiveFlags() const { return Active; }

    NYX_FORCEINLINE std::vector<Vec3>& accessPositions() { return Positions; }
    NYX_FORCEINLINE std::vector<Vec3>& accessPrevPositions() { return PrevPositions; }
    NYX_FORCEINLINE std::vector<Vec3>& accessVelocities() { return Velocities; }
    NYX_FORCEINLINE std::vector<Vec3>& accessForces() { return Forces; }

private:
    static constexpr size_t kInitialEntityCount = 10'000;

    NYX_ALIGNAS_CACHE std::vector<Vec3> Positions;
    NYX_ALIGNAS_CACHE std::vector<Vec3> PrevPositions;
    NYX_ALIGNAS_CACHE std::vector<Vec3> Velocities;
    NYX_ALIGNAS_CACHE std::vector<Vec3> Forces;
    NYX_ALIGNAS_CACHE std::vector<real_t> Masses;
    NYX_ALIGNAS_CACHE std::vector<real_t> InvMasses;
    NYX_ALIGNAS_CACHE std::vector<uint32_t> Active;

    friend class RigidbodySystem;
};

class RigidbodySystem {
public:
    RigidbodySystem();
    ~RigidbodySystem() = default;

    size_t addRigidbody(const Vec3& pos, const Vec3& vel, real_t mass);
    void update(real_t dt);
    NYX_FORCEINLINE const RigidbodyData& getData() const { return Data; }
    NYX_FORCEINLINE RigidbodyData& accessData() { return Data; }

private:
    void updateRigidbodies(real_t dt);
    void clearForces();

    RigidbodyData Data;
};

}  // namespace nyx