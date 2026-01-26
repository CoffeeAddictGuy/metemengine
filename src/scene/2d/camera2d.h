#pragma once
#include "entity.h"


typedef struct MCamera2D {
	char *name;
	Camera2D camera;
	Entity2D *target;
} MCamera2D;

MCamera2D camera_create();
