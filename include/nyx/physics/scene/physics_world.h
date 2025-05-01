#pragma once

#include "nyx/physics/rigidbody/rigidbody_system.h"

namespace nyx {

class PhysicsWorld {
public:
    PhysicsWorld();
    ~PhysicsWorld() = default;

    size_t addRigidbody(const Vec3& pos, const Vec3& vel, real_t mass);
    const RigidbodyData& getRigidbodyData() const { return Rb.getData(); }
    RigidbodyData& accessRigidbodyData() { return Rb.accessData(); }

    void update(real_t dt);

private:
    RigidbodySystem Rb;
};

}  // namespace nyx
