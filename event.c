#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

int event_switcher() {
  /* clear screen */
  clear_window();

  /* looping on each event */
  while (SDL_PollEvent(&game->event))
  {
    if (game->event.type == SDL_QUIT)
      return -1;
    else if (game->event.type == SDL_KEYDOWN)
      add_player_action();
    else if (game->event.type == SDL_KEYUP)
      remove_player_action();
  }

  /* going through each performable action */
  manage_player_actions();
  /* parse through bullets */
  manage_player_bullets();

  /* check enemy actions. {move, shoot, take damage} */
  /* manage_enemy_actions(); */
  /* manage enemy bullets */
  /* manage_enemy_bullets(); */


  /* check game actions. {animate background, change music, powerUps} */
  manage_game_actions();

  return 0;
}

int error() {
  printf("some sort of error message game->error\n");
  return -1;
}
