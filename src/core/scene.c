#include "../../include/core/scene.h"

Scene scene_create() {
  Scene scene = {0};
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
