#include "../../main/prototypes.h"

void enemies_actions() {
  element_actions(&g_game->enemies->enemy_list);
  element_actions(&g_game->enemies->bullet_list);
}

void enemy_bullet_direction(t_element* enemy, t_element* bullet) {
  int x;
  int y;
  int angle;

  x = bullet->hitbox.x - g_game->player->hitbox.x;
  if (bullet->hitbox.y >= g_game->player->hitbox.y)
    y = - (bullet->hitbox.y - g_game->player->hitbox.y);
  else
    y = g_game->player->hitbox.y - bullet->hitbox.y;

  if (x != 0)
    angle = (3 * y) / x;
  else
    angle = y;

  bullet->x = -3;
  if (enemy->type == 1 && enemy->type == 9)
    bullet->y = angle;
  else
    bullet->y = 0;
}

void boss_bullet_direction(t_element* bullet, int type) {
  int x;
  int y;
  int angle;

  if (type == 1 || type == -1)
  {
    bullet->x = -3;
    bullet->y = 3 * type;
  }
  else
  {
    x = bullet->hitbox.x - g_game->player->hitbox.x;
    if (bullet->hitbox.y >= g_game->player->hitbox.y)
      y = - (bullet->hitbox.y - g_game->player->hitbox.y);
    else
      y = g_game->player->hitbox.y - bullet->hitbox.y;

    if (x != 0)
      angle = (3 * y) / x;
    else
      angle = y;
    bullet->x = -3;
    bullet->y = angle;
  }
}
