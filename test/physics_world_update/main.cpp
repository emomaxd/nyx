#include <iomanip>
#include <iostream>

#include "physics/physics_world.h"

namespace nyx {
static std::ostream& operator<<(std::ostream& os, const Vec3& v) {
    os << "(" << std::fixed << std::setprecision(2) << v.X << ", " << v.Y << ", " << v.Z << ")";
    return os;
}
} // namespace nyx

int main() {
    constexpr float timestep = 1.0f / 60.0f;
    constexpr int steps = 5;

    nyx::PhysicsWorld world;

    size_t rbId = world.addRigidbody({0.0f, 10.0f, 0.0f}, {1.0f, 0.0f, 0.0f}, 2.0f);
    std::cout << "Rigidbody Test:\n";
    std::cout << "Initial Pos: " << world.getRigidbodyData().Positions[rbId] 
              << ", Vel: " << world.getRigidbodyData().Velocities[rbId] << "\n";

    std::cout << "\nRunning simulation for " << steps << " steps...\n";
    for (int i = 0; i < steps; ++i) {
        world.update(timestep);
        std::cout << "Step " << i + 1 << ": Pos: " << world.getRigidbodyData().Positions[rbId] 
                  << ", Vel: " << world.getRigidbodyData().Velocities[rbId] << "\n";
    }

    std::cout << "\nDeactivating Rigidbody and running 1 more step...\n";
    world.accessRigidbodyData().Active[rbId] = 0;
    world.update(timestep);
    std::cout << "  Rigidbody teil Pos (should not change): " << world.getRigidbodyData().Positions[rbId] 
              << ", Vel: " << world.getRigidbodyData().Velocities[rbId] << "\n";

    return 0;
}