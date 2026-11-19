#include <algorithm>
#include <array>
#include <chrono>
#include <cstddef>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

#include "cube.hpp"
#include "octtree.hpp"
#include "particle.hpp"
#include "physics.hpp"
#include "random.hpp"

struct BenchmarkResult {
  std::size_t collision_count;
  double elapsed_ms;
};

std::vector<Particle> generate_particles(int num_particles, Random &random) {
  std::vector<Particle> particles;
  particles.reserve(num_particles);

  for (int i{0}; i < num_particles; ++i) {
    float radius{random.uniform(3.5f, 5.0f)};

    Vector3 pos{
        random.uniform(-100.0f, 100.0f),
        random.uniform(-100.0f, 100.0f),
        random.uniform(-100.0f, 100.0f),
    };

    Vector3 vel{
        random.uniform(-10.0f, 10.0f),
        random.uniform(-10.0f, 10.0f),
        random.uniform(-10.0f, 10.0f),
    };

    particles.emplace_back(RED, radius, pos, vel);
  }

  return particles;
}

BenchmarkResult benchmark_brute_force(const std::vector<Particle> &particles) {
  auto start{std::chrono::steady_clock::now()};

  std::size_t collision_count{0};

  for (std::size_t i{0}; i < particles.size(); ++i) {
    for (std::size_t j{i + 1}; j < particles.size(); ++j) {
      auto collision{
          Physics::check_particle_collision(particles[i], particles[j])};

      if (collision) {
        ++collision_count;
      }
    }
  }

  auto end{std::chrono::steady_clock::now()};

  double elapsed_ms{
      std::chrono::duration<double, std::milli>(end - start).count()};

  return {collision_count, elapsed_ms};
}

BenchmarkResult benchmark_octtree(std::vector<Particle> &particles) {
  float max_radius{0.0f};

  for (const auto &particle : particles) {
    max_radius = std::max(max_radius, particle.get_radius());
  }

  Cube bounds{{-100.0f, -100.0f, -100.0f}, 200.0f};
  Octtree octtree{bounds, 0, 6};

  auto start{std::chrono::steady_clock::now()};

  // Build the octree.
  for (auto &particle : particles) {
    octtree.insert(&particle);
  }

  // Query the octree and check candidate pairs.
  std::size_t collision_count{0};

  for (std::size_t i{0}; i < particles.size(); ++i) {
    auto candidates{octtree.query(particles[i], max_radius)};

    Particle *current{&particles[i]};

    for (Particle *candidate : candidates) {
      // Skip self-comparisons and pairs already considered.
      if (candidate <= current) {
        continue;
      }

      auto collision{
          Physics::check_particle_collision(particles[i], *candidate)};

      if (collision) {
        ++collision_count;
      }
    }
  }

  auto end{std::chrono::steady_clock::now()};

  double elapsed_ms{
      std::chrono::duration<double, std::milli>(end - start).count()};

  return {collision_count, elapsed_ms};
}

int main() {
  constexpr std::array<int, 5> particle_counts{100, 500, 1000, 2000, 5000};

  Random random{42};

  std::ofstream file{"results/benchmark_results.csv"};

  file << "particles,brute_force_ms,octtree_ms,"
          "brute_force_collisions,octtree_collisions\n";

  for (int num_particles : particle_counts) {
    auto particles{generate_particles(num_particles, random)};

    auto brute_force{benchmark_brute_force(particles)};
    auto octtree{benchmark_octtree(particles)};

    bool results_match{brute_force.collision_count == octtree.collision_count};

    std::cout << "Particles: " << num_particles << '\n';

    std::cout << "Brute force: " << brute_force.elapsed_ms << "ms\n";

    std::cout << "Octtree: " << octtree.elapsed_ms << "ms\n";

    std::cout << "Brute force collisions: " << brute_force.collision_count
              << '\n';

    std::cout << "Octtree collisions: " << octtree.collision_count << '\n';

    std::cout << "Results match: " << (results_match ? "YES" : "NO") << '\n';

    std::cout << "-----------------------\n";

    file << num_particles << ',' << brute_force.elapsed_ms << ','
         << octtree.elapsed_ms << ',' << brute_force.collision_count << ','
         << octtree.collision_count << '\n';
  }

  return 0;
}
