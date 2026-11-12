#include "grid.hpp"

void Grid::DrawGridPlane() const {
  Vector3 norm_u{Vector3Normalize(u_axis)};
  Vector3 norm_v{Vector3Normalize(v_axis)};

  for (float u{-width / 2}; u <= width / 2; u += interval) {
    Vector3 u_offset{Vector3Scale(norm_u, u)};
    Vector3 v_offset{Vector3Scale(norm_v, height / 2)};
    Vector3 u_start{Vector3Subtract(Vector3Add(origin, u_offset), v_offset)};
    Vector3 u_end{Vector3Add(Vector3Add(origin, u_offset), v_offset)};

    DrawLine3D(u_start, u_end, colour);
  }
  for (float v{-height / 2}; v <= height / 2; v += interval) {
    Vector3 v_offset{Vector3Scale(norm_v, v)};
    Vector3 u_offset{Vector3Scale(norm_u, width / 2)};
    Vector3 v_start{Vector3Subtract(Vector3Add(origin, v_offset), u_offset)};
    Vector3 v_end{Vector3Add(Vector3Add(origin, v_offset), u_offset)};

    DrawLine3D(v_start, v_end, colour);
  }
}
