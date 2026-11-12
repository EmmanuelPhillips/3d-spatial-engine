#include <raylib.h>
#include <raymath.h>

#include "particle.hpp"

void DrawXYPlane(float width, float height, float interval, Color colour) {
  for (float x{-width / 2}; x <= width / 2; x += interval) {
    DrawLine3D(Vector3{x, -height / 2, 0.0f}, Vector3{x, height / 2, 0.0f},
               colour);
  }
  for (float y{-height / 2}; y <= height / 2; y += interval) {
    DrawLine3D(Vector3{-width / 2, y, 0.0f}, Vector3{width / 2, y, 0.0f},
               colour);
  }
}

void DrawXZPlane(float width, float length, float interval, Color colour) {
  for (float x{-width / 2}; x <= width / 2; x += interval) {
    DrawLine3D(Vector3{x, 0.0f, -length / 2}, Vector3{x, 0.0f, length / 2},
               colour);
  }
  for (float z{-length / 2}; z <= length / 2; z += interval) {
    DrawLine3D(Vector3{-width / 2, 0.0f, z}, Vector3{width / 2, 0.0f, z},
               colour);
  }
}
void DrawYZPlane(float height, float length, float interval, Color colour) {
  for (float y{-height / 2}; y <= height / 2; y += interval) {
    DrawLine3D(Vector3{0.0f, y, -length / 2}, Vector3{0.0f, y, length / 2},
               colour);
  }
  for (float z{-length / 2}; z <= length / 2; z += interval) {
    DrawLine3D(Vector3{0.0f, -height / 2, z}, Vector3{0.0f, height / 2, z},
               colour);
  }
}
void DrawOuterCube(const Vector3 &origin, const float width, const float height,
                   const float length, Color colour) {
  DrawCubeWires(origin, width, height, length, colour);
}

void DrawSetup(const Vector3 &origin, const float width, const float height,
               const float length, Color colour, const float interval) {
  DrawOuterCube(origin, width, height, length, colour);
  DrawXYPlane(width, height, interval, colour);
  DrawXZPlane(width, length, interval, colour);
  DrawYZPlane(height, length, interval, colour);
}

int main() {

  constexpr float window_width{1280};
  constexpr float window_height{720};

  constexpr Vector3 cube_origin{0.0f, 0.0f, 0.0f};
  constexpr float cube_width{50.0f};
  constexpr float cube_height{50.0f};
  constexpr float cube_length{50.0f};

  Particle p{RED, 10.0f, Vector3{0.0f, 0.0f, 0.0f}, Vector3{0.0f, 0.0f, 0.0f}};

  InitWindow(window_width, window_height, "3D Particle Collision Simulator");
  SetTargetFPS(60);

  Camera3D camera{.position{50.0f, 50.0f, 50.0f},
                  .target{0.0f, 0.0f, 0.0f},
                  .up{0.0f, 1.0f, 0.0f},
                  .fovy{45.0f},
                  .projection{CAMERA_PERSPECTIVE}};

  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(camera);
    DrawSetup(cube_origin, cube_width, cube_height, cube_length, BLACK, 5.0f);

    DrawSphere(p.get_position(), p.get_radius(), p.get_colour());
    DrawSphereWires(p.get_position(), p.get_radius(), 16, 16, BLACK);

    EndMode3D();

    EndDrawing();
  }

  CloseWindow();

  return 0;
}
