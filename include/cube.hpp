#pragma once

#include <raylib.h>
#include <raymath.h>

#include "particle.hpp"

struct Cube {
  Vector3 origin;
  float length;

  bool contains(const Particle &p) const;
};
