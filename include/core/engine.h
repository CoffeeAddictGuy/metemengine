#pragma once
#include <raylib.h>

typedef enum { START, STOP } EngineStatus;

typedef struct {
  float delta_time;
  EngineStatus status;
  bool debug_draw;
} Engine;

extern Engine engine;

typedef struct Scene Scene;
typedef struct Entity2D Entity2D;
typedef struct CollisionBox2D CollisionBox2D;

void engine_init();
void engine_run();
void engine_update();
void engine_shutdown();

void on_update();
void on_draw();
void draw_debug();
