#pragma once
#include "entity.h"
#include <raylib.h>


typedef struct MCamera2D {
	char name[32];
	Camera2D camera;
  
  void *target;
  OnInitFn on_init;
  OnUpdateFn on_update;
  OnDestroyFn on_destroy;
} MCamera2D;

MCamera2D camera_create(OnInitFn on_init, OnUpdateFn on_update, OnDestroyFn on_destroy);
Vector2 get_target_pos(void *target);
void camera_update_offset(MCamera2D *camera);