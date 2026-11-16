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
  const float w1{1.0f / p1.get_mass()};
  const float w2{1.0f / p2.get_mass()};
  const float wtotal{w1 + w2};
  Vector3 p1_push{Vector3Scale(c.normal, c.overlap * w1 / wtotal)};
  Vector3 p2_push{Vector3Scale(c.normal, c.overlap * w2 / wtotal)};
  p1.set_position(Vector3Add(p1.get_position(), p1_push));
  p2.set_position(Vector3Subtract(p2.get_position(), p2_push));
}

void resolve_particle_velocity(Particle &p1, Particle &p2,
                               const CollisionInfo &c) {
  const Vector3 relative_velocity{p1.get_velocity() - p2.get_velocity()};
  const float approach_speed{Vector3DotProduct(relative_velocity, c.normal)};
  const float restitution{1.0f};
  const float scalar{-(1.0f + restitution) * approach_speed /
                     ((1.0f / p1.get_mass()) + 1.0f / p2.get_mass())};
  const Vector3 impulse_vector{Vector3Scale(c.normal, scalar)};
  const Vector3 p1_impulse_vector{
      Vector3Scale(impulse_vector, 1.0f / p1.get_mass())};
  const Vector3 p2_impulse_vector{
      Vector3Scale(impulse_vector, 1.0f / p2.get_mass())};
  p1.set_velocity(Vector3Add(p1.get_velocity(), p1_impulse_vector));
  p2.set_velocity(Vector3Subtract(p2.get_velocity(), p2_impulse_vector));
}

void check_and_resolve_collision() {}
} // namespace Physics
