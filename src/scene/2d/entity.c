#include "entity.h"
#include <raylib.h>

Entity2D entity_create() {
  Entity2D entity = (Entity2D){.name = "Default Entity",
                               .pos = (Vector2){0, 0},
                               .size = (Vector2){50, 50},
                               .atlas_cord = (Vector2){0, 0},
                               .velocity = (Vector2){0, 0},
                               .collision_box = NULL};
  // CollisionBox2D entity_collider = (CollisionBox2D){
  //     .name = "Default Collider", .pos = entity.pos, .size = entity.size};
  // entity.collision_box = entity_collider;
  // TraceLog(LOG_DEBUG, "Created entity collision_box size: %f x %f",
  //          entity.collision_box.size.x, entity.collision_box.size.y);

  return entity;
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

void entity_movement(Entity2D *entity) {
  entity->pos.x += entity->velocity.x * engine.delta_time;
  entity->collision_box.pos.x += entity->velocity.x * engine.delta_time;

  entity->pos.y += entity->velocity.y * engine.delta_time;
  entity->collision_box.pos.y += entity->velocity.y * engine.delta_time;

  if (entity->velocity.x != 0 && entity->velocity.y != 0) {
    entity->velocity.x *= 0.7f;
    entity->velocity.y *= 0.7f;
  }
}
