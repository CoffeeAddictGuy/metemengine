#include "../../src/core/renderer.h"
#include "../../src/scene/2d/scene.h"
#include "engine.h"
#include <math.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>

Renderer renderer_create() {
  Renderer renderer = {0};
  return renderer;
}

void renderer_set_scene(Renderer *renderer, Scene *scene) {
  renderer->current_scene = scene;
}

void renderer_current_scene(Renderer *renderer) {
  Scene *curr = renderer->current_scene;

  TileMap *curr_map = curr->map;
  int width = curr_map->layers[0].width;
  int height = curr_map->layers[0].height;
  int tile_width = curr_map->tile_width;
  int tile_height = curr_map->tile_height;
  if (curr->map != NULL) {
    for (int y = 0; y < height; y++) {
      for (int x = 0; x < width; x++) {
        uint16_t gid = curr_map->layers[0].gids[y * width + x];
        if (gid == 0) {
          continue;
        }
        uint16_t local_id = gid - 1;
        int tile_x = local_id % width;
        int tile_y = local_id / width;

        Rectangle src = {tile_x * tile_width, tile_y * tile_height, tile_width,
                         tile_height};
        Rectangle dest = {x * tile_width, y * tile_height, tile_width,
                          tile_height};
        if (dest.x + dest.width <= 800 && dest.x >= 0 ||
            dest.x + dest.height >= -450 && dest.x <= 0) {
          DrawTexturePro(curr_map->tileset, src, dest, (Vector2){0, 0}, 0,
                         WHITE);
        }
      }
    }
  }
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
  int fps = GetFPS();
  DrawText(TextFormat("%d", fps), 0, 0, 15, BLACK);
}
