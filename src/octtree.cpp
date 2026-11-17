#include "octtree.hpp"

bool Cube::contains(const Particle &p) const {
  bool x_valid{p.get_position().x >= origin.x &&
               p.get_position().x < origin.x + length};
  bool y_valid{p.get_position().y >= origin.y &&
               p.get_position().y < origin.y + length};
  bool z_valid{p.get_position().z >= origin.z &&
               p.get_position().z < origin.z + length};

  return x_valid && y_valid && z_valid;
}

Octtree::Octtree(Cube bounds, int current_depth, int max_depth)
    : bounds_{bounds}, divided_{false}, current_depth_{current_depth},
      max_depth_{max_depth} {}

void Octtree::subdivide() {}

void Octtree::insert(Particle *p) {}

std::vector<Particle *> Octtree::query(const Particle &p) {
  return std::vector<Particle *>{};
}

void Octtree::clear() {}
