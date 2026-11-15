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

void Particle::draw() { DrawSphere(position_, radius_, colour_); }

void Particle::resolve_boundary_collision(const float xbound,
                                          const float ybound,
                                          const float zbound) {
  if (position_.x + radius_ >= xbound && velocity_.x > 0.0f) {
    position_.x = xbound - radius_;
    velocity_.x *= -1;
  }
  if (position_.x - radius_ <= -xbound && velocity_.x < 0.0f) {
    position_.x = -xbound + radius_;
    velocity_.x *= -1;
  }
  if (position_.y + radius_ >= ybound && velocity_.y > 0.0f) {
    position_.y = ybound - radius_;
    velocity_.y *= -1;
  }
  if (position_.y - radius_ <= -ybound && velocity_.y < 0.0f) {
    position_.y = -ybound + radius_;
    velocity_.y *= -1;
  }
  if (position_.z + radius_ >= zbound && velocity_.z > 0.0f) {
    position_.z = zbound - radius_;
    velocity_.z *= -1;
  }
  if (position_.z - radius_ <= -zbound && velocity_.z < 0.0f) {
    position_.z = -zbound + radius_;
    velocity_.z *= -1;
  }
}
