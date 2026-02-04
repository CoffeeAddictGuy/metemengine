#include "scene.h"
#include "entity.h"
#include "tile_map.h"
#include <raylib.h>
#include <stdio.h>

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

  for (int i = 0; i < scene->entity_count; i++) {
    if (scene->entities[i].on_init) {
      scene->entities[i].on_init(scene->entities[i].self);
    }
  }

  for (int i = 0; i < scene->character_count; i++) {
    if (scene->characters[i].on_init) {
      TraceLog(LOG_DEBUG, "Name %s", scene->characters[i].name);
      scene->characters[i].on_init(&scene->characters[i]);
    }
  }
}

void scene_update(Scene *scene, float dt) {
  if (scene == NULL) {
    return;
  }

  for (int i = 0; i < scene->entity_count; i++) {
    if (scene->entities[i].on_update) {
      scene->entities[i].on_update(scene->entities[i].self, dt);
    }
  }

  for (int i = 0; i < scene->character_count; i++) {
    if (scene->characters[i].on_update) {
      TraceLog(LOG_DEBUG, "Name - %s", scene->characters[i].name);
      scene->characters[i].on_update(&scene->characters[i], dt);
    }
  }
}

void scene_destroy(Scene *scene) {
  if (scene == NULL) {
    return;
  }

  for (int i = 0; i < scene->entity_count; i++) {
    if (scene->entities[i].on_destroy) {
      scene->entities[i].on_destroy(scene->entities[i].self);
    }
  }
  if (scene->on_destroy) {
    scene->on_destroy(scene);
  }
}

void scene_add_entity(Scene *scene, Entity2D entity) {
  scene->entities[scene->entity_count++] = entity;
}

void scene_add_character(Scene *scene, Character2D character) {
  scene->characters[scene->character_count++] = character;
}

Entity2D *scene_add_entityPro(Scene *scene, Vector2 size, Vector2 pos,
                              Vector2 atlas_cord) {
  Entity2D entity = entity_create_Pro(size, pos, atlas_cord);
  scene->entities[scene->entity_count] = entity;
  scene->entity_count++;
  return &scene->entities[scene->entity_count - 1];
}

MCamera2D *scene_add_camera(Scene *scene) {
  MCamera2D camera = camera_create();
  printf("Camera name %s!\n", camera.name);
  scene->cameras[scene->camera_count] = camera;
  scene->camera_count++;
  if (scene->main_camera == NULL) {
    set_main_camera(scene, &scene->cameras[scene->camera_count - 1]);
  }
  printf("Camera name %s!\n", scene->main_camera->name);
  return &scene->cameras[scene->camera_count - 1];
}

void scene_add_tilemap(Scene *scene, const char *json_path,
                       const char *tileset_path) {
  scene->map = tile_map_create(scene, json_path, tileset_path);
}

void set_main_camera(Scene *scene, MCamera2D *camera) {
  scene->main_camera = camera;
}
