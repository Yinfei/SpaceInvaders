#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

void clear_window() {
  /* clear screen */
  SDL_RenderClear(game->renderer);

  /* render each background layer (far to near) */
  SDL_RenderCopy(game->renderer, game->background.far_texture, NULL, &game->background.far);
  SDL_RenderCopy(game->renderer, game->background.mid_texture, NULL, &game->background.mid);
  SDL_RenderCopy(game->renderer, game->background.near_texture, NULL, &game->background.near);
}

void render_screen() {
  /* Render window */
  SDL_RenderPresent(game->renderer);
}
