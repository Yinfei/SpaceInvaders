#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

int init_background() {
  /* setting box for near */
  g_game->background.near.x = -640;
  g_game->background.near.y = 0;
  g_game->background.near.w = 1920;
  g_game->background.near.h = 420;

  /* setting box for mid */
  g_game->background.mid.x = -320;
  g_game->background.mid.y = 0;
  g_game->background.mid.w = 1280;
  g_game->background.mid.h = 420;

  /* setting box for far */
  g_game->background.far.x = 0;
  g_game->background.far.y = 0;
  g_game->background.far.w = 640;
  g_game->background.far.h = 420;

  /* applying textures on boxes */
  g_game->background.near_texture = IMG_LoadTexture(g_game->renderer, "img/near.png");
  g_game->background.mid_texture  = IMG_LoadTexture(g_game->renderer, "img/mid.png");
  g_game->background.far_texture  = IMG_LoadTexture(g_game->renderer, "img/far.png");

  return 0;
}

void background_actions() {

  if (g_game->background.near.x <= -400)
    g_game->background.near.x = 0;
  if (g_game->background.mid.x <= -600)
    g_game->background.mid.x = 0;

  g_game->background.near.x -= 2;
  g_game->background.mid.x -= 1;
}

void free_background() {
  SDL_DestroyTexture(g_game->background.near_texture);
  SDL_DestroyTexture(g_game->background.mid_texture);
  SDL_DestroyTexture(g_game->background.far_texture);
}
