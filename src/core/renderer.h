#pragma once
#include "engine.h"
#include "../scene/2d/tile_map.h"
#include "../scene/2d/entity.h"

typedef struct Scene Scene;
typedef struct MCamera2D MCamera2D;
typedef struct Renderer {
  Scene *current_scene;
}Renderer;

Renderer renderer_create();
void render_current_scene(Renderer *renderer);
void render_tile_map(TileMap *map, Rectangle *vewport);
void render_entities(TileMap *map, Rectangle *viewport, Entity2D *entities, int entities_count);
bool is_tile_in_viewport(Rectangle *viewport, Rectangle *object);
bool is_object_in_viewport(Rectangle *viewport, Rectangle *object);
int comp(const void *a, const void *b);

