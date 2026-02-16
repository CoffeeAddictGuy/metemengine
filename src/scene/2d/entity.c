#include "entity.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdlib.h>

Entity2D entity_create(void *self, OnInitFn on_init, OnUpdateFn on_update,
                       OnDestroyFn on_destroy) {
  Entity2D entity = (Entity2D){.name = "Default Entity",
                               .pos = (Vector2){0, 0},
                               .self = self,
                               .on_init = on_init,
                               .on_update = on_update,
                               .on_destroy = on_destroy};

  return entity;
}

Entity2D entity_create_pro(Vector2 size, Vector2 pos, Vector2 atlas_cord) {
  Entity2D entity = (Entity2D){.name = "Default Entity", .pos = pos};
  return entity;
}

Character2D character2d_create(void *self, OnInitFn on_init,
                               OnUpdateFn on_update, OnDestroyFn on_destroy) {
  Entity2D e_base = entity_create(self, on_init, on_update, on_destroy);
  Character2D character = (Character2D){.base = e_base,
                                        .size = (Vector2){50.f, 50.f},
                                        .atlas_cord = (Vector2){0.f, 0.f},
                                        .velocity = (Vector2){0.f, 0.f},
                                        .is_colliding = false,
                                        .collision_box = NULL};
  return character;
}

Character2D character2d_create_pro(void *self, OnInitFn on_init,
                                   OnUpdateFn on_update, OnDestroyFn on_destroy,
                                   Vector2 size, Vector2 pos,
                                   Vector2 atlas_cord) {
  Entity2D e_base = entity_create(self, on_init, on_update, on_destroy);
  e_base.pos = pos;
  Character2D character = (Character2D){.base = e_base,
                                        .size = size,
                                        .atlas_cord = atlas_cord,
                                        .velocity = (Vector2){0.f, 0.f},
                                        .is_colliding = false,
                                        .collision_box = NULL};
  return character;
}

StaticBody2D static_body_create(void *self, OnInitFn on_init,
                                OnUpdateFn on_update, OnDestroyFn on_destroy) {
  Entity2D e_base = entity_create(self, on_init, on_update, on_destroy);
  StaticBody2D static_body = (StaticBody2D){.base = e_base,
                                            .size = (Vector2){50.f, 50.f},
                                            .atlas_cord = (Vector2){0.f, 0.f},
                                            .is_colliding = false,
                                            .collision_box = NULL};
  return static_body;
}

StaticBody2D static_body_create_pro(void *self, OnInitFn on_init,
                                    OnUpdateFn on_update,
                                    OnDestroyFn on_destroy, Vector2 size,
                                    Vector2 pos, Vector2 atlas_cord) {
  Entity2D e_base = entity_create(self, on_init, on_update, on_destroy);
  e_base.pos = pos;
  StaticBody2D static_body = (StaticBody2D){.base = e_base,
                                            .size = size,
                                            .atlas_cord = atlas_cord,
                                            .is_colliding = false,
                                            .collision_box = NULL};
  return static_body;
}

void entity_movement(Character2D *character) {
  character->base.pos.x += character->velocity.x * engine.delta_time;

  character->base.pos.y += character->velocity.y * engine.delta_time;

  if (character->velocity.x != 0 && character->velocity.y != 0) {
    character->velocity.x *= 0.7f;
    character->velocity.y *= 0.7f;
  }
}
