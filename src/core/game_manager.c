#include "game_manager.h"
#include "engine.h"
#include <stdlib.h>

GameManager *game_manager_init() {
  GameManager *gm = malloc(sizeof(GameManager));
  gm->preload_scene_count = 0;
  return gm;
}

void set_scene(Scene *scene) {
  if (engine.gm->current_scene) {
    scene_destroy(engine.gm->current_scene);
    free(engine.gm->current_scene);
  }
  engine.gm->current_scene = scene;
  scene_init(scene);
}

void load_scene(Scene *scene) {
  // free(engine.gm->current_scene);
  engine.gm->current_scene = scene;
}

void preload_scene(Scene *scene) {
  GameManager *gm = engine.gm;
  if (gm->preload_scene_count <= MAX_PRELOAD_SCENE) {
    gm->preload_scene[gm->preload_scene_count] = *scene;
    gm->preload_scene[gm->preload_scene_count].load = true;
    gm->preload_scene_count++;
  }

  if (gm->preload_scene_count > MAX_PRELOAD_SCENE) {
    for (int i = 0; i < MAX_PRELOAD_SCENE; i++) {
      if (!gm->preload_scene[i].load) {
        gm->preload_scene[gm->preload_scene_count] = *scene;
        gm->preload_scene[gm->preload_scene_count].load = true;
      }
    }
  }
}

void unload_scene(Scene *scene) {
  GameManager *gm = engine.gm;
  for (int i = 0; i < gm->preload_scene_count; i++) {
    if (&gm->preload_scene[i] == scene) {
      gm->preload_scene[i].load = false;
    }
  }
}

void game_update(float dt) { scene_update(engine.gm->current_scene, dt); }

void game_manager_free(Scene *scene) { free(scene); }
