#pragma once
#include "C:\raylib\include\raylib.h"

typedef enum { START, STOP } EngineStatus;

typedef struct {
  float delta_time;
  EngineStatus status;
} Engine;

extern Engine engine;

void engine_init();
void engine_run();
void engine_update();
void engine_shutdown();

void on_update();
void on_draw();