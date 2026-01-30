#include "physics/collision_box2d.h"
#include "../2d/entity.h"
#include "tile_map.h"
#include "camera2d.h"
#include <raylib.h>
#include <stdlib.h>

#define ENTITY_MAX 1000
#define CAMERA_MAX 10

typedef struct Scene {
  Entity2D entities[ENTITY_MAX];
  CollisionBox2D collision_boxes[ENTITY_MAX];
  int entity_count;
  int collision_count;
  TileMap *map;
  MCamera2D cameras[CAMERA_MAX];
  int camera_count;
  MCamera2D *main_camera;

  void (*scene_on_draw) (void);
  void (*scene_on_update) (void);
} Scene;


Scene scene_create();
Entity2D *scene_add_entity(Scene *scene);
Entity2D *scene_add_entityPro(Scene *scene, Vector2 size, Vector2 pos, Vector2 atlas_cord);
MCamera2D *scene_add_camera(Scene *scene);
void scene_add_tilemap(Scene *scene, const char *json_path, const char *tileset_path);
void set_main_camera(Scene *scene, MCamera2D *camera);
