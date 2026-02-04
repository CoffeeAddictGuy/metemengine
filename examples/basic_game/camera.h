#pragma once
#include "../../src/scene/2d/camera2d.h"
#include "../../src/core/game_manager.h"

void camera_init(void *self);
void camera_update(void *self, float dt);
void camera_destroy(void *self);
