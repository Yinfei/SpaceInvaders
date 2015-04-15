#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

int initialize_background() {
  /* setting box for near */
  game->background.near.x = -640;
  game->background.near.y = 0;
  game->background.near.w = 1920;
  game->background.near.h = 420;

  /* setting box for mid */
  game->background.mid.x = -320;
  game->background.mid.y = 0;
  game->background.mid.w = 1280;
  game->background.mid.h = 420;

  /* setting box for far */
  game->background.far.x = 0;
  game->background.far.y = 0;
  game->background.far.w = 640;
  game->background.far.h = 420;

  /* applying textures on boxes */
  game->background.near_texture = IMG_LoadTexture(game->renderer, "img/near.png");
  game->background.mid_texture  = IMG_LoadTexture(game->renderer, "img/mid.png");
  game->background.far_texture  = IMG_LoadTexture(game->renderer, "img/far.png");

  return 0;
}

void manage_background_actions() {

  if (game->background.near.x <= -400)
    game->background.near.x = 0;
  if (game->background.mid.x <= -600)
    game->background.mid.x = 0;

  game->background.near.x -= 2;
  game->background.mid.x -= 1;
}

void free_background() {
  SDL_DestroyTexture(game->background.near_texture);
  SDL_DestroyTexture(game->background.mid_texture);
  SDL_DestroyTexture(game->background.far_texture);
}
