#pragma once

#include <array>

#include "math/vec3.h"

namespace nyx {

using namespace math;

constexpr size_t MAX_RB_COUNT = 1e5; 

class Rigidbody
{
public:
  void update(float timestep);
private:
  std::array<vec3, MAX_RB_COUNT> Positions;
  std::array<vec3, MAX_RB_COUNT> Rotations;
};


}
