#include "../../include/core/collision_box2D.h"
#include <raylib.h>

void collision_draw_debug(CollisionBox2D *cb) {
  DrawRectangleLinesEx((Rectangle){.x = cb->pos.x,
                                   .y = cb->pos.y,
                                   .height = cb->size.x,
                                   .width = cb->size.y},
                       2.f, BLUE);
}

bool aabb_collision(CollisionBox2D *a, CollisionBox2D *b) {
  if ((a->pos.x >= b->pos.x && a->pos.x <= b->pos.x + b->size.x &&
       a->pos.y >= b->pos.y && a->pos.y <= b->pos.y + b->size.y) || // top left
      (a->pos.x + a->size.x >= b->pos.x &&
       a->pos.x + a->size.x <= b->pos.x + b->size.x && a->pos.y >= b->pos.y &&
       a->pos.y <= b->pos.y + b->size.y) || // top right
      (a->pos.x >= b->pos.x && a->pos.x <= b->pos.x + b->size.x &&
       a->pos.y + a->size.y >= b->pos.y &&
       a->pos.y + a->size.y <= b->pos.y + b->size.y) || // bottom left
      (a->pos.x + a->size.x >= b->pos.x &&
       a->pos.x + a->size.x <= b->pos.x + b->size.x &&
       a->pos.y + a->size.y >= b->pos.y &&
       a->pos.y + a->size.y <= b->pos.y + b->size.y)) { // bottom right
    return true;
  }
  return false;
}
