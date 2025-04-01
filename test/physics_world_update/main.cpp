#include <iostream>

#include "core/base.h"
#include "physics/physics_world.h"

using namespace nyx;

int main() {
    nyx::PhysicsWorld world;

    nyx::Vec3 initialPos{0.0f, 10.0f, 0.0f};
    nyx::Vec3 initialVel{0.0f, 0.0f, 0.0f};
    real_t mass = 1.0f;
    size_t id = world.addRigidbody(initialPos, initialVel, mass);

    real_t dt = 0.016f;
    int steps = 60;

    std::cout << "Initial position: (" << initialPos.X << ", " << initialPos.Y << ", " << initialPos.Z << ")\n";

    auto& forces = world.accessRigidbodyData().accessForces();
    forces[id] = nyx::Vec3{0.0f, -9.81f * mass, 0.0f};

    for (int step = 0; step < steps; ++step) {
        world.update(dt);
        const auto& positions = world.getRigidbodyData().getPositions();
        const nyx::Vec3& pos = positions[id];
        std::cout << "Step " << step + 1 << ": (" << pos.X << ", " << pos.Y << ", " << pos.Z << ")\n";
    }

    return 0;
}