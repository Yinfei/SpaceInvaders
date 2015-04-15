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


  /* some examples for dying */
  if (game->player.hitbox.x + game->player.hitbox.w <= 0)
    return -1;
  if (game->player.hp <= 0)
    return -1;



  /* going through each performable action */
  manage_player_actions();
  /* check enemy actions. {shoot, take damage} */
  manage_enemies_actions();
  /* check game actions. {animate background, change music, powerUps} */
  manage_game_actions();

  return 0;
}

int error() {
  printf("some sort of error message game->error\n");
  return -1;
}
