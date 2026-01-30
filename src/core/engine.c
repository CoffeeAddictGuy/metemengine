#include "engine.h"
#include "../core/renderer.h"
#include "../scene/2d/entity.h"
#include "../scene/2d/physics/collision_box2d.h"
#include "../scene/2d/scene.h"
#include "../ui/profiler.h"
#include <raylib.h>
#include <stdio.h>

const int WIDTH = 800;
const int HEIGHT = 450;

Engine engine = {0};
Renderer renderer = {0};
Profiler *metrics = {0};

void engine_init() {
  engine.status = START;
  engine.debug_draw = false;
  engine.window_size = (Vector2){WIDTH, HEIGHT};
  metrics = profiler_init();
  InitWindow(WIDTH, HEIGHT, "metemengine");
  SetWindowState(FLAG_WINDOW_UNDECORATED);
  SetTargetFPS(1000);
  SetTraceLogLevel(LOG_DEBUG);
}

void engine_run() {
  while (!WindowShouldClose() && engine.status == START) {
    engine.delta_time = GetFrameTime();
    on_update();
#ifdef Debug
    metric_update();
#endif
    BeginDrawing();
    ClearBackground(BLACK);
    on_draw();
    EndDrawing();
  }
}

void on_draw() { render_current_scene(&renderer); }

void window_fullscreen() {
  if (engine.w_mode == FULLSCREEN) {
    ToggleFullscreen();
    engine.w_mode = FULLSCREEN;
  } else if (engine.w_mode != FULLSCREEN) {
    ToggleBorderlessWindowed();
    engine.w_mode = BORDERLESS;
  }
}

void metric_update() {
  metrics->last_update_time += engine.delta_time;
  if (metrics->last_update_time >= metrics->update_interval) {
    profiler_update_data(metrics);
    metrics->last_update_time = 0.0f;
  }
}

void engine_shutdown() { CloseWindow(); }
