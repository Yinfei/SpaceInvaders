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
  enemy->hitbox.x = cos(enemy->timeline)*40 + enemy->init_x;
  enemy->init_x--;
  enemy->timeline += 0.1;
}

void boss_movement(t_element* boss) {
  if ((boss->hitbox.x + boss->hitbox.w) < (g_window_width - 100))
    boss->hitbox.x += 1;
  boss->hitbox.y = sin(boss->timeline)*80 + boss->init_y;
  boss->timeline += 0.1;
 /* if (boss->hitbox.x == (g_window_width + 25))
    Mix_PlayMusic(g_game->jukebox.music[2], -1);
 */
}

void enemy_movement(t_element* enemy) {
  if (g_game->enemies->movements[enemy->type] != NULL)
    g_game->enemies->movements[enemy->type](enemy);
}
