#pragma once

#include <vector>

#include "math/vec3.h"

namespace nyx {

using namespace math;

constexpr size_t initialRbCount = 10'000;

struct RigidbodyData {
    std::vector<Vec3> Positions;
    std::vector<Vec3> Rotations;
    std::vector<Vec3> Velocities;
    std::vector<Vec3> Forces;
    std::vector<float> Masses;

    RigidbodyData() {
        Positions.reserve(initialRbCount);
        Rotations.reserve(initialRbCount);
        Velocities.reserve(initialRbCount);
        Forces.reserve(initialRbCount);
        Masses.reserve(initialRbCount);
    }
};

class RigidbodySystem {
public:
  void update(float timestep);

private:
  RigidbodyData Data;

};

} // namespace nyx
