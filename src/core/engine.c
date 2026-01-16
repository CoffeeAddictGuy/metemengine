#include "../../include/core/engine.h"

const int WIDTH = 800;
const int HEIGHT = 450;

Engine engine = {0};

void engine_init() {
  engine.status = START;
  InitWindow(WIDTH, HEIGHT, "metemengine");
  SetTargetFPS(60);
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

void engine_shutdown() { CloseWindow(); }