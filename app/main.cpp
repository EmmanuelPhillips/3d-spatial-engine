#include <raylib.h>
#include <raymath.h>

#include "grid.hpp"
#include "particle.hpp"

int main() {

  constexpr float window_width{1280};
  constexpr float window_height{720};

  constexpr float grid_width{50.0f};
  constexpr float grid_height{50.0f};
  constexpr float grid_interval{5.0f};

  constexpr Grid XY{Vector3{0.0f, 0.0f, 0.0f},
                    Vector3{1.0f, 0.0f, 0.0f},
                    Vector3{0.0f, 1.0f, 0.0f},
                    grid_width,
                    grid_height,
                    grid_interval,
                    RED};

  constexpr Grid XZ{Vector3{0.0f, 0.0f, 0.0f},
                    Vector3{1.0f, 0.0f, 0.0f},
                    Vector3{0.0f, 0.0f, 1.0f},
                    grid_width,
                    grid_height,
                    grid_interval,
                    PURPLE};

  constexpr Grid YZ{Vector3{0.0f, 0.0f, 0.0f},
                    Vector3{0.0f, 1.0f, 0.0f},
                    Vector3{0.0f, 0.0f, 1.0f},
                    grid_width,
                    grid_height,
                    grid_interval,
                    YELLOW};

  Particle p{RED, 10.0f, Vector3{0.0f, 0.0f, 0.0f}, Vector3{0.0f, 0.0f, 0.0f}};

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

    BeginMode3D(camera);

    XY.DrawGridPlane();
    XZ.DrawGridPlane();
    YZ.DrawGridPlane();

    DrawSphere(p.get_position(), p.get_radius(), p.get_colour());
    DrawSphereWires(p.get_position(), p.get_radius(), 16, 16, BLACK);

    EndMode3D();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
