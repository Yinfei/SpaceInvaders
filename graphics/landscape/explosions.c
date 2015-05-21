#include "../../main/prototypes.h"

void explosion_block(t_element* enemy) {
  t_element* block;

  block = malloc(sizeof (t_element));
  block->hitbox.x = enemy->hitbox.x;
  block->hitbox.y = enemy->hitbox.y;
  block->hitbox.w = enemy->hitbox.w;
  block->hitbox.h = enemy->hitbox.h;
  block->prev = NULL;
  block->type = 13;
  block->x = -1;
  block->y = 0;
  block->timeline = SDL_GetTicks();
  block->cooldown = SDL_GetTicks() + 1000;
  add_element(&g_game->landscape->block_list, block);
}
