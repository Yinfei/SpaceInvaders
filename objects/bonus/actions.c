#include "../../main/prototypes.h"

void switch_bonus(t_element* bonus) {
  int i;

  i = bonus->type - 31;
  g_game->bonus->funcs[i](bonus);
}

int bonus_collision(t_element* bonus) {
  if (collision_manager(&bonus->hitbox, &g_game->player->hitbox) > 0)
  {
    switch_bonus(bonus);
    remove_element(&g_game->bonus->bonus_list, bonus);
    return 1;
  }
  return 0;
}
