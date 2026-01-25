#include "physics/collision_box2D.h"
#include "../2d/entity.h"
#include "tile_map.h"


#define MAX 1000

typedef struct Scene {
  Entity2D entities[MAX];
  CollisionBox2D collision_boxes[MAX];
  int entity_count;
  int collision_count;
  TileMap *map;
  void (*scene_on_draw) (void);
  void (*scene_on_update) (void);
} Scene;


Scene scene_create();
Entity2D *scene_add_entity(Scene *scene);
