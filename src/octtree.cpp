#include "octtree.hpp"

Octtree::Octtree(Cube bounds, int current_depth, int max_depth)
    : bounds_{bounds}, divided_{false}, current_depth_{current_depth},
      max_depth_{max_depth} {}

void Octtree::subdivide() {
  if (divided_ || current_depth_ >= max_depth_) {
    return;
  }

  const float child_length{bounds_.length / 2.0f};

  for (int i{0}; i < 8; ++i) {
    bool upper_x{(i & 1) != 0};
    bool upper_y{(i & 2) != 0};
    bool upper_z{(i & 4) != 0};

    float x{upper_x ? child_length : 0.0f};
    float y{upper_y ? child_length : 0.0f};
    float z{upper_z ? child_length : 0.0f};

    Vector3 child_origin{bounds_.origin.x + x, bounds_.origin.y + y,
                         bounds_.origin.z + z};

    children_[i] = std::make_unique<Octtree>(Cube{child_origin, child_length},
                                             current_depth_ + 1, max_depth_);
  }

  divided_ = true;

  for (auto *p : particles_) {
    for (auto &child : children_) {
      if (child->bounds_.contains(*p)) {
        child->insert(p);
        break;
      }
    }
  }

  particles_.clear();
}

void Octtree::insert(Particle *p) {
  if (!bounds_.contains(*p)) {
    return;
  }

  if (divided_) {
    for (auto &child : children_) {
      if (child->bounds_.contains(*p)) {
        child->insert(p);
        return;
      }
    }

    particles_.push_back(p);
    return;
  }

  if (particles_.size() < MAX_PARTICLES || current_depth_ >= max_depth_) {
    particles_.push_back(p);
    return;
  }

  subdivide();

  if (divided_) {
    for (auto &child : children_) {
      if (child->bounds_.contains(*p)) {
        child->insert(p);
        return;
      }
    }
  }

  particles_.push_back(p);
}

std::vector<Particle *> Octtree::query(const Particle &p, float max_radius) {
  std::vector<Particle *> candidates;

  float search_radius{p.get_radius() + max_radius};

  if (!bounds_.intersects(p.get_position(), search_radius)) {
    return candidates;
  }

  for (const auto &particle : particles_) {
    candidates.emplace_back(particle);
  }

  if (divided_) {
    for (auto &child : children_) {
      auto child_candidates{child->query(p, max_radius)};
      for (auto *candidate : child_candidates) {
        candidates.emplace_back(candidate);
      }
    }
  }

  return candidates;
}

void Octtree::clear() {
  particles_.clear();
  children_ = {};
  divided_ = false;
}
