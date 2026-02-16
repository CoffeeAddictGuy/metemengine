#include "profiler.h"
#include "../../src/core/engine.h"
#include <raylib.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define RAYGUI_IMPLEMENTATION
#include "../../includes/raygui.h"

const char ram_info[13] = "/proc/meminfo";
const char cpu_stat[10] = "/proc/stat";

Profiler *profiler_init() {
  Profiler *profiler = malloc(sizeof(Profiler));
  profiler->cpu = 0.0f;
  profiler->fps = 0;
  profiler->memory = 0;
  profiler->pid = getpid();
  profiler->last_update_time = 0.0f;
  profiler->update_interval = 5.0f;
  profiler_update_data(profiler);

  return profiler;
}

void profiler_print_info(Profiler *profiler) {
  printf("Pid %d\n", profiler->pid);
}

void profiler_update_data(Profiler *profiler) {
// Linux
#ifdef __linux__
  FILE *f = fopen(ram_info, "r");
  char string[128];
  while (fgets(string, 128, f)) {
    if (strncmp(string, "MemTotal:", 8) == 0) {
      printf("MemTotal: %s\n", string);
    }
  }
  fclose(f);
#elif WIN32
#endif
}

void profiler_data_view(Profiler *profiler) {
  GuiPanel((Rectangle){engine.window_size.x - 300, 0, 300, 200}, "Debug info");
  GuiLabel((Rectangle){engine.window_size.x - 300, 0, 300, 200}, TextFormat("FPS: %d", GetFPS()));
  GuiLabel((Rectangle){engine.window_size.x - 300, 10, 300, 200}, TextFormat("Delta time: %f", engine.delta_time));
  if (GuiCheckBox((Rectangle){engine.window_size.x - 280, 50, 10, 10},
                  "Fullscreen?", &engine.fullscreen)) {
    window_fullscreen();
  }
}
