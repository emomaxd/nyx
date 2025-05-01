#include "nyx/physics/scene/physics_world.h"

namespace nyx {

PhysicsWorld::PhysicsWorld() = default;

size_t PhysicsWorld::addRigidbody(const Vec3& pos, const Vec3& vel, real_t mass, const Mat3& inertia) {
    return Rb.addRigidbody(pos, vel, mass, inertia);
}

void PhysicsWorld::update(real_t dt) {
    Rb.update(dt);
}

} // namespace nyx