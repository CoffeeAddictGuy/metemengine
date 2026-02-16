#pragma once
#include "../../core/engine.h"
#include "../../core/engine_types.h"
#include "physics/collision_box2d.h"
#include <raylib.h>

typedef struct Entity2D {
  char name[32];
  Vector2 pos;

  void *self;
  OnInitFn on_init;
  OnUpdateFn on_update;
  OnDestroyFn on_destroy;
} Entity2D;

Entity2D entity_create(void *self, OnInitFn on_init, OnUpdateFn on_update,
                       OnDestroyFn on_destroy);

Entity2D entity_create_pro(Vector2 size, Vector2 pos, Vector2 atlas_cord);

typedef struct StaticBody2D {
  Entity2D base;

  Vector2 size;
  Vector2 atlas_cord;

  bool is_colliding;
  CollisionBox2D collision_box;
} StaticBody2D;

StaticBody2D static_body_create(void *self, OnInitFn on_init,
                                OnUpdateFn on_update, OnDestroyFn on_destroy);
StaticBody2D static_body_create_pro(void *self, OnInitFn on_init,
                                    OnUpdateFn on_update,
                                    OnDestroyFn on_destroy, Vector2 size,
                                    Vector2 pos, Vector2 atlas_cord);

typedef struct Character2D {
  Entity2D base;

  Vector2 size;
  Vector2 atlas_cord;
  Vector2 velocity;

  bool is_colliding;
  CollisionBox2D collision_box;

} Character2D;

Character2D character2d_create(void *self, OnInitFn on_init,
                               OnUpdateFn on_update, OnDestroyFn on_destroy);
Character2D character2d_create_pro(void *self, OnInitFn on_init,
                                   OnUpdateFn on_update, OnDestroyFn on_destroy,
                                   Vector2 size, Vector2 pos,
                                   Vector2 atlas_cord);

void entity_movement(Character2D *character);
