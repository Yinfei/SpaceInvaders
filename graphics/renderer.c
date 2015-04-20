#include "../main/prototypes.h"

void clear_window() {
  SDL_RenderClear(g_game->renderer);
  SDL_RenderCopy(g_game->renderer, g_game->background.far_texture, NULL, &g_game->background.far);
  SDL_RenderCopy(g_game->renderer, g_game->background.mid_texture, NULL, &g_game->background.mid);
  SDL_RenderCopy(g_game->renderer, g_game->background.near_texture, NULL, &g_game->background.near);
}

void render_window() {
  SDL_RenderPresent(g_game->renderer);
}
