#include "player.h"
#include <raylib.h>
#include <string.h>

void player_init(void *self) {
  Character2D *p = (Character2D *)self;
  p->pos.x = 0;
  p->pos.y = 0;
  p->size.x = 50;
  p->size.y = 50;
  p->speed = 100.f;
  strcpy(p->name, "Player");
}

void player_update(void *self, float dt) {
  Character2D *player = self;

  if (IsKeyDown(KEY_W)) {
    player->velocity.y = -1 * player->speed;
  } else if (IsKeyReleased(KEY_W)) {
    player->velocity.y = 0;
  }
  if (IsKeyDown(KEY_S)) {
    player->velocity.y = 1 * player->speed;
  } else if (IsKeyReleased(KEY_S)) {
    player->velocity.y = 0;
  }
  if (IsKeyDown(KEY_A)) {
    player->velocity.x = -1 * player->speed;
  } else if (IsKeyReleased(KEY_A)) {
    player->velocity.x = 0;
  }
  if (IsKeyDown(KEY_D)) {
    player->velocity.x = 1 * player->speed;
  } else if (IsKeyReleased(KEY_D)) {
    player->velocity.x = 0;
  }
  if (IsKeyPressed(KEY_ESCAPE)) {
    engine.status = STOP;
  }
  if (IsKeyPressed(KEY_F1)) {
    engine.debug_draw = !engine.debug_draw;
  }

  TraceLog(LOG_DEBUG, "Player name - %s", player->name);
  TraceLog(LOG_DEBUG, "Player pos - %f.x/%f.y", player->pos.x, player->pos.y);
  TraceLog(LOG_DEBUG, "Player size - %f.x/%f.y", player->size.x,
           player->size.y);

  entity_movement(player);
}

void player_destroy(void *self) { TraceLog(LOG_DEBUG, "Player destroy"); }
