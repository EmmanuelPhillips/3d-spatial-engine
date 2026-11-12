#pragma once

#include <raylib.h>
#include <raymath.h>

class Particle {
private:
  Color colour_;
  float radius_;
  float mass_;
  Vector3 position_;
  Vector3 velocity_;

public:
  Particle(Color c, float r, Vector3 p, Vector3 v);

  Color get_colour() const;
  float get_radius() const;
  float get_mass() const;
  Vector3 get_position() const;
  Vector3 get_velocity() const;

  void set_position(const Vector3 &p);
  void set_velocity(const Vector3 &v);

  void update(float delta_time);
};
