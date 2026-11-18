#pragma once

#include <raylib.h>
#include <raymath.h>

#include <array>
#include <memory>
#include <vector>

#include "cube.hpp"
#include "particle.hpp"

static constexpr std::size_t MAX_PARTICLES{8};

class Octtree {
private:
  Cube bounds_;
  std::vector<Particle *> particles_;
  std::array<std::unique_ptr<Octtree>, 8> children_;
  bool divided_;
  int current_depth_;
  int max_depth_;

public:
  Octtree(Cube bounds, int current_depth, int max_depth);
  void subdivide();
  void insert(Particle *p);
  std::vector<Particle *> query(const Particle &p, float max_radius);
  void clear();
};
