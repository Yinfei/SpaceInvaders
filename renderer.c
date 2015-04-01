#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

void clearWindow(game_stc* game) {
  /* clear screen */
  SDL_RenderClear(game->renderer);

  /* render each background layer (far to near) */
  SDL_RenderCopy(game->renderer, game->background.farTxtr, NULL, &game->background.far);
  SDL_RenderCopy(game->renderer, game->background.midTxtr, NULL, &game->background.mid);
  SDL_RenderCopy(game->renderer, game->background.nearTxtr, NULL, &game->background.near);
}

void renderScreen(game_stc* game) {
  /* Render window */
  SDL_RenderPresent(game->renderer);
}
