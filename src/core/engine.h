#pragma once
#include <raylib.h>
#include <stdlib.h>

typedef enum { START, STOP } EngineStatus;
typedef enum {FULLSCREEN, WINDOWED} WindowMode;

typedef struct Scene Scene;
typedef struct Entity2D Entity2D;
typedef struct CollisionBox2D CollisionBox2D;
typedef struct Scene Scene;
typedef struct Renderer Renderer;

typedef struct {
  float delta_time;
  EngineStatus status;
  bool debug_draw;
  Vector2 window_size;
  WindowMode w_mode;
} Engine;

extern Engine engine;
extern Renderer renderer;
void engine_init();
void engine_run();
void engine_update();
void engine_shutdown();

void on_update();
void on_draw();
void draw_debug();
