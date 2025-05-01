#pragma once

#include "nyx/core/base.h"
#include "nyx/math/vec3.h"
#include "nyx/math/mat3.h"
#include "nyx/physics/rigidbody/rigidbody_system.h"

namespace nyx {

class PhysicsWorld {
public:
    PhysicsWorld();
    ~PhysicsWorld() = default;

    size_t addRigidbody(const Vec3& pos, const Vec3& vel, real_t mass, const Mat3& inertia);
    void update(real_t dt);

    NYX_FORCEINLINE const RigidbodyData& getRigidbodyData() const { return Rb.getData(); }
    NYX_FORCEINLINE RigidbodyData& accessRigidbodyData() { return Rb.accessData(); }

private:
    RigidbodySystem Rb;
};

} // namespace nyx