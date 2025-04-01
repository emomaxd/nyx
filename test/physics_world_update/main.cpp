#include <iostream>

#include "core/base.h"
#include "physics/physics_world.h"

using namespace nyx;

int main() {
    nyx::PhysicsWorld world;

    // Yerçekimi etkisiyle düşen bir cisim ekleyelim
    nyx::Vec3 initialPos{0.0f, 10.0f, 0.0f};  // 10 birim yukarıda
    nyx::Vec3 initialVel{0.0f, 0.0f, 0.0f};   // Başlangıç hızı sıfır
    real_t mass = 1.0f;
    size_t id = world.addRigidbody(initialPos, initialVel, mass);

    // Simülasyon parametreleri
    real_t dt = 0.016f;  // 60 FPS için zaman adımı
    int steps = 60;      // 1 saniye simülasyon

    std::cout << "Initial position: (" << initialPos.X << ", " << initialPos.Y << ", " << initialPos.Z << ")\n";

    // Yerçekimi kuvvetini manuel olarak ekleyelim (örneğin: -9.81 m/s^2 y yönünde)
    auto& forces = world.accessRigidbodyData().accessForces();
    forces[id] = nyx::Vec3{0.0f, -9.81f * mass, 0.0f};

    // Simülasyon döngüsü
    for (int step = 0; step < steps; ++step) {
        world.update(dt);
        const auto& positions = world.getRigidbodyData().getPositions();
        const nyx::Vec3& pos = positions[id];
        std::cout << "Step " << step + 1 << ": (" << pos.X << ", " << pos.Y << ", " << pos.Z << ")\n";
    }

    return 0;
}