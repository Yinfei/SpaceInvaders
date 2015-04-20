#include "../main/prototypes.h"

void render_player() {
  SDL_Rect rect;

  rect.x = ((SDL_GetTicks() / 50) % 3) * 150;
  rect.y = 0;
  rect.w = 150;
  rect.h = 100;
  SDL_RenderCopy(g_game->renderer, g_game->player->texture, &rect, &g_game->player->hitbox);
}

int damage_player(int i, t_element* element) {
  if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->player->damage_cooldown) == 1)
  {
    g_game->player->hp -= i;
    if (g_game->player->hp <= 0)
      g_game->player->killed_by = element->parent;

    g_game->player->damage_cooldown = SDL_GetTicks() + 500;
    return 1;
  }
  else
    return 0;
}

/* to come : power up ... */
