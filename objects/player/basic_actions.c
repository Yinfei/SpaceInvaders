#include "../../main/prototypes.h"

void render_player() {
  SDL_Rect rect;

  rect.x = ((SDL_GetTicks() / 50) % 2) * 100;
  rect.y = 0;
  rect.w = 100;
  rect.h = 100;
  SDL_RenderCopy(g_game->renderer, g_game->player->texture, &rect, &g_game->player->hitbox);
}

int damage_player(int i, t_element* element) {
  if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->player->damage_cooldown) == 1)
  {
    g_game->player->hp -= i;

    if (g_game->player->hp <= 0)
    {
      g_game->player->killed_by = element->parent;
      Mix_PlayChannel(1, g_game->jukebox.soundboard[6], 0);
    }
    else
      Mix_PlayChannel(1, g_game->jukebox.soundboard[4], 0);


    g_game->player->damage_cooldown = SDL_GetTicks() + 500;
    return 1;
  }
  else
    return 0;
}

void render_player_hp() {
  SDL_Rect rec;

  rec.x = 0;
  rec.y = 0;
  rec.w = 100 * g_game->player->hp;
  rec.h = 100;
  g_game->player->lifebox->box.w = 30 * g_game->player->hp;
  SDL_RenderCopy(g_game->renderer, g_game->player->lifebox->texture, &rec, &g_game->player->lifebox->box);
}
