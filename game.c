#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

int initialize_game() {
  /* initializing game globals */
  GAMEHEIGHT = 420;
  GAMEWIDTH = 640;

  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    return -1;

  /* initializing window   (title, posx, posy, width, height, ..) */
  game->window = SDL_CreateWindow("DUBSTEP CAT !",100,200,GAMEWIDTH,GAMEHEIGHT,0);

  /* initializing renderer   (window, index, rendering flags) */
  game->renderer = SDL_CreateRenderer(game->window,-1,0);

  /* initialize variable to know if we keep going in the game */
  game->running = 1;

  /* initialize game score */
  game->score = 0;

  /* initialize timer */
  game->timer = SDL_GetTicks();

  /* setting all textures and loading images */
  initialize_background();

  /* setting all the landscape blocks */
  initialize_landscape();

  /* call to initialize player */
  initialize_player();

  /* call to initialize enemies */
  initialize_enemies();

  return 0;
}

void manage_game_actions() {

  /* manage background moving */
  manage_background_actions();

  /* manage landscape blocks, move everything backwards */
  manage_landscape_actions();

  /* manage landscape collisions with player bullets */
  manage_landscape_collisions();

  /* manage powerups appearing ? manage powerups moving forwards ... */

  /* changing music ? (for boss ...) */
}


void end_game() {
  free_player();
  free_landscape();
  free_enemies();
  free_background();

  /* destroy window */
  SDL_DestroyWindow(game->window);
  /* exit SDL */
  SDL_Quit();
}
