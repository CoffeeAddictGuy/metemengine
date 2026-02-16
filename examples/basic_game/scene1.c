#include "scene1.h"
#include "../../src/scene/2d/camera2d.h"
#include "../../src/scene/2d/scene.h"
#include "camera.h"
#include "player.h"
#include <raylib.h>
#include <stdlib.h>

static void scene1_init(Scene *scene) {
  scene->static_count = 0;
  scene->static_count = 0;
  scene->character_count = 0;
  scene->camera_count = 0;
  Character2D player =
      character2d_create(NULL, player_init, player_update, player_destroy);
  player.base.self = &player;
  player_init(&player);

  scene_add_character(scene, player);

  MCamera2D camera = camera_create(camera_init, camera_update, camera_destroy);
  camera_init(&camera);

  scene_add_camera(scene, camera, 1, &scene->characters[0]);

  scene_add_tilemap(scene, "../resources/test3.json",
                    "../resources/testset.png");
}

Scene *scene1_create(void) {
  Scene *scene = malloc(sizeof(Scene));
  *scene = (Scene){0};
  scene->on_init = scene1_init;
  return scene;
}
