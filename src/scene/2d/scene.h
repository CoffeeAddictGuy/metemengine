#pragma once
#include "physics/collision_box2d.h"
#include "../2d/entity.h"
#include "tile_map.h"
#include "camera2d.h"
#include <raylib.h>
#include <stdlib.h>

#define ENTITY_MAX 1000
#define CHARACTER_MAX 100
#define CAMERA_MAX 10

typedef struct Scene {
  Entity2D entities[ENTITY_MAX];
  Character2D characters[CHARACTER_MAX];
  CollisionBox2D collision_boxes[ENTITY_MAX];
  int entity_count;
  int character_count;
  int collision_count;
  TileMap *map;
  MCamera2D cameras[CAMERA_MAX];
  int camera_count;
  MCamera2D *main_camera;
  bool load;

  void (*on_init) (struct Scene *scene);
  void (*on_destroy) (struct Scene *scene);
} Scene;

void scene_init(Scene *scene);
void scene_update(Scene *scene, float dt);
void scene_destroy(Scene *scene);


Scene scene_create();
void scene_add_entity(Scene *scene, Entity2D entity);
void scene_add_character(Scene *scene, Character2D character);
Entity2D *scene_add_entityPro(Scene *scene, Vector2 size, Vector2 pos, Vector2 atlas_cord);
MCamera2D *scene_add_camera(Scene *scene);
void scene_add_tilemap(Scene *scene, const char *json_path, const char *tileset_path);
void set_main_camera(Scene *scene, MCamera2D *camera);
