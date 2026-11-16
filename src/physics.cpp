#include <cmath>

#include "physics.hpp"

#include "raymath.h"

namespace Physics {
std::optional<CollisionInfo> check_particle_collision(const Particle &p1,
                                                      const Particle &p2) {
  const float x_squared{(p2.get_position().x - p1.get_position().x) *
                        (p2.get_position().x - p1.get_position().x)};
  const float y_squared{(p2.get_position().y - p1.get_position().y) *
                        (p2.get_position().y - p1.get_position().y)};
  const float z_squared{(p2.get_position().z - p1.get_position().z) *
                        (p2.get_position().z - p1.get_position().z)};
  const float distance_squared{x_squared + y_squared + z_squared};
  const float distance{std::sqrt(distance_squared)};

  const float radii_sum{p1.get_radius() + p2.get_radius()};

  if (distance <= radii_sum) {
    CollisionInfo c{Vector3{Vector3Normalize(
                        Vector3Subtract(p1.get_position(), p2.get_position()))},
                    radii_sum - distance};
    return c;
  } else {
    return std::nullopt;
  }
}

void resolve_particle_overlap(Particle &p1, Particle &p2,
                              const CollisionInfo &c) {
  // move particles away from each other relative to their mass.
  // w1 = 1/m1, w2 = 1/m2
  // use collisioninfo. change p1 = overlap * (w1 / w1 + w2)
  const float w1{1.0f / p1.get_mass()};
  const float w2{1.0f / p2.get_mass()};
  p1.set_position(Vector3Add(p1.get_position(), c.normal * (w1 / (w1 + w2))));
  p2.set_position(
      Vector3Subtract(p2.get_position(), c.normal * (w2 / (w1 + w2))));
}

void resolve_particle_velocity(Particle &p1, Particle &p2) {}
} // namespace Physics
