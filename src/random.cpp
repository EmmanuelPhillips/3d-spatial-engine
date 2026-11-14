#include "random.hpp"

Random::Random() : gen_{std::random_device{}()} {};

float Random::uniform(float min, float max) {
  std::uniform_real_distribution<float> dist(min, max);
  return dist(gen_);
}
