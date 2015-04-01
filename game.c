#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

int initializeGame(game_stc* game) {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    return -1;

  /* initializing window   (title, posx, posy, width, height, ..) */
  game->window = SDL_CreateWindow("Water Evaders",100,200,640,420,0);

  /* initializing renderer   (window, index, rendering flags) */
  game->renderer = SDL_CreateRenderer(game->window,-1,0);

  /* initialize timer */
  game->timer = SDL_GetTicks();

  /* setting all textures and loading images */
  initializeBackground(game);

  /* call to initialize player */
  initializePlayer(game);
  return 0;
}

int initializeBackground(game_stc* game) {
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
  game->background.nearTxtr  = IMG_LoadTexture(game->renderer, "img/near.png");
  game->background.midTxtr   = IMG_LoadTexture(game->renderer, "img/mid.png");
  game->background.farTxtr   = IMG_LoadTexture(game->renderer, "img/far.png");

  return 0;
}

void endGame(game_stc* game) {

  /* delete all bullets */
  freeBulletList(game);

  /* free bullet texture */
  /* SDL_DestroyTexture(game->player.bulletTxtr); */

  /* free background textures */
  SDL_DestroyTexture(game->background.nearTxtr);
  SDL_DestroyTexture(game->background.midTxtr);
  SDL_DestroyTexture(game->background.farTxtr);

  /* destroy window */
  SDL_DestroyWindow(game->window);
  /* exit SDL */
  SDL_Quit();
}
