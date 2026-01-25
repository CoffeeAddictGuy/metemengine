#pragma once
#include "../../core/engine.h"
#include <raylib.h>
#include <stdint.h>


typedef struct TileLayer {
  char name[32];
  uint16_t *gids;
  int width, height;
  int layer_id;
} TileLayer;

typedef struct TileMap {
  TileLayer *layers;
  int layer_count;
  Texture2D tileset;
  int tile_width, tile_height;
} TileMap;

TileMap *tile_map_create(const char *const tilemap_json_path, const char *const tileset_path);
void tile_map_tlx_parse(TileMap *map, const char *const tileset_path);
void tile_map_free(TileMap *tilemap); 
