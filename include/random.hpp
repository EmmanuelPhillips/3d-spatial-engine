#pragma once

#include <random>

class Random {
private:
  std::mt19937 gen_;

public:
  Random();
  float uniform(float min, float max);
};
