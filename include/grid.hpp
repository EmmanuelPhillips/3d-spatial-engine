#pragma once

#include <raylib.h>
#include <raymath.h>

struct Grid {
  Vector3 origin;
  Vector3 u_axis;
  Vector3 v_axis;
  float width;
  float height;
  float interval;
  Color colour;

  void DrawGridPlane() const;
};
