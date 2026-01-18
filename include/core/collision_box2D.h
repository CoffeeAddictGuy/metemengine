#pragma once
#include <raylib.h>


typedef struct CollisionBox2D {
  char *name;
  Vector2 pos;
  Vector2 size;
} CollisionBox2D;

void collision_draw_debug(CollisionBox2D *cb);

bool aabb_collision(CollisionBox2D *a, CollisionBox2D *b);
