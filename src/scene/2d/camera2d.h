#pragma once
#include "entity.h"


typedef struct MCamera2D {
	char name[32];
	Camera2D camera;
} MCamera2D;

MCamera2D camera_create();
