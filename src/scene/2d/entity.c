#include "entity.h"
#include <raylib.h>

Entity2D entity_create(void *self, OnInitFn on_init, OnUpdateFn on_update,
                       OnDestroyFn on_destroy) {
  Entity2D entity = (Entity2D){.name = "Default Entity",
                               .pos = (Vector2){0, 0},
                               .size = (Vector2){50, 50},
                               .atlas_cord = (Vector2){0, 0},
                               .velocity = (Vector2){0, 0},
                               .collision_box = NULL,
                               .self = self,
                               .on_init = on_init,
                               .on_update = on_update,
                               .on_destroy = on_destroy};

  return entity;
}

Character2D character2d_create(OnInitFn on_init, OnUpdateFn on_update,
                               OnDestroyFn on_destroy) {
  Character2D character = (Character2D){.name = "Default Character",
                                        .pos = (Vector2){0, 0},
                                        .size = (Vector2){50, 50},
                                        .speed = 100.f,
                                        .velocity = (Vector2){0, 0},
                                        .on_init = on_init,
                                        .on_update = on_update,
                                        .on_destroy = on_destroy};
  return character;
}

Entity2D entity_create_Pro(Vector2 size, Vector2 pos, Vector2 atlas_cord) {
  Entity2D entity = (Entity2D){.name = "Default Entity",
                               .pos = pos,
                               .size = size,
                               .atlas_cord = atlas_cord,
                               .velocity = (Vector2){0, 0},
                               .collision_box = NULL};
  return entity;
}

void entity_movement(Character2D *character) {
  character->pos.x += character->velocity.x * engine.delta_time;
  // character->collision_box.pos.x += character->velocity.x *
  // engine.delta_time;

  character->pos.y += character->velocity.y * engine.delta_time;
  // character->collision_box.pos.y += character->velocity.y *
  // engine.delta_time;

  if (character->velocity.x != 0 && character->velocity.y != 0) {
    character->velocity.x *= 0.7f;
    character->velocity.y *= 0.7f;
  }
}
