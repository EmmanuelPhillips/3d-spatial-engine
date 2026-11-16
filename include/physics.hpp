#pragma once

#include <optional>

#include "particle.hpp"

struct CollisionInfo {
  Vector3 normal;
  float overlap;
};

namespace Physics {
std::optional<CollisionInfo> check_particle_collision(const Particle &p1,
                                                      const Particle &p2);
void resolve_particle_overlap(Particle &p1, Particle &p2,
                              const CollisionInfo &c);
void resolve_particle_velocity(Particle &p1, Particle &p2,
                               const CollisionInfo &c);
} // namespace Physics
