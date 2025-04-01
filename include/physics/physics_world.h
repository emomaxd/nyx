#pragma once

#include "rigidbody_system.h"

namespace nyx {

class PhysicsWorld {
public:
    PhysicsWorld();
    ~PhysicsWorld() = default;

    size_t addRigidbody(const Vec3& pos, const Vec3& vel, real_t mass);
    const RigidbodyData& getRigidbodyData() const { return RigidbodySystem.getData(); }
    RigidbodyData& accessRigidbodyData() { return RigidbodySystem.accessData(); }

    void update(real_t dt);

private:
    RigidbodySystem RigidbodySystem;
};

}  // namespace nyx