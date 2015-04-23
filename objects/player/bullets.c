#include "../../main/prototypes.h"

int player_bullet_direction() {
  return g_game->player->bullet_direction;
}

void set_bullet_direction_up() {
  if (g_game->player->bullet_direction > -1)
    g_game->player->bullet_direction -= 1;
}

void set_bullet_direction_down() {
  if (g_game->player->bullet_direction < 1)
    g_game->player->bullet_direction += 1;
}

void reset_bullet_direction() {
  g_game->player->bullet_direction = 0;
}
