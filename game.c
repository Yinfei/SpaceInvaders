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
  game->window = SDL_CreateWindow("Water Evaders",100,200,GAMEWIDTH,GAMEHEIGHT,0);

  /* initializing renderer   (window, index, rendering flags) */
  game->renderer = SDL_CreateRenderer(game->window,-1,0);

  /* initialize variable to know if we keep going in the game */
  game->running = 1;

  /* initialize timer */
  game->timer = SDL_GetTicks();

  /* setting all textures and loading images */
  initialize_background();

  /* setting all the landscape blocks */
  initialize_landscape();

  /* call to initialize player */
  initialize_player();
  return 0;
}

void manage_game_actions() {

  /* manage background moving */
  manage_background_actions();

  /* manage landscape blocks, move everything backwards */
  manage_landscape_actions();

  /* manage enemies appearing ? manage ennemies moving forwards ... */

  /* manage powerups appearing ? manage powerups moving forwards ... */

  /* changing music ? (for boss ...) */

}

void end_game() {

  /* delete all bullets */
  free_player_bullets();

  /* free bullet texture */
  /* SDL_DestroyTexture(game->player.bullet_texture); */

  /* free landscape blocks ... */

  /* free player {address, textures} */

  /* free enemies */

  /* free enemy texture */

  /* free background textures */
  SDL_DestroyTexture(game->background.near_texture);
  SDL_DestroyTexture(game->background.mid_texture);
  SDL_DestroyTexture(game->background.far_texture);

  /* destroy window */
  SDL_DestroyWindow(game->window);
  /* exit SDL */
  SDL_Quit();
}
