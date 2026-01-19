#include "../../include/core/engine.h"
#include "../../include/core/collision_box2D.h"
#include "../../include/core/entity.h"
#include "../../include/core/renderer.h"
#include "../../include/core/scene.h"
#include <raylib.h>

const int WIDTH = 800;
const int HEIGHT = 450;

Engine engine = {0};
Renderer renderer = {0};

void engine_init() {
  engine.status = START;
  engine.debug_draw = false;
  InitWindow(WIDTH, HEIGHT, "metemengine");
  SetTargetFPS(60);
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

void on_draw() { renderer_current_scene(&renderer); }

void engine_shutdown() { CloseWindow(); }
