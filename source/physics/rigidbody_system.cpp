#include "physics/rigidbody_system.h"

namespace nyx {

RigidbodyData::RigidbodyData() {
    Positions.reserve(kInitialEntityCount);
    Velocities.reserve(kInitialEntityCount);
    Forces.reserve(kInitialEntityCount);
    Masses.reserve(kInitialEntityCount);
    InvMasses.reserve(kInitialEntityCount);
    Active.reserve(kInitialEntityCount);
}

RigidbodySystem::RigidbodySystem() = default;

size_t RigidbodySystem::addRigidbody(const Vec3& pos, const Vec3& vel, real_t mass) {
    size_t id = Data.Positions.size();
    Data.Positions.push_back(pos);
    Data.Velocities.push_back(vel);
    Data.Forces.push_back(Vec3{0, 0, 0});
    Data.Masses.push_back(mass);
    Data.InvMasses.push_back(mass > 0 ? 1.0f / mass : 0.0f);
    Data.Active.push_back(1);
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
        Vec3 accel = Data.Forces[i] * Data.InvMasses[i];
        Data.Velocities[i] += accel * dt;
        Data.Positions[i] += Data.Velocities[i] * dt;
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