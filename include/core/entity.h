#pragma once
#include <raylib.h>
#include <stdlib.h>

#include "engine.h"
#include "collision_box2D.h"


typedef struct Entity2D {
  char name[32];
  Vector2 pos;
  Vector2 size;
  Vector2 velocity;
  float speed;
  CollisionBox2D collision_box;
  bool is_colliding;

  void (*entity_on_init) (void);
  void (*entity_on_update) (void); 
} Entity2D;


Entity2D entity_create();
void entity_movement(Entity2D *entity);
