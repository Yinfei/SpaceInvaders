#include "../../main/prototypes.h"

void init_enemies_hp(t_enemies* enemies) {
  int i;

  for (i = 0; i < 10; i++)
    enemies->hp[i] = 0;

  enemies->hp[0] = 3;
  enemies->hp[1] = 2;
  enemies->hp[2] = 1;
}

int enemy_hp(int type) {
  return g_game->enemies->hp[type];
}

void init_enemies_points(t_enemies* enemies) {
  int i;

  for (i = 0; i < 10; i++)
    enemies->points[i] = 0;

  enemies->points[0] = 7;
  enemies->points[1] = 3;
  enemies->points[2] = 1;
}

int enemy_points(int type) {
  return g_game->enemies->points[type];
}

int enemy_collision(t_element* enemy) {
  int collision;

  collision = 0;
  if (collision_manager(&enemy->hitbox, &g_game->player->hitbox) > 0)
  {
    damage_player(1, enemy);
    collision += damage_element(&g_game->enemies->enemy_list, enemy);
  }
  if (element_list_collision(&g_game->player->bullet_list, enemy) > 0)
    collision += damage_element(&g_game->enemies->enemy_list, enemy);

  return collision;
}
