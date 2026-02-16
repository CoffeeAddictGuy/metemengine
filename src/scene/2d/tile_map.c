#include "tile_map.h"
#include "scene.h"
#include <cjson/cJSON.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TileMap *tile_map_create(Scene *scene, const char *const tilemap_json_path,
                         const char *const tileset_path) {
  TileMap *map = malloc(sizeof(TileMap));
  map->tileset = LoadTexture(tileset_path);
  tile_map_tlx_parse(scene, map, tilemap_json_path);
  return map;
}

void tile_map_tlx_parse(Scene *scene, TileMap *map,
                        const char *const tileset_path) {
  FILE *fp = fopen(tileset_path, "r");
  if (fp == NULL) {
    printf("Error: Unable to open file.\n");
    return;
  }
  fseek(fp, 0, SEEK_END);
  long file_size = ftell(fp);
  fseek(fp, 0, SEEK_SET);

  if (file_size > 1024 * 1024) {
    printf("Error: file too big\n");
    fclose(fp);
    return;
  }

  char *buffer = malloc(file_size + 1);
  size_t read = fread(buffer, 1, file_size, fp);
  buffer[read] = '\0';
  fclose(fp);

  const cJSON *name = NULL;
  cJSON *tilemap_json = cJSON_Parse(buffer);

  if (tilemap_json == NULL) {
    const char *error_ptr = cJSON_GetErrorPtr();
    if (error_ptr != NULL) {
      fprintf(stderr, "Error: %s\n", error_ptr);
    }
  }

  // get width and height for tilemap
  const cJSON *tile_width = NULL;
  const cJSON *tile_height = NULL;

  const cJSON *map_width = NULL;
  const cJSON *map_height = NULL;

  tile_width = cJSON_GetObjectItemCaseSensitive(tilemap_json, "tilewidth");
  tile_height = cJSON_GetObjectItemCaseSensitive(tilemap_json, "tileheight");

  map_width = cJSON_GetObjectItemCaseSensitive(tilemap_json, "width");
  map_height = cJSON_GetObjectItemCaseSensitive(tilemap_json, "height");

  if (!cJSON_IsNumber(tile_width) || tile_width == NULL ||
      !cJSON_IsNumber(tile_height) || tile_height == NULL) {
    printf("ERROR: tile width or tile height not found\n");
    return;
  }

  if (!cJSON_IsNumber(map_width) || map_width == NULL ||
      !cJSON_IsNumber(map_height) || map_height == NULL) {
    printf("ERROR: tile width or tile height not found\n");
    return;
  }

  printf("Tile width %d and tile height %d\n", tile_width->valueint,
         tile_height->valueint);
  map->tile_width = tile_width->valueint;
  map->tile_height = tile_height->valueint;
  map->map_width = map_width->valueint;
  map->map_height = map_height->valueint;

  // get layers
  const cJSON *layers = NULL;
  const cJSON *layer = NULL;

  layers = cJSON_GetObjectItemCaseSensitive(tilemap_json, "layers");

  int l_count = 0;
  cJSON_ArrayForEach(layer, layers) {
    TileLayer *curr = &map->layers[l_count];
    cJSON *type = cJSON_GetObjectItemCaseSensitive(layer, "type");
    if (cJSON_IsString(type) && type != NULL) {
      if (strcmp(type->valuestring, "tilelayer") == 0) {
        l_count++;
      }
    }
  }
  map->layer_count = l_count;
  map->layers = malloc(sizeof(TileLayer) * map->layer_count);
  if (map->layers == NULL) {
    return;
  }

  printf("Map have %d layers\n", map->layer_count);

  int l = 0;

  // go through layers
  cJSON_ArrayForEach(layer, layers) {
    TileLayer *curr = &map->layers[l];
    cJSON *type = cJSON_GetObjectItemCaseSensitive(layer, "type");
    TraceLog(LOG_DEBUG, "TYPE IS %s", type->valuestring);
    if (cJSON_IsString(type) && type != NULL) {
      if (strcmp(type->valuestring, "tilelayer") == 0) {
        tile_map_tile_layer_parser(scene, curr, layer);
        l++;
      } else if (strcmp(type->valuestring, "objectgroup") == 0) {
        TraceLog(LOG_DEBUG, "Found Objects layer!");
        tile_map_object_layer_parser(scene, curr, layer);
      }
    }
  }

  cJSON_Delete(tilemap_json);
  free(buffer);
  return;
}

void tile_map_tile_layer_parser(Scene *scene, TileLayer *t_layer,
                                const cJSON *layer) {
  cJSON *width = cJSON_GetObjectItemCaseSensitive(layer, "width");
  cJSON *height = cJSON_GetObjectItemCaseSensitive(layer, "height");
  if (!cJSON_IsNumber(width) || !cJSON_IsNumber(height)) {
    printf("Width or Height is not number!");
    return;
  }
  t_layer->width = width->valueint;
  t_layer->height = height->valueint;

  cJSON *name = cJSON_GetObjectItemCaseSensitive(layer, "name");
  if (!cJSON_IsString(name) || name->valuestring == NULL) {
    printf("Name is invalid!");
    return;
  }
  strcpy(t_layer->name, name->valuestring);

  cJSON *id = cJSON_GetObjectItemCaseSensitive(layer, "id");
  if (!cJSON_IsNumber(id) || id == NULL) {
    printf("ID is invalid!");
    return;
  }
  t_layer->layer_id = id->valueint;

  cJSON *data = cJSON_GetObjectItemCaseSensitive(layer, "data");
  if (!cJSON_IsArray(data) || data == NULL) {
    printf("No valid data!");
    return;
  }
  int tile_count = t_layer->width * t_layer->height;
  int i = 0;
  cJSON *item = NULL;

  t_layer->gids = malloc(sizeof(uint16_t) * (t_layer->width * t_layer->height));
  cJSON_ArrayForEach(item, data) {
    if (cJSON_IsNumber(item) && i < tile_count) {
      t_layer->gids[i++] = (uint16_t)item->valueint;
    }
  }
}

void tile_map_object_layer_parser(Scene *scene, TileLayer *t_layer,
                                  const cJSON *layer) {
  cJSON *object = NULL;
  cJSON *objects = NULL;
  if (cJSON_GetObjectItemCaseSensitive(layer, "name") != NULL &&
      strcmp(cJSON_GetObjectItemCaseSensitive(layer, "name")->valuestring,
             "Tree") == 0) {
    objects = cJSON_GetObjectItemCaseSensitive(layer, "objects");
    cJSON_ArrayForEach(object, objects) {
      cJSON *gid = cJSON_GetObjectItemCaseSensitive(object, "gid");
      cJSON *height = cJSON_GetObjectItemCaseSensitive(object, "height");
      cJSON *width = cJSON_GetObjectItemCaseSensitive(object, "width");
      cJSON *x_pos = cJSON_GetObjectItemCaseSensitive(object, "x");
      cJSON *y_pos = cJSON_GetObjectItemCaseSensitive(object, "y");

      if (!cJSON_IsNumber(gid) || gid == NULL) {
        continue;
      }

      if (!cJSON_IsNumber(height) || height == NULL) {
        continue;
      }

      if (!cJSON_IsNumber(width) || width == NULL) {
        continue;
      }

      if (!cJSON_IsNumber(x_pos) || x_pos == NULL) {
        continue;
      }

      if (!cJSON_IsNumber(y_pos) || y_pos == NULL) {
        continue;
      }

      int local_id = gid->valueint - 1041;

      int x_atlas = local_id % 20;
      int y_atlas = local_id / 20;

      Vector2 entity_size = (Vector2){width->valueint, height->valueint};
      Vector2 entity_pos =
          (Vector2){x_pos->valueint, y_pos->valueint - height->valueint};
      Vector2 atlas_pos =
          (Vector2){x_atlas * width->valueint, y_atlas * height->valueint};
      scene_add_static_pro(scene, entity_size, entity_pos, atlas_pos);
    }
  }
}

void tile_map_free(TileMap *tilemap) {
  for (int i = 0; i < tilemap->layer_count; i++) {
    free(tilemap->layers[i].gids);
  }
  free(tilemap->layers);
  UnloadTexture(tilemap->tileset);
  free(tilemap);
}
