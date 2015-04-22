#include "../main/prototypes.h"

void clear_window() {
  SDL_RenderClear(g_game->renderer);
}

void render_window() {
  SDL_RenderPresent(g_game->renderer);
}
