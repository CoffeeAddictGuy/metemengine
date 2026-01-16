#pragma once
#include <raylib.h>

#include "engine.h"

typedef struct {
  Vector2 pos;
  Vector2 velocity;
  float speed;
  Rectangle collision_box;
} Entity;

void entity_movement(Entity *entity);