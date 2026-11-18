#include <raylib.h>
#include <raymath.h>

#include <algorithm>
#include <cstddef>
#include <utility>
#include <vector>

#include "grid.hpp"
#include "octtree.hpp"
#include "particle.hpp"
#include "physics.hpp"
#include "random.hpp"

int main() {

  // Window parameters
  constexpr float window_width{1280};
  constexpr float window_height{720};

  // Grid parameters
  constexpr float grid_width{200.0f};
  constexpr float grid_height{200.0f};
  constexpr float grid_length{200.0f};
  constexpr float grid_interval{20.0f};

  constexpr Grid XY{Vector3{0.0f, 0.0f, -grid_length / 2},
                    Vector3{1.0f, 0.0f, 0.0f},
                    Vector3{0.0f, 1.0f, 0.0f},
                    grid_width,
                    grid_height,
                    grid_interval,
                    RED};

  constexpr Grid XZ{Vector3{0.0f, -grid_height / 2, 0.0f},
                    Vector3{1.0f, 0.0f, 0.0f},
                    Vector3{0.0f, 0.0f, 1.0f},
                    grid_width,
                    grid_height,
                    grid_interval,
                    PURPLE};

  constexpr Grid YZ{Vector3{-grid_width / 2, 0.0f, 0.0f},
                    Vector3{0.0f, 1.0f, 0.0f},
                    Vector3{0.0f, 0.0f, 1.0f},
                    grid_width,
                    grid_height,
                    grid_interval,
                    BLACK};

  // Particle parameters
  constexpr Color colour{RED};
  constexpr float min_radius{3.5f};
  constexpr float max_radius{5.0f};
  constexpr float min_position{-grid_width / 2};
  constexpr float max_position{grid_width / 2};
  constexpr float min_velocity{-10.0f};
  constexpr float max_velocity{10.0f};
  constexpr int num_particles{100};

  // Generate random
  Random random;

  std::vector<Particle> particles;
  particles.reserve(num_particles);

  for (int i{0}; i < num_particles; ++i) {
    float r{random.uniform(min_radius, max_radius)};

    Vector3 p{random.uniform(min_position, max_position),
              random.uniform(min_position, max_position),
              random.uniform(min_position, max_position)};

    Vector3 v{random.uniform(min_velocity, max_velocity),
              random.uniform(min_velocity, max_velocity),
              random.uniform(min_velocity, max_velocity)};

    particles.emplace_back(Particle{colour, r, p, v});
  }

  Cube bounds{{-grid_width / 2, -grid_height / 2, -grid_length / 2},
              grid_width};

  Octtree octtree{bounds, 0, 6};

  float max_particle_radius{0.0f};

  for (const auto &particle : particles) {
    max_particle_radius = std::max(max_particle_radius, particle.get_radius());
  }

  InitWindow(window_width, window_height, "3D Particle Collision Simulator");
  SetTargetFPS(60);

  Camera3D camera{.position{350.0f, 350.0f, 350.0f},
                  .target{0.0f, 0.0f, 0.0f},
                  .up{0.0f, 1.0f, 0.0f},
                  .fovy = 45.0f,
                  .projection = CAMERA_PERSPECTIVE};

  while (!WindowShouldClose()) {

    const float delta_time{GetFrameTime()};

    for (auto &particle : particles) {
      particle.update(delta_time);

      particle.resolve_boundary_collision(grid_width / 2, grid_height / 2,
                                          grid_length / 2);
    }

    octtree.clear();

    for (auto &particle : particles) {
      octtree.insert(&particle);
    }

    std::vector<std::pair<std::size_t, std::size_t>> candidate_pairs;

    for (std::size_t i{0}; i < particles.size(); ++i) {

      auto candidates{octtree.query(particles[i], max_particle_radius)};

      for (auto *candidate : candidates) {

        const auto candidate_index{
            static_cast<std::size_t>(candidate - particles.data())};

        if (candidate_index <= i) {
          continue;
        }

        candidate_pairs.emplace_back(i, candidate_index);
      }
    }

    for (const auto &pair : candidate_pairs) {

      Particle &p1{particles[pair.first]};
      Particle &p2{particles[pair.second]};

      auto collision_occured{Physics::check_particle_collision(p1, p2)};

      if (collision_occured) {
        Physics::resolve_particle_overlap(p1, p2, *collision_occured);
        Physics::resolve_particle_velocity(p1, p2, *collision_occured);
      }
    }

    BeginDrawing();
    ClearBackground(RAYWHITE);
    DrawFPS(0, 0);

    BeginMode3D(camera);

    XY.DrawGridPlane();
    XZ.DrawGridPlane();
    YZ.DrawGridPlane();

    DrawCubeWires(Vector3{0.0f, 0.0f, 0.0f}, grid_width, grid_height,
                  grid_length, BLACK);

    for (auto &particle : particles) {
      particle.draw();
    }

    EndMode3D();
    EndDrawing();
  }

  CloseWindow();

  return 0;
}
