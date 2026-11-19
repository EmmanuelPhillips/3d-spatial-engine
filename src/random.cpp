#include "random.hpp"

Random::Random() : gen_{std::random_device{}()} {};

Random::Random(std::mt19937::result_type seed) : gen_{seed} {}

float Random::uniform(float min, float max) {
  std::uniform_real_distribution<float> dist(min, max);
  return dist(gen_);
}
