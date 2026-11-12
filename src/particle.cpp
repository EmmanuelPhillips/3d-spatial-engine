#include <numbers>

#include "particle.hpp"

#include "raymath.h"

Particle::Particle(Color c, float r, Vector3 p, Vector3 v)
    : colour_{c}, radius_{r}, mass_{(4.0f / 3.0f) * std::numbers::pi_v<float> *
                                    (radius_ * radius_ * radius_)},
      position_{p}, velocity_{v} {}

Color Particle::get_colour() const { return colour_; }
float Particle::get_radius() const { return radius_; }
float Particle::get_mass() const { return mass_; }
Vector3 Particle::get_position() const { return position_; }
Vector3 Particle::get_velocity() const { return velocity_; }

void Particle::set_position(const Vector3 &p) { position_ = p; }
void Particle::set_velocity(const Vector3 &v) { velocity_ = v; }

void Particle::update(float delta_time) {
  position_ = Vector3Add(position_, Vector3Scale(velocity_, delta_time));
}
