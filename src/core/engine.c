#include "engine.h"
#include "../core/renderer.h"
#include "../scene/2d/entity.h"
#include "../scene/2d/physics/collision_box2d.h"
#include "../scene/2d/scene.h"
#include <raylib.h>

const int WIDTH = 800;
const int HEIGHT = 450;

Engine engine = {0};
Renderer renderer = {0};

void engine_init() {
  engine.status = START;
  engine.debug_draw = false;
  engine.window_size = (Vector2){WIDTH, HEIGHT};
  InitWindow(WIDTH, HEIGHT, "metemengine");
  SetWindowState(FLAG_WINDOW_UNDECORATED);
  SetTargetFPS(1000);
  SetTraceLogLevel(LOG_DEBUG);
}

void engine_run() {
  while (!WindowShouldClose() && engine.status == START) {
    engine.delta_time = GetFrameTime();
    on_update();

    BeginDrawing();
    ClearBackground(BLACK);
    on_draw();
    EndDrawing();
  }
}

void on_draw() { render_current_scene(&renderer); }

void engine_shutdown() { CloseWindow(); }
