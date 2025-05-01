#include "nyx/physics/rigidbody/rigidbody_system.h"
#include "nyx/math/vec3_naive.h"
#include <algorithm>
#include <cassert>

namespace nyx {

RigidbodyData::RigidbodyData() {
    Positions.reserve(kInitialEntityCount);
    Velocities.reserve(kInitialEntityCount);
    AngularVelocities.reserve(kInitialEntityCount);
    Orientations.reserve(kInitialEntityCount);
    Masses.reserve(kInitialEntityCount);
    InvMasses.reserve(kInitialEntityCount);
    Inertias.reserve(kInitialEntityCount);
    InvInertias.reserve(kInitialEntityCount);
    Active.reserve(kInitialEntityCount);
}

RigidbodySystem::RigidbodySystem() {
    // No additional initialization needed; RigidbodyData constructor handles it
}

size_t RigidbodySystem::addRigidbody(const Vec3& pos, const Vec3& vel, real_t mass, const Mat3& inertia) {
    assert(mass > 0.0f && "Mass must be positive");
    assert(inertia.isValid() && "Inertia tensor must be valid");

    size_t index = Data.Positions.size();
    Data.Positions.push_back(pos);
    Data.Velocities.push_back(vel);
    Data.AngularVelocities.push_back(Vec3(0.0f, 0.0f, 0.0f));
    Data.Orientations.push_back(Quaternion::identity());
    Data.Masses.push_back(mass);
    Data.InvMasses.push_back(1.0f / mass);
    Data.Inertias.push_back(inertia);
    Data.InvInertias.push_back(inertia.inverse());
    Data.Active.push_back(1); // Active by default

    return index;
}

void RigidbodySystem::update(real_t dt) {
    integrate(dt);
    clearForces(); // Forces are typically cleared after integration
}

void RigidbodySystem::applyImpulse(size_t index, const Vec3& impulse, const Vec3& contactVector) {
    assert(index < Data.Positions.size() && "Invalid rigidbody index");
    if (!Data.Active[index]) return;

    // Linear velocity change: v += impulse / mass
    Data.Velocities[index] += impulse * Data.InvMasses[index];

    // Angular velocity change: ω += I⁻¹ * (r × impulse)
    Vec3 torque = cross(contactVector,  impulse);
    Data.AngularVelocities[index] += Data.InvInertias[index] * torque;
}

void RigidbodySystem::integrate(real_t dt) {
    for (size_t i = 0; i < Data.Positions.size(); ++i) {
        if (!Data.Active[i]) continue;

        // Update position: p += v * dt
        Data.Positions[i] += Data.Velocities[i] * dt;

        // Update orientation: q += 0.5 * ω * q * dt
        Quaternion omega(0.0f, Data.AngularVelocities[i].X, Data.AngularVelocities[i].Y, Data.AngularVelocities[i].Z);
        Data.Orientations[i] += 0.5f * omega * Data.Orientations[i] * dt;
        Data.Orientations[i].normalize();

        // Note: Velocities and angular velocities are not updated here (assume forces/impulses handle it)
    }
}

void RigidbodySystem::clearForces() {
    // Currently, no accumulated forces are stored, so this is a no-op
    // If forces are added later, reset them here
}

} // namespace nyx