#include "../../src/core/renderer.h"
#include "../../src/scene/2d/scene.h"
#include <raylib.h>

Renderer renderer_create() {
  Renderer renderer = {0};
  return renderer;
}

void renderer_set_scene(Renderer *renderer, Scene *scene) {
  renderer->current_scene = scene;
}

void renderer_current_scene(Renderer *renderer) {
  Scene *curr = renderer->current_scene;
  // TraceLog(LOG_DEBUG, "Current scene pointer: %p", (void *)curr);
  // TraceLog(LOG_DEBUG, "Entity count: %d", curr->entity_count);

  // draw entities
  for (int i = 0; i < curr->entity_count; i++) {
    // TraceLog(LOG_DEBUG, "Entity %d size: %f x %f", i,
    // curr->entities[i].size.x,
    //          curr->entities[i].size.y);
    DrawRectangleV(curr->entities[i].pos, curr->entities[i].size, RED);
    if (engine.debug_draw) {
      if (!curr->entities[i].is_colliding) {
        DrawRectangleLinesEx(
            (Rectangle){curr->entities[i].collision_box.pos.x,
                        curr->entities[i].collision_box.pos.y,
                        curr->entities[i].collision_box.size.x,
                        curr->entities[i].collision_box.size.y},
            1, BLUE);
      } else {
        DrawRectangleLinesEx(
            (Rectangle){curr->entities[i].collision_box.pos.x,
                        curr->entities[i].collision_box.pos.y,
                        curr->entities[i].collision_box.size.x,
                        curr->entities[i].collision_box.size.y},
            1, YELLOW);
      }
    }
  }
  if (curr->map != NULL) {
    DrawTexture(curr->map->tileset, 0, 0, WHITE);
  }
}
