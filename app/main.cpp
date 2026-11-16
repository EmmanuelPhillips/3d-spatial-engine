#include <raylib.h>
#include <raymath.h>

#include "grid.hpp"
#include "particle.hpp"
#include "physics.hpp"
#include "random.hpp"

int main() {

  // Window parameters
  constexpr float window_width{1280};
  constexpr float window_height{720};

  // Grid parameters
  constexpr float grid_width{50.0f};
  constexpr float grid_height{50.0f};
  constexpr float grid_length{50.0f}; // just for boundary collision
  constexpr float grid_interval{5.0f};

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
  constexpr float min_radius{1.0f};
  constexpr float max_radius{5.0f};
  constexpr float min_position{-grid_width / 2};
  constexpr float max_position{grid_width / 2};
  constexpr float min_velocity{-1.0f};
  constexpr float max_velocity{1.0f};
  constexpr int num_particles{50};
  constexpr float time_interval{1.0f};

  // Generate random
  Random random;

  // Initialise particles
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

  InitWindow(window_width, window_height, "3D Particle Collision Simulator");
  SetTargetFPS(60);

  Camera3D camera{.position{50.0f, 50.0f, 50.0f},
                  .target{0.0f, 0.0f, 0.0f},
                  .up{0.0f, 1.0f, 0.0f},
                  .fovy = 45.0f,
                  .projection = CAMERA_PERSPECTIVE};

  while (!WindowShouldClose()) {
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
    for (auto &particle : particles) {
      particle.update(time_interval);
      particle.resolve_boundary_collision(grid_width / 2, grid_height / 2,
                                          grid_length / 2);
    }
    for (int i{0}; i < num_particles; ++i) {
      for (int j{i + 1}; j < num_particles; ++j) {
        auto collision_occured{
            Physics::check_particle_collision(particles[i], particles[j])};
        if (collision_occured) {
          Physics::resolve_particle_overlap(particles[i], particles[j],
                                            *collision_occured);
          Physics::resolve_particle_velocity(particles[i], particles[j],
                                             *collision_occured);
        }
      }
    }

    EndMode3D();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
