#include "../../include/core/engine.h"
#include "../../include/core/entity.h"

Entity player = (Entity){(Vector2){0, 0}, (Vector2){0, 0}, 0.f, 50};
Entity player2 = (Entity){(Vector2){0, 100}, (Vector2){0, 0}, 0.f, 50};

void on_update() {
  if (IsKeyDown(KEY_W)) {
    player.velocity.y = -1;
  } else if (IsKeyReleased(KEY_W)) {
    player.velocity.y = 0;
  }
  if (IsKeyDown(KEY_S)) {
    player.velocity.y = 1;
  } else if (IsKeyReleased(KEY_S)) {
    player.velocity.y = 0;
  }
  if (IsKeyDown(KEY_A)) {
    player.velocity.x = -1;
  } else if (IsKeyReleased(KEY_A)) {
    player.velocity.x = 0;
  }
  if (IsKeyDown(KEY_D)) {
    player.velocity.x = 1;
  } else if (IsKeyReleased(KEY_D)) {
    player.velocity.x = 0;
  }
  player2.velocity.x = player.velocity.x;
  player2.velocity.y = player.velocity.y;
  if (IsKeyPressed(KEY_ESCAPE)) {
    engine.status = STOP;
  }

  entity_movement(&player);
  entity_movement(&player2);
}

void on_draw() {
  DrawRectangleV(player.pos, (Vector2){50, 50}, RED);
  DrawRectangleV(player2.pos, (Vector2){50, 50}, GREEN);
}

int main() {
  engine_init();
  engine_run();

  return 0;
}