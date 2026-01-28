#pragma once

#ifdef WIN32
#include <pdh.h>

#elif __linux__
#include <sys/sysinfo.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>

#endif


typedef struct Profiler {
  pid_t pid;
  int fps;
  int memory;
  float cpu;
  float last_update_time;
  float update_interval;
} Profiler;

Profiler *profiler_init();

void profiler_print_info(Profiler *profiler);
void profiler_update_data(Profiler *profiler);
void profiler_data_view(Profiler *profiler);
