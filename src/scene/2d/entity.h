#pragma once
#include "../../core/engine.h"
#include "../../core/engine_types.h"
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
  
  void *self;
  OnInitFn on_init;
  OnUpdateFn on_update;
  OnDestroyFn on_destroy;
} Entity2D;

typedef struct Character2D {
  char name[32];
  Vector2 pos;
  Vector2 size;
  Vector2 velocity;
  float speed;

  OnInitFn on_init;
  OnUpdateFn on_update;
  OnDestroyFn on_destroy;
} Character2D;


Entity2D entity_create(  
  void *self,
  OnInitFn on_init,
  OnUpdateFn on_update,
  OnDestroyFn on_destroy
);

Character2D character2d_create(  
  OnInitFn on_init,
  OnUpdateFn on_update,
  OnDestroyFn on_destroy
);

Entity2D entity_create_Pro(Vector2 size, Vector2 pos, Vector2 atlas_cord);
void entity_movement(Character2D *character);
