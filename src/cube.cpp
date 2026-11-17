#include "cube.hpp"

bool Cube::contains(const Particle &p) const {
  bool x_valid{p.get_position().x >= origin.x &&
               p.get_position().x < origin.x + length};
  bool y_valid{p.get_position().y >= origin.y &&
               p.get_position().y < origin.y + length};
  bool z_valid{p.get_position().z >= origin.z &&
               p.get_position().z < origin.z + length};

  return x_valid && y_valid && z_valid;
}
