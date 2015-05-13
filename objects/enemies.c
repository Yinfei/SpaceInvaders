#include "../main/prototypes.h"

void init_enemies() {
  t_enemies* enemies;

  enemies = malloc(sizeof(t_enemies));
  g_game->enemies = enemies;
  enemies->enemy_list = NULL;
  init_enemies_hp(enemies);
  init_enemies_points(enemies);
  init_enemies_names();
  init_enemies_movements();
  init_enemy_fire();

  /* creating enemy for test purposes */
  create_enemy(900, 120, 0);
  create_enemy(920, 330, 1);
  create_enemy(1000, 240, 2);
  create_enemy(1050, 200, 0);

  create_enemy(700, 200, 9);

  enemies->bullet_list = NULL;
}

void init_enemies_movements() {
  int i;

  for (i = 0; i < 10; i++)
    g_game->enemies->movements[i] = NULL;

  g_game->enemies->movements[0] = &enemy_movement_rotate;
  g_game->enemies->movements[1] = &enemy_mouvement_vertical;
  g_game->enemies->movements[2] = &enemy_mouvement_none;
  g_game->enemies->movements[9] = &boss_movement;
}

void init_enemies_names() {
  g_game->enemies->names[0] = "fatty";
  g_game->enemies->names[1] = "bobby";
  g_game->enemies->names[2] = "mine";
  g_game->enemies->names[9] = "BOSS";
}

void create_enemy(int x, int y, int type) {
  t_element* enemy;

  enemy = malloc(sizeof(t_element));
  enemy->type = type;
  enemy->parent = type;
  enemy->hitbox.x = x;
  enemy->hitbox.y = y;
  enemy->init_x = x;
  enemy->init_y = y;
  if (type == 9)
  {
    enemy->hitbox.w = 100;
    enemy->hitbox.h = 100;
  }
  else
  {
    enemy->hitbox.w = 50;
    enemy->hitbox.h = 50;
  }
  enemy->prev = NULL;
  enemy->hp = enemy_hp(type);
  enemy->cooldown = 0;
  enemy->timeline = 0;
  enemy->points = enemy_points(type);
  enemy->x = -1;
  enemy->y = 0;
  add_element(&g_game->enemies->enemy_list, enemy);
}

void free_enemies() {
  free_element_list(&g_game->enemies->enemy_list);
  free(g_game->enemies);
}
