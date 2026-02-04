#include "camera.h"
#include <raylib.h>

void camera_init(void *self) { MCamera2D *c = (MCamera2D *)self; }
void camera_update(void *self, float dt) {
  MCamera2D *c = self;

  Vector2 target_pos = get_target_pos(c->target);

  c->camera.target.x += (target_pos.x - c->camera.target.x) * 8.0f * dt;
  c->camera.target.y += (target_pos.y - c->camera.target.y) * 8.0f * dt;

  TraceLog(LOG_DEBUG, "Target cord - %f.x/%f.y", c->camera.target.x,
           c->camera.target.y);
}
void camera_destroy(void *self) { TraceLog(LOG_DEBUG, "Camera destroy!"); }
