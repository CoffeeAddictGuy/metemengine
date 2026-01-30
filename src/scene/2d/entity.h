#pragma once
#include "../../core/engine.h"
#include "physics/collision_box2d.h"
#include <raylib.h>


typedef struct Entity2D {
  char name[32];
  Vector2 pos;
  Vector2 size;
  Vector2 velocity;
  Vector2 atlas_cord;
  CollisionBox2D collision_box;
  bool is_colliding;

  void (*entity_on_init) (void);
  void (*entity_on_update) (void); 
} Entity2D;


Entity2D entity_create();
Entity2D entity_create_Pro(Vector2 size, Vector2 pos, Vector2 atlas_cord);
void entity_movement(Entity2D *entity);
