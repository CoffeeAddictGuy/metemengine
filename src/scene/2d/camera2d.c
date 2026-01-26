#include "camera2d.h"

MCamera2D camera_create() {
	MCamera2D camera = { 0 };
	camera.camera.zoom = 1.0f;
	return camera;
}