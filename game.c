#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

int init_game() {
  /* initializing game globals */
  g_window_height = 420;
  g_window_width = 640;

  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    return -1;

  /* initializing window   (title, posx, posy, width, height, ..) */
  g_game->window = SDL_CreateWindow("DUBSTEP CAT !",100,200,g_window_width,g_window_height,0);
  /* initializing renderer   (window, index, rendering flags) */
  g_game->renderer = SDL_CreateRenderer(g_game->window,-1,0);
  /* initialize variable to know if we keep going in the game */
  g_game->running = 1;
  /* initialize game score */
  g_game->score = 0;
  /* initialize timer */
  g_game->timer = SDL_GetTicks();
  /* setting all textures and loading images */
  init_background();
  /* setting all the landscape blocks */
  init_landscape();
  /* call to initialize player */
  init_player();
  /* call to initialize enemies */
  init_enemies();
  return 0;
}

void game_actions() {
  /* manage background moving */
  background_actions();
  /* manage landscape blocks, move everything backwards */
  landscape_actions();
  /* manage landscape collisions with player bullets */
  landscape_collisions();
  /* manage powerups appearing ? manage powerups moving forwards ... */
  /* changing music ? (for boss ...) */
}

void end_game() {
  free_player();
  free_landscape();
  free_enemies();
  free_background();
  /* destroy window */
  SDL_DestroyWindow(g_game->window);
  /* exit SDL */
  SDL_Quit();
}
