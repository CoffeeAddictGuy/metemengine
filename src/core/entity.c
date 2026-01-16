#include "../../include/core/entity.h"

void entity_movement(Entity *entity) {
  entity->speed = 200.0f;
  if (entity->velocity.x != 0 && entity->velocity.y != 0) {
    entity->speed *= 0.7f;
  }
  entity->pos.x += entity->velocity.x * entity->speed * engine.delta_time;
  entity->pos.y += entity->velocity.y * entity->speed * engine.delta_time;
}