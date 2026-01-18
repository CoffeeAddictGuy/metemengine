#include "../../include/core/entity.h"
#include <raylib.h>

Entity2D entity_create() {
  Entity2D entity = (Entity2D){.name = "Default Entity",
                               .pos = (Vector2){0, 0},
                               .size = (Vector2){50, 50},
                               .speed = 0.f,
                               .velocity = (Vector2){0, 0},
                               .collision_box = NULL};
  CollisionBox2D entity_collider = (CollisionBox2D){
      .name = "Default Collider", .pos = entity.pos, .size = entity.size};
  entity.collision_box = entity_collider;
  return entity;
}

void entity_draw(Entity2D *entity) {
  DrawRectangleV(entity->pos, entity->size, RED);
  if (engine.debug_draw) {
    if (!entity->is_colliding) {
      DrawRectangleLinesEx((Rectangle){entity->collision_box.pos.x,
                                       entity->collision_box.pos.y,
                                       entity->collision_box.size.x,
                                       entity->collision_box.size.y},
                           1, BLUE);
    } else {
      DrawRectangleLinesEx((Rectangle){entity->collision_box.pos.x,
                                       entity->collision_box.pos.y,
                                       entity->collision_box.size.x,
                                       entity->collision_box.size.y},
                           1, YELLOW);
    }
  }
}

void entity_movement(Entity2D *entity) {
  entity->speed = 200.0f;
  if (entity->velocity.x != 0 && entity->velocity.y != 0) {
    entity->speed *= 0.7f;
  }
  entity->pos.x += entity->velocity.x * entity->speed * engine.delta_time;
  entity->pos.y += entity->velocity.y * entity->speed * engine.delta_time;

  entity->collision_box.pos.x +=
      entity->velocity.x * entity->speed * engine.delta_time;
  entity->collision_box.pos.y +=
      entity->velocity.y * entity->speed * engine.delta_time;
}
