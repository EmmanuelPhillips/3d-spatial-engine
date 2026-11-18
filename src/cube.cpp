#include <algorithm>

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

bool Cube::intersects(const Vector3 &position, float search_radius) const {
  float closest_x{std::max(origin.x, std::min(position.x, origin.x + length))};
  float closest_y{std::max(origin.y, std::min(position.y, origin.y + length))};
  float closest_z{std::max(origin.z, std::min(position.z, origin.z + length))};

  float x_squared{(position.x - closest_x) * (position.x - closest_x)};
  float y_squared{(position.y - closest_y) * (position.y - closest_y)};
  float z_squared{(position.z - closest_z) * (position.z - closest_z)};

  float squared_distance{x_squared + y_squared + z_squared};
  float squared_radius{search_radius * search_radius};
  return squared_distance <= squared_radius;
}
