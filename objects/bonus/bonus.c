#include "../../main/prototypes.h"

int init_bonus() {
  t_bonus* bonus;

  bonus = malloc(sizeof(t_bonus));
  bonus->funcs[0] = &alter_speed;
  bonus->funcs[1] = &alter_speed;
  bonus->funcs[2] = &alter_fire;
  bonus->funcs[3] = &alter_fire;
  bonus->funcs[4] = &alter_hp;
  bonus->funcs[5] = &alter_bullet_speed;
  bonus->funcs[6] = &alter_bullet_speed;
  bonus->bonus_list = NULL;
  g_game->bonus = bonus;
  bonus_batch();
  return 0;
}

void create_bonus(int x, int y, int type) {
  t_element* bonus;

  bonus = malloc(sizeof (t_element));
  bonus->hitbox.x = x;
  bonus->hitbox.y = y;
  bonus->hitbox.w = 20;
  bonus->hitbox.h = 20;
  bonus->prev = NULL;
  bonus->type = type;
  bonus->x = -1;
  bonus->y = 0;
  add_element(&g_game->bonus->bonus_list, bonus);
}

void free_bonus() {
  free_element_list(&g_game->bonus->bonus_list);
  free(g_game->bonus);
}
