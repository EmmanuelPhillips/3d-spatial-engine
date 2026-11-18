#pragma once

#include <raylib.h>
#include <raymath.h>

#include "particle.hpp"

struct Cube {
  Vector3 origin;
  float length;

  bool contains(const Particle &p) const;
  bool intersects(const Vector3 &position, float search_radius) const;
};
