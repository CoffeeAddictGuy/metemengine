#include "camera2d.h"
#include <raylib.h>

MCamera2D camera_create() {
  MCamera2D camera = (MCamera2D){"Default camera", (Camera2D){0}};
  camera.camera.zoom = 1.0f;
  return camera;
}
