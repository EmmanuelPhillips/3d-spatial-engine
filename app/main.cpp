#include <iostream>

#include "particle.hpp"

int main() {
  Particle p{RED, 1.0f, Vector3{1.0f, 1.0f, 1.0f}, Vector3{1.0f, 1.0f, 1.0f}};

  std::cout << "Particle mass: " << p.get_mass() << '\n';

  return 0;
}
