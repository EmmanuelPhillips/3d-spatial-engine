#pragma once

#include "particle.hpp"

namespace Physics {
bool check_particle_collision(const Particle &p1, const Particle &p2);
void resolve_particle_overlap(Particle &p1, Particle &p2);
void resolve_particle_velocity(Particle &p1, Particle &p2);
} // namespace Physics
