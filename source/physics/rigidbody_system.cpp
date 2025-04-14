#include "physics/rigidbody_system.h"

namespace nyx {

RigidbodyData::RigidbodyData() {
    Positions.reserve(kInitialEntityCount);
    Velocities.reserve(kInitialEntityCount);
    Forces.reserve(kInitialEntityCount);
    Masses.reserve(kInitialEntityCount);
    InvMasses.reserve(kInitialEntityCount);
    Active.reserve(kInitialEntityCount);
    // Add storage for previous positions (needed for Verlet)
    PrevPositions.reserve(kInitialEntityCount);
}

RigidbodySystem::RigidbodySystem() = default;

size_t RigidbodySystem::addRigidbody(const Vec3& pos, const Vec3& vel, real_t mass) {
    size_t id = Data.Positions.size();
    Data.Positions.emplace_back(pos);
    Data.Velocities.emplace_back(vel);
    Data.Forces.emplace_back(Vec3{0, 0, 0});
    Data.Masses.emplace_back(mass);
    Data.InvMasses.emplace_back(mass > 0 ? 1.0f / mass : 0.0f);
    Data.Active.emplace_back(1);
    // Initialize previous position (assume at t=0, prev = current - vel * dt)
    Data.PrevPositions.emplace_back(pos - vel * 0.0f); // dt=0 for initial setup
    return id;
}

void RigidbodySystem::update(real_t dt) {
    updateRigidbodies(dt);
    clearForces();
}

void RigidbodySystem::updateRigidbodies(real_t dt) {
    size_t count = Data.Positions.size();
    for (size_t i = 0; i < count; ++i) {
        if (!Data.Active[i]) {
            continue;
        }

        // Velocity Verlet integration
        // Step 1: Compute current acceleration
        Vec3 accel = Data.Forces[i] * Data.InvMasses[i];

        // Step 2: Store current position for velocity update
        Vec3 currPos = Data.Positions[i];

        // Step 3: Update position using Verlet formula
        // pos(t + dt) = 2 * pos(t) - pos(t - dt) + accel * dt^2
        Data.Positions[i] = 2.0f * Data.Positions[i] - Data.PrevPositions[i] + accel * dt * dt;

        // Step 4: Update previous position
        Data.PrevPositions[i] = currPos;

        // Step 5: Update velocity using average acceleration
        // For velocity, we use: vel(t + dt) = (pos(t + dt) - pos(t - dt)) / (2 * dt)
        Data.Velocities[i] = (Data.Positions[i] - Data.PrevPositions[i]) / (2.0f * dt);
    }
}

void RigidbodySystem::clearForces() {
    size_t count = Data.Forces.size();
    for (size_t i = 0; i < count; ++i) {
        if (Data.Active[i]) {
            Data.Forces[i] = Vec3{0, 0, 0};
        }
    }
}

}  // namespace nyx