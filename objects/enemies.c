#include "../main/prototypes.h"



void init_enemies() {
  t_enemies* enemies;

  enemies = malloc(sizeof(t_enemies));
  g_game->enemies = enemies;
  enemies->enemy_list = NULL;
  init_enemies_hp(enemies);

  /* creating enemy for test purposes */
  create_enemy(900, 120, 0, 3);
  create_enemy(920, 300, 0, 2);
  create_enemy(1000, 240, 0, 1);
  create_enemy(1050, 200, 0, 3);

  enemies->bullet_list = NULL;
}

void init_enemies_hp(t_enemies* enemies) {
  int i;

  for (i = 0; i < 10; i++)
    enemies->hp[i] = 0;

  enemies->hp[0] = 3;
}

int enemy_hp(int type) {
  return g_game->enemies->hp[type];
}

void create_enemy(int x, int y, int type) {
  t_element* enemy;

  enemy = malloc(sizeof(t_element));
  enemy->hitbox.x = x;
  enemy->hitbox.y = y;
  enemy->hitbox.w = 50;
  enemy->hitbox.h = 50;
  enemy->prev = NULL;
  enemy->hp = enemy_hp(type);
  enemy->cooldown = 0;
  enemy->type = type;
  enemy->parent = type;
  enemy->x = -1;
  enemy->y = 0;
  add_element(&g_game->enemies->enemy_list, enemy);
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

void enemies_actions() {
  element_actions(&g_game->enemies->enemy_list);
  element_actions(&g_game->enemies->bullet_list);
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

void free_enemies() {
  free_element_list(&g_game->enemies->enemy_list);
  free(g_game->enemies);
}
