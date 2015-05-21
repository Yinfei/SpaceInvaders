#include "../../main/prototypes.h"

int simulate_player_collision() {
  t_element* current;

  current = g_game->landscape->block_list;
  while (current != NULL)
  {
    if (collision_manager(&g_game->player->hitbox, &current->hitbox) > 0
      && current->type != 13)
      return 1;
    else
      current = next_element(current);
  }
  return 0;
}

void player_collisions() {
  t_element* bullet;
  t_element* next;

  bullet = g_game->enemies->bullet_list;
  while (bullet != NULL)
  {
    next = next_element(bullet);
    if (collision_manager(&bullet->hitbox, &g_game->player->hitbox) > 0)
    {
      damage_player(1, bullet);
      remove_element(&g_game->enemies->bullet_list, bullet);
    }
    bullet = next;
  }
}
