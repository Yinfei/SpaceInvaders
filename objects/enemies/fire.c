#include "../../main/prototypes.h"

void init_enemy_fire() {
  int i;

  for (i = 0; i < 10; i++)
    g_game->enemies->fire[i] = NULL;

  g_game->enemies->fire[0] = &enemy_default_fire;
  g_game->enemies->fire[1] = &enemy_default_fire;
  g_game->enemies->fire[9] = &boss_fire;
}

void enemy_fire(t_element* enemy) {
  if (g_game->enemies->fire[enemy->type] != NULL)
    g_game->enemies->fire[enemy->type](enemy);
}

void boss_fire_bullet(t_element* enemy, int type) {
  t_element* bullet;

  bullet = malloc(sizeof(t_element));
  bullet->hitbox.x = enemy->hitbox.x;
  bullet->hitbox.y = enemy->hitbox.y + (enemy->hitbox.h / 2);
  bullet->hitbox.w = 20;
  bullet->hitbox.h = 20;
  bullet->type = 22;
  bullet->parent = enemy->type;
  boss_bullet_direction(bullet, type);
  add_element(&g_game->enemies->bullet_list, bullet);
}

void boss_fire(t_element* enemy) {
  int i;

  if (SDL_TICKS_PASSED(SDL_GetTicks(), enemy->cooldown) == 1)
  {
    i = rand() % 100;
    if (i < 5 && enemy->hitbox.x >= g_game->player->hitbox.x)
    {
      boss_fire_bullet(enemy, -1);
      boss_fire_bullet(enemy, 0);
      boss_fire_bullet(enemy, 1);
      enemy->cooldown = SDL_GetTicks() + 200;
    }
  }
}

void enemy_default_fire(t_element* enemy) {
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
      enemy_bullet_direction(enemy, bullet);
      add_element(&g_game->enemies->bullet_list, bullet);
      enemy->cooldown = SDL_GetTicks() + 700;
    }
  }
}
