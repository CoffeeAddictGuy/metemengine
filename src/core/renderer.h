#pragma once
#include "engine.h"

typedef struct Scene Scene;

typedef struct Renderer {
  Scene *current_scene;

}Renderer;

Renderer renderer_create();
void renderer_set_scene(Renderer *renderer, Scene *scene);
void renderer_current_scene(Renderer *renderer);
