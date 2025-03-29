#include "rigidbody/rigidbody_system.h"

int main() {
  constexpr float timestep = 1 / 60.0f;

  nyx::RigidbodySystem rb;

  rb.update(timestep);

  return 0;
}
