#pragma once

#include <random>

class Random {
private:
  std::mt19937 gen_;

public:
  Random();
  explicit Random(std::mt19937::result_type seed);
  float uniform(float min, float max);
};
