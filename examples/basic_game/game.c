#include "../../include/core/collision_box2D.h"
#include "../../include/core/engine.h"
#include "../../include/core/entity.h"
#include "../../include/core/renderer.h"
#include "../../include/core/scene.h"
#include <raylib.h>
#include <string.h>

Entity2D *player = {0};
Entity2D *enemy = {0};
Scene scene1 = {0};
float player_speed = 200;

void character_init() {
  player = scene_add_entity(&scene1);
  enemy = scene_add_entity(&scene1);
  strcpy(player->name, "Player");
  strcpy(enemy->name, "Enemy");
}

void on_update() {
  if (IsKeyDown(KEY_W)) {
    player->velocity.y = -1 * player_speed;
  } else if (IsKeyReleased(KEY_W)) {
    player->velocity.y = 0;
  }
  if (IsKeyDown(KEY_S)) {
    player->velocity.y = 1 * player_speed;
  } else if (IsKeyReleased(KEY_S)) {
    player->velocity.y = 0;
  }
  if (IsKeyDown(KEY_A)) {
    player->velocity.x = -1 * player_speed;
  } else if (IsKeyReleased(KEY_A)) {
    player->velocity.x = 0;
  }
  if (IsKeyDown(KEY_D)) {
    player->velocity.x = 1 * player_speed;
  } else if (IsKeyReleased(KEY_D)) {
    player->velocity.x = 0;
  }
  if (IsKeyPressed(KEY_ESCAPE)) {
    engine.status = STOP;
  }
  if (IsKeyPressed(KEY_R)) {
    player->collision_box.pos.x = 300;
    player->collision_box.pos.y = -100;
  }
  if (IsKeyPressed(KEY_F1)) {
    engine.debug_draw = !engine.debug_draw;
  }

  TraceLog(LOG_DEBUG, "Entity %s pos  x = %f, y = %f ", player->name,
           player->pos.x, player->pos.y);
  TraceLog(LOG_DEBUG, "Collision %s pos  x = %f, y = %f ",
           player->collision_box.name, player->collision_box.pos.x,
           player->collision_box.pos.y);
  if (aabb_collision(&player->collision_box, &enemy->collision_box)) {
    TraceLog(LOG_DEBUG, "COLLIDING!");
    player->is_colliding = true;
    enemy->is_colliding = true;
  } else {
    player->is_colliding = false;
    enemy->is_colliding = false;
  }
  entity_movement(player);
}

int main() {
  engine_init();
  character_init();
  renderer_set_scene(&renderer, &scene1);
  engine_run();

  return 0;
}
