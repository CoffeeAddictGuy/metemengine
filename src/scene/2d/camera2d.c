#include "camera2d.h"
#include "entity.h"
#include <raylib.h>

MCamera2D camera_create(OnInitFn on_init, OnUpdateFn on_update,
                        OnDestroyFn on_destroy) {
  MCamera2D camera =
      (MCamera2D){"Default camera", (Camera2D){0}, .on_init = on_init,
                  .on_update = on_update, .on_destroy = on_destroy};
  camera.camera.zoom = 1.0f;
  camera.camera.offset =
      (Vector2){engine.window_size.x / 2, engine.window_size.y / 2};
  return camera;
}

Vector2 get_target_pos(void *target) {
  Character2D *c = target;
  return c->pos;
}
