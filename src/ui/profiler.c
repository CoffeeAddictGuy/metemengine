#include "profiler.h"
#define RAYGUI_IMPLEMENTATION
#include "../../includes/raygui.h"

int profiler_init() { return GuiPanel((Rectangle){85, 70, 250, 100}, "Hello"); }
