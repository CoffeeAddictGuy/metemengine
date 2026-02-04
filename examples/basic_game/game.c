#include "../../src/core/engine.h"
#include "../../src/core/game_manager.h"
#include "scene1.h"

int main() {
  engine_init();
  Scene *scene1 = scene1_create();
  set_scene(scene1);
  engine_run();

  return 0;
}
