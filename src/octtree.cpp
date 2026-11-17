#include "octtree.hpp"

Octtree::Octtree(Cube bounds, int current_depth, int max_depth)
    : bounds_{bounds}, divided_{false}, current_depth_{current_depth},
      max_depth_{max_depth} {}

void Octtree::subdivide() {
  const float child_length{bounds_.length / 2.0f};
  for (int i{0}; i < 8; ++i) {
    bool upper_x{(i & 1) != 0.0f};
    bool upper_y{(i & 2) != 0.0f};
    bool upper_z{(i & 4) != 0.0f};
    float x{upper_x ? child_length : 0.0f};
    float y{upper_y ? child_length : 0.0f};
    float z{upper_z ? child_length : 0.0f};
    Vector3 child_origin{bounds_.origin.x + x, bounds_.origin.y + y,
                         bounds_.origin.z};
    children_[i] = std::make_unique<Octtree>(Cube{child_origin, child_length},
                                             ++current_depth_, max_depth_);
  }
}

void Octtree::insert(Particle *p) {}

std::vector<Particle *> Octtree::query(const Particle &p) {
  return std::vector<Particle *>{};
}

void Octtree::clear() {}
