#include "scene.h"
#include "camera2d.h"
#include "entity.h"
#include "tile_map.h"
#include <raylib.h>
#include <string.h>

Scene scene_create() {
  Scene scene = {0};
  scene.map = NULL;
  scene.main_camera = NULL;
  return scene;
}

void scene_init(Scene *scene) {
  if (scene == NULL) {
    return;
  }
  if (scene->on_init) {
    scene->on_init(scene);
  }

  for (int i = 0; i < scene->static_count; i++) {
    if (scene->statics[i].base.on_init) {
      scene->statics[i].base.on_init(scene->statics[i].base.self);
    }
  }

  for (int i = 0; i < scene->character_count; i++) {
    if (scene->characters[i].base.on_init) {
      scene->characters[i].base.on_init(&scene->characters[i]);
    }
  }

  for (int i = 0; i < scene->camera_count; i++) {
    if (scene->cameras[i].on_init) {
      scene->cameras[i].on_init(&scene->cameras[i]);
    }
  }
}

void scene_update(Scene *scene, float dt) {
  if (scene == NULL) {
    return;
  }

  for (int i = 0; i < scene->static_count; i++) {
    if (scene->statics[i].base.on_update) {
      scene->statics[i].base.on_update(scene->statics[i].base.self, dt);
    }
  }

  for (int i = 0; i < scene->character_count; i++) {
    if (scene->characters[i].base.on_update) {
      scene->characters[i].base.on_update(&scene->characters[i], dt);
    }
  }

  for (int i = 0; i < scene->camera_count; i++) {
    if (scene->cameras[i].on_update) {
      scene->cameras[i].on_update(&scene->cameras[i], dt);
    }
  }
}

void scene_destroy(Scene *scene) {
  if (scene == NULL) {
    return;
  }

  for (int i = 0; i < scene->static_count; i++) {
    if (scene->statics[i].base.on_destroy) {
      scene->statics[i].base.on_destroy(scene->statics[i].base.self);
    }
  }
  if (scene->on_destroy) {
    scene->on_destroy(scene);
  }
}

void scene_add_static(Scene *scene, StaticBody2D static_body) {
  scene->statics[scene->static_count++] = static_body;
}

void scene_add_character(Scene *scene, Character2D character) {
  scene->characters[scene->character_count++] = character;
}

// Entity2D *scene_add_entity_pro(Scene *scene, Vector2 size, Vector2 pos,
//                               Vector2 atlas_cord) {
//   Entity2D entity = entity_create_Pro(size, pos, atlas_cord);
//   scene->statics[scene->static_count++] = entity;
//   return &scene->statics[scene->static_count - 1];
// }

StaticBody2D *scene_add_static_pro(Scene *scene, Vector2 size, Vector2 pos,
                                   Vector2 atlas_cord) {
  StaticBody2D static_body =
      static_body_create_pro(NULL, NULL, NULL, NULL, size, pos, atlas_cord);
  scene->statics[scene->static_count++] = static_body;
  return &scene->statics[scene->static_count - 1];
}

Character2D *scene_add_character_pro(Scene *scene, Vector2 size, Vector2 pos,
                                     Vector2 atlas_cord) {
  Character2D character_body =
      character2d_create_pro(NULL, NULL, NULL, NULL, size, pos, atlas_cord);
  scene->characters[scene->character_count++] = character_body;
  return &scene->characters[scene->character_count - 1];
}

void scene_add_camera(Scene *scene, MCamera2D camera, int mode, void *target) {
  if (target == NULL) {
    return;
  }

  if (mode == 1) {
    camera.target = target;
  }
  scene->cameras[scene->camera_count++] = camera;
  TraceLog(LOG_DEBUG, "Camera name %s", camera.name);
  if (scene->main_camera == NULL) {
    set_main_camera(scene, &scene->cameras[scene->camera_count - 1]);
  }
  TraceLog(LOG_DEBUG, "Main camera name - %s", scene->main_camera->name);
}

// MCamera2D *scene_add_camera(Scene *scene) {
//   MCamera2D camera = camera_create();
//   printf("Camera name %s!\n", camera.name);
//   scene->cameras[scene->camera_count] = camera;
//   scene->camera_count++;
//   if (scene->main_camera == NULL) {
//     set_main_camera(scene, &scene->cameras[scene->camera_count - 1]);
//   }
//   printf("Camera name %s!\n", scene->main_camera->name);
//   return &scene->cameras[scene->camera_count - 1];
// }

void scene_add_tilemap(Scene *scene, const char *json_path,
                       const char *tileset_path) {
  scene->map = tile_map_create(scene, json_path, tileset_path);
}

void set_main_camera(Scene *scene, MCamera2D *camera) {
  scene->main_camera = camera;
}
