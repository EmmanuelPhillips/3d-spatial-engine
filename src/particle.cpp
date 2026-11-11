#include <numbers>

#include "particle.hpp"

Particle::Particle(Color c, float r, Vector3 p, Vector3 v)
    : colour_{c}, radius_{r}, mass_{(4.0f / 3.0f) * std::numbers::pi_v<float> *
                                    (radius_ * radius_ * radius_)},
      position_{p}, velocity_{v} {}

float Particle::get_radius() const { return radius_; }
float Particle::get_mass() const { return mass_; }
Vector3 Particle::get_position() const { return position_; }
Vector3 Particle::get_velocity() const { return velocity_; }

void Particle::set_position(const Vector3 &p) { position_ = p; }
void Particle::set_velocity(const Vector3 &v) { velocity_ = v; }
