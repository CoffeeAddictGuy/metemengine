#include "../../src/core/renderer.h"
#include "../../src/scene/2d/scene.h"
#include "engine.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

Renderer renderer_create() {
  Renderer renderer = {0};
  return renderer;
}

void renderer_set_scene(Renderer *renderer, Scene *scene) {
  renderer->current_scene = scene;
}

void render_current_scene(Renderer *renderer) {
  Scene *curr = renderer->current_scene;

  bool has_camera = false;
  MCamera2D *cmr;

  if (curr->main_camera != NULL) {
    BeginMode2D(curr->main_camera->camera);
    has_camera = true;
    cmr = curr->main_camera;
  }

  render_tile_map(curr->map);
  render_entities(curr->map, curr->entities, curr->entity_count);

  if (curr->main_camera != NULL) {
    EndMode2D();
  }

  int fps = GetFPS();
  DrawText(TextFormat("%d", fps), 0, 0, 15, WHITE);
}

void render_tile_map(TileMap *map) {
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

        DrawTexturePro(map->tileset, src, dest, (Vector2){0, 0}, .0f, WHITE);
      }
    }
  }
}

void render_entities(TileMap *map, Entity2D *entities, int entities_count) {
  Entity2D *render_order = malloc(sizeof(Entity2D) * entities_count);
  memcpy(render_order, entities, sizeof(Entity2D) * entities_count);

  qsort(render_order, entities_count, sizeof(Entity2D), comp);

  for (int i = 0; i < entities_count; i++) {
    if (strcmp(render_order[i].name, "Player") == 0 ||
        strcmp(render_order[i].name, "Enemy") == 0) {
      DrawRectangleV(render_order[i].pos, render_order[i].size, RED);
    } else {
      Rectangle src = (Rectangle){
          render_order[i].atlas_cord.x, render_order[i].atlas_cord.y,
          render_order[i].size.x, render_order[i].size.y};
      Rectangle dest =
          (Rectangle){render_order[i].pos.x, render_order[i].pos.y,
                      render_order[i].size.x, render_order[i].size.y};
      DrawTexturePro(map->tileset, src, dest, (Vector2){0, 0}, .0f, WHITE);
    }
  }
  free(render_order);
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
