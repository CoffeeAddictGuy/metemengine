#include "scene.h"
#include <stdio.h>

Scene scene_create() {
  Scene scene = {0};
  scene.map = NULL;
  scene.main_camera = NULL;
  return scene;
}

Entity2D *scene_add_entity(Scene *scene) {
  Entity2D entity = entity_create();
  scene->entities[scene->entity_count] = entity;
  scene->collision_boxes[scene->collision_count] = entity.collision_box;
  scene->entity_count++;
  scene->collision_count++;
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

void set_main_camera(Scene *scene, MCamera2D *camera) {
  scene->main_camera = camera;
}
