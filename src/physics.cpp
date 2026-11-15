#include "physics.hpp"

namespace Physics {
bool check_particle_collision(const Particle &p1, const Particle &p2) {
  const float x_squared{(p2.get_position().x - p1.get_position().x) *
                        (p2.get_position().x - p1.get_position().x)};
  const float y_squared{(p2.get_position().y - p1.get_position().y) *
                        (p2.get_position().y - p1.get_position().y)};
  const float z_squared{(p2.get_position().z - p1.get_position().z) *
                        (p2.get_position().z - p1.get_position().z)};
  const float distance_squared{x_squared + y_squared + z_squared};

  const float radii_sum{p1.get_radius() + p2.get_radius()};

  return distance_squared <= radii_sum;
}

void resolve_particle_overlap(Particle &p1, Particle &p2) {}

void resolve_particle_velocity(Particle &p1, Particle &p2) {}
} // namespace Physics
