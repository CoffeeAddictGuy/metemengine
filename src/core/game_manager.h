#pragma once
#include "../scene/2d/scene.h"

#include "engine.h"

#define MAX_PRELOAD_SCENE 10

#define ENTITY_MAX 1000
#define CAMERA_MAX 10

typedef struct GameManager {
  Scene *current_scene;
  Scene preload_scene[MAX_PRELOAD_SCENE];
  int preload_scene_count;
} GameManager;

GameManager *game_manager_init();
void set_scene(Scene *scene);
void load_scene(Scene *scene);
void preload_scene(Scene *scene);
void unload_scene(Scene *scene);
void game_manager_free(Scene *scene);
void game_update(float dt);
