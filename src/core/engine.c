#include "engine.h"
#include "../core/game_manager.h"
#include "../core/renderer.h"
#include "../scene/2d/scene.h"
#include "../ui/profiler.h"
#include "../scene/2d/tile_map.h"
#include "../ui/profiler.h"
#include <raylib.h>

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
  engine.gm = game_manager_init();
  metrics = profiler_init();
  engine.w_mode = BORDERLESS;
  InitWindow(WIDTH, HEIGHT, "metemengine");
  SetWindowState(FLAG_WINDOW_UNDECORATED);
  SetTargetFPS(144);
  SetTraceLogLevel(LOG_DEBUG);
}

void engine_run() {
  TraceLog(LOG_DEBUG, "Engine window size %f width and %f height", engine.window_size.x, engine.window_size.y);
  while (!WindowShouldClose() && engine.status == START) {
    engine.delta_time = GetFrameTime();
#ifdef Debug
    metric_update();
#endif
    scene_update(engine.gm->current_scene, engine.delta_time);

    BeginDrawing();
    ClearBackground(BLACK);
    on_draw();
    EndDrawing();
  }
}

void on_draw() { render_current_scene(&renderer); }

void window_fullscreen() {
  if (engine.w_mode != FULLSCREEN) {
    int curr_monitor = GetCurrentMonitor();
    int m_height = GetMonitorHeight(curr_monitor);
    int m_width = GetMonitorWidth(curr_monitor);
    ToggleFullscreen();
    SetWindowSize(m_width, m_height);
    engine.window_size = (Vector2) {m_width, m_height};
    engine.w_mode = FULLSCREEN;
    TraceLog(LOG_DEBUG, "Engine window size %f width and %f height", engine.window_size.x, engine.window_size.y);
    if (engine.gm->current_scene->camera_count > 0) {
      camera_update_offset(&engine.gm->current_scene->cameras[0]);
      TraceLog(LOG_DEBUG, "Update camera offset");
    }
  } else if (engine.w_mode == FULLSCREEN) {
    ToggleBorderlessWindowed();
    SetWindowSize(WIDTH, HEIGHT);
    engine.window_size = (Vector2) {WIDTH, HEIGHT};
    engine.w_mode = BORDERLESS;
    TraceLog(LOG_DEBUG, "Engine window size %f width and %f height", engine.window_size.x, engine.window_size.y);
    if (engine.gm->current_scene->camera_count > 0) {
      camera_update_offset(&engine.gm->current_scene->cameras[0]);
      TraceLog(LOG_DEBUG, "Update camera offset");
    }
  }
}

void metric_update() {
  metrics->last_update_time += engine.delta_time;
  if (metrics->last_update_time >= metrics->update_interval) {
    profiler_update_data(metrics);
    metrics->last_update_time = 0.0f;
  }
}

void engine_shutdown() {
  tile_map_free(renderer.current_scene->map);
  game_manager_free(engine.gm->current_scene);
  CloseWindow();
}
