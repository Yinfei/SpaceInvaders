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

void free_enemies() {
  free_element_list(&g_game->enemies->enemy_list);
  free(g_game->enemies);
}
