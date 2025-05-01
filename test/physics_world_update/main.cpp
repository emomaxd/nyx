#include <iostream>

#include "nyx/core/base.h"
#include "nyx/physics/scene/physics_world.h"

using namespace nyx;

int main() {
    nyx::RigidbodySystem system;

    // Define initial conditions
    nyx::Vec3 initialPos(0.0f, 10.0f, 0.0f);
    nyx::Vec3 initialVel(0.0f, 0.0f, 0.0f);
    real_t mass = 1.0f;

    // Inertia tensor for a sphere with radius 1 (I = (2/5) * m * r^2)
    real_t i = (2.0f / 5.0f) * mass * 1.0f;
    nyx::Mat3 inertia(i, 0.0f, 0.0f,
                      0.0f, i, 0.0f,
                      0.0f, 0.0f, i);

    // Add rigidbody
    size_t id = system.addRigidbody(initialPos, initialVel, mass, inertia);

    // Simulation parameters
    real_t dt = 0.016f; // ~60 FPS
    int steps = 60;

    // Print initial position
    std::cout << "Initial position: (" << initialPos.X << ", " << initialPos.Y << ", " << initialPos.Z << ")\n";

    // Simulation loop
    for (int step = 0; step < steps; ++step) {
        system.update(dt);
        const auto& positions = system.getData().getPositions();
        const nyx::Vec3& pos = positions[id];
        std::cout << "Step " << step + 1 << ": (" << pos.X << ", " << pos.Y << ", " << pos.Z << ")\n";
    }

    return 0;
}
