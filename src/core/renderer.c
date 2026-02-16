#include "../../src/core/renderer.h"
#include "../../src/scene/2d/scene.h"
#include "engine.h"
#include "game_manager.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdint.h>
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
  if (curr->static_count > 0) {
    render_entities(curr->map, curr);
  }

  if (curr->main_camera != NULL) {
    EndMode2D();
  }

  int fps = GetFPS();
  DrawText(TextFormat("%d", fps), 0, 0, 15, WHITE);
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

void render_entities(TileMap *map, Scene *scene) {

  RendererItem render_list[ENTITY_MAX];
  int render_item = 0;

  for (int static_body = 0; static_body < scene->static_count; static_body++) {
    render_list[render_item++] =
        make_render_item_from_static(&scene->statics[static_body]);
  }

  for (int character = 0; character < scene->character_count; character++) {
    render_list[render_item++] =
        make_render_item_from_character(&scene->characters[character]);
  }

  qsort(render_list, render_item, sizeof(RendererItem), comp);

  for (int i = 0; i < render_item; i++) {
    if (render_list[i].type == CHARACTER_BODY) {
      DrawRectangleV(render_list[i].pos, render_list[i].size, RED);
    } else {
      Rectangle src = render_list[i].src;
      Rectangle dest =
          (Rectangle){render_list[i].pos.x, render_list[i].pos.y,
                      render_list[i].size.x, render_list[i].size.y};
      DrawTexturePro(map->tileset, src, dest, (Vector2){0, 0}, .0f, WHITE);
    }
  }
}

RendererItem make_render_item_from_static(StaticBody2D *static_body) {
  Rectangle static_src =
      (Rectangle){static_body->atlas_cord.x, static_body->atlas_cord.y,
                  static_body->size.x, static_body->size.y};
  RendererItem item =
      (RendererItem){.pos = static_body->base.pos,
                     .size = static_body->size,
                     .src = static_src,
                     .y_sort = static_body->base.pos.y + static_body->size.y,
                     .type = STATIC_BODY};
  return item;
}

RendererItem make_render_item_from_character(Character2D *character) {
  Rectangle static_src =
      (Rectangle){character->atlas_cord.x, character->atlas_cord.y,
                  character->size.x, character->size.y};
  RendererItem item =
      (RendererItem){.pos = character->base.pos,
                     .size = character->size,
                     .src = static_src,
                     .y_sort = character->base.pos.y + character->size.y,
                     .type = CHARACTER_BODY};
  return item;
}

int comp(const void *a, const void *b) {
  float a_y = ((RendererItem *)a)->pos.y + ((RendererItem *)a)->size.y;
  float b_y = ((RendererItem *)b)->pos.y + ((RendererItem *)b)->size.y;

  if (a_y < b_y) {
    return -1;
  } else if (a_y > b_y) {
    return 1;
  } else {
    return 0;
  }
}
