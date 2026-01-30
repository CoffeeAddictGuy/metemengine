#include "../../src/core/renderer.h"
#include "../../src/scene/2d/scene.h"
#include "../../src/ui/profiler.h"
#include "engine.h"
#include "game_manager.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

Renderer renderer_create() {
  Renderer renderer = {0};
  renderer.current_scene = engine.gm->current_scene;
  return renderer;
}

void render_current_scene(Renderer *renderer) {
  Scene *curr = engine.gm->current_scene;

  bool has_camera = false;
  MCamera2D *cmr;
  Rectangle viewport = (Rectangle){0, 0, 0, 0};

  if (curr->main_camera != NULL) {
    BeginMode2D(curr->main_camera->camera);
    has_camera = true;
    cmr = curr->main_camera;
    viewport = (Rectangle){cmr->camera.target.x - engine.window_size.x * 0.5f,
                           cmr->camera.target.y - engine.window_size.y * 0.5f,
                           engine.window_size.x, engine.window_size.y};
  }

  if (curr->map) {
    render_tile_map(curr->map);
  }
  if (curr->entity_count > 0) {
    render_entities(curr->map, curr->entities, curr->entity_count);
  }

  if (curr->character_count > 0) {
    render_characters(curr->characters, curr->character_count);
  }

  if (curr->main_camera != NULL) {
    EndMode2D();
  }
#ifdef DEBUG
  profiler_data_view(metrics);
#endif
  int fps = GetFPS();
  DrawText(TextFormat("%d", fps), 0, 0, 15, WHITE);
}

void render_tile_map(TileMap *map, Rectangle *viewport) {
  for (int i = 0; i < map->layer_count; i++) {
    for (int y = 0; y < map->map_height; y++) {
      for (int x = 0; x < map->map_width; x++) {
        uint16_t gid = map->layers[i].gids[y * map->map_width + x];
        if (gid == 0) {
          continue;
        }

        uint16_t local_id = gid - 1;

        int tile_x = local_id % map->map_width;
        int tile_y = local_id / map->map_width;

        Rectangle src = {tile_x * map->tile_width, tile_y * map->tile_height,
                         map->tile_width, map->tile_height};
        Rectangle dest = {x * map->tile_width, y * map->tile_height,
                          map->tile_width, map->tile_height};
        if (is_tile_in_viewport(viewport, &dest)) {
          DrawTexturePro(map->tileset, src, dest, (Vector2){0, 0}, .0f, WHITE);
        }
      }
    }
  }
}

void render_entities(TileMap *map, Rectangle *viewport, Entity2D *entities,
                     int entities_count) {
  Entity2D *render_order = malloc(sizeof(Entity2D) * entities_count);
  memcpy(render_order, entities, sizeof(Entity2D) * entities_count);

  qsort(render_order, entities_count, sizeof(Entity2D), comp);

  for (int i = 0; i < entities_count; i++) {
    if (strcmp(render_order[i].name, "Player") == 0 ||
        strcmp(render_order[i].name, "Enemy") == 0) {
      TraceLog(LOG_DEBUG, "Player found out!");
      TraceLog(LOG_DEBUG, "Player pos - %f.x/%f.y", render_order[i].pos.x,
               render_order[i].pos.y);
      DrawRectangleV(render_order[i].pos, render_order[i].size, RED);
    } else {
      Rectangle src = (Rectangle){
          render_order[i].atlas_cord.x, render_order[i].atlas_cord.y,
          render_order[i].size.x, render_order[i].size.y};
      Rectangle dest =
          (Rectangle){render_order[i].pos.x, render_order[i].pos.y,
                      render_order[i].size.x, render_order[i].size.y};
      if (is_object_in_viewport(viewport, &dest)) {
        DrawTexturePro(map->tileset, src, dest, (Vector2){0, 0}, .0f, WHITE);
      }
    }
  }
  free(render_order);
}

bool is_tile_in_viewport(Rectangle *viewport, Rectangle *object) {
  if (CheckCollisionRecs(*viewport, *object)) {
    return true;
  }
  return false;
}

bool is_object_in_viewport(Rectangle *viewport, Rectangle *object) {
  if (CheckCollisionRecs(*viewport, *object)) {
    return true;
  }
  return false;
}

void render_characters(Character2D *characters, int characters_count) {
  for (int i = 0; i < characters_count; i++) {
    DrawRectangleV(characters[i].pos, characters[i].size, RED);
  }
}

int comp(const void *a, const void *b) {
  float a_y = ((Entity2D *)a)->pos.y + ((Entity2D *)a)->size.y;
  float b_y = ((Entity2D *)b)->pos.y + ((Entity2D *)b)->size.y;

  if (a_y < b_y) {
    return -1;
  } else if (a_y > b_y) {
    return 1;
  } else {
    return 0;
  }
}
