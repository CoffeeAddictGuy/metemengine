#pragma once
#include "engine.h"
#include "../scene/2d/tile_map.h"
#include "../scene/2d/entity.h"
#include <raylib.h>

typedef struct Scene Scene;
typedef struct MCamera2D MCamera2D;

typedef enum {STATIC_BODY, CHARACTER_BODY} RenderType;

typedef struct Renderer {
  Scene *current_scene;
} Renderer;

typedef struct RendererItem {
  Vector2 pos;
  Vector2 size;
  Rectangle src;
  float y_sort;
  RenderType type;
} RendererItem;

Renderer renderer_create();
void render_current_scene(Renderer *renderer);
void render_tile_map(TileMap *map);
void render_entities(TileMap *map, Scene *scene);
RendererItem make_render_item_from_static(StaticBody2D *static_body);
RendererItem make_render_item_from_character(Character2D *character);
void render_characters(Character2D *characters, int characters_count);
int comp(const void *a, const void *b);

