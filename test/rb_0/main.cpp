#include "rigidbody/rigidbody.h"


int main()
{
  constexpr float TIMESTEP = 1 / 60.0f;

  nyx::Rigidbody rb;
  
  rb.update(TIMESTEP);

  return 0;
}
