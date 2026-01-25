#include "tile_map.h"
#include <cjson/cJSON.h>
#include <raylib.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

TileMap *tile_map_create(const char *const tilemap_json_path,
                         const char *const tileset_path) {
  TileMap *map = malloc(sizeof(TileMap));
  map->tileset = LoadTexture(tileset_path);
  tile_map_tlx_parse(map, tilemap_json_path);
  return map;
}

void tile_map_tlx_parse(TileMap *map, const char *const tileset_path) {
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

  const cJSON *layers = NULL;
  const cJSON *layer = NULL;

  printf("Layer print\n");
  layers = cJSON_GetObjectItemCaseSensitive(tilemap_json, "layers");
  map->layer_count = cJSON_GetArraySize(layers);
  map->layers = malloc(sizeof(TileLayer) * map->layer_count);
  if (map->layers == NULL) {
    return;
  }
  printf("Map have %d layers\n", cJSON_GetArraySize(layers));

  int l = 0;

  cJSON_ArrayForEach(layer, layers) {
    TileLayer *curr = &map->layers[l];
    cJSON *width = cJSON_GetObjectItemCaseSensitive(layer, "width");
    cJSON *height = cJSON_GetObjectItemCaseSensitive(layer, "height");
    if (!cJSON_IsNumber(width) || !cJSON_IsNumber(height)) {
      printf("Width or Height is not number!");
      return;
    }
    curr->width = width->valueint;
    curr->height = height->valueint;

    cJSON *name = cJSON_GetObjectItemCaseSensitive(layer, "name");
    if (!cJSON_IsString(name) || name->valuestring == NULL) {
      printf("Name is invalid!");
      return;
    }
    strcpy(curr->name, name->valuestring);

    cJSON *id = cJSON_GetObjectItemCaseSensitive(layer, "id");
    if (!cJSON_IsNumber(id) || id == NULL) {
      printf("ID is invalid!");
      return;
    }
    curr->layer_id = id->valueint;

    cJSON *data = cJSON_GetObjectItemCaseSensitive(layer, "data");
    if (!cJSON_IsArray(data) || data == NULL) {
      printf("No valid data!");
      continue;
    }
    int tile_count = curr->width * curr->height;
    int i = 0;
    cJSON *item = NULL;

    const char *data_print = cJSON_Print(data);
    curr->gids = malloc(sizeof(uint16_t) * (curr->width * curr->height));
    cJSON_ArrayForEach(item, data) {
      if (cJSON_IsNumber(item) && i < tile_count) {
        curr->gids[i++] = (uint16_t)item->valueint;
      }
    }

    printf("Layer %d. Width %d and Height %d with name %s\n", curr->layer_id,
           curr->width, curr->height, curr->name);
    for (int i = 0; i < curr->width * curr->height; i++) {
      if (i == (curr->width * curr->height) - 1) {
        printf("%d\n", curr->gids[i]);
      } else {
        printf("%d, ", curr->gids[i]);
      }
    }
    l += 1;
  }

  cJSON_Delete(tilemap_json);
  return;
}

void tile_map_free(TileMap *tilemap) {
  for (int i = 0; i < tilemap->layer_count; i++) {
    free(tilemap->layers[i].gids);
  }
  free(tilemap->layers);
  free(tilemap);
}
