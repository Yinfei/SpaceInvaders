#include "../../main/prototypes.h"

void enemy_mouvement_vertical(t_element* enemy) {
  enemy->hitbox.y = sin(enemy->timeline)*40 + enemy->init_y;
  enemy->timeline += 0.1;
}

void enemy_mouvement_none(t_element* enemy) {
  enemy->timeline += 0.1;
}

void enemy_movement_rotate(t_element* enemy) {
  enemy->hitbox.y = sin(enemy->timeline)*40 + enemy->init_y;
  enemy->hitbox.x = cos(enemy->timeline) + enemy->hitbox.x;
  enemy->timeline += 0.1;
}

void enemy_movement(t_element* enemy) {
  if (g_game->enemies->movements[enemy->type] != NULL)
    g_game->enemies->movements[enemy->type](enemy);
}
