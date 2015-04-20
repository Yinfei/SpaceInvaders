#include "../main/prototypes.h"

void enemies_actions() {
  element_actions(&g_game->enemies->enemy_list);
  element_actions(&g_game->enemies->bullet_list);
}

void enemy_movement(t_element* enemy) {
  /* change this to some sort of custom movement (oscilation, rotation, linear) */
  enemy->hitbox.y = enemy->hitbox.y;
}

void enemy_bullet_direction(t_element* bullet) {
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
  bullet->y = angle;
}

void enemy_fire(t_element* enemy) {
  t_element* bullet;
  int i;

  if (SDL_TICKS_PASSED(SDL_GetTicks(), enemy->cooldown) == 1)
  {
    i = rand() % 100;
    if (i == 1 && enemy->hitbox.x >= g_game->player->hitbox.x)
    {
      bullet = malloc(sizeof(t_element));
      bullet->hitbox.x = enemy->hitbox.x;
      bullet->hitbox.y = enemy->hitbox.y + (enemy->hitbox.h / 2);
      bullet->hitbox.w = 10;
      bullet->hitbox.h = 10;
      bullet->type = 21;
      bullet->parent = enemy->type;
      enemy_bullet_direction(bullet);
      add_element(&g_game->enemies->bullet_list, bullet);
      enemy->cooldown = SDL_GetTicks() + 700;
    }
  }
}

