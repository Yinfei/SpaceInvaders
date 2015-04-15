#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

int event_switcher() {
  /* clear screen */
  clear_window();

  /* looping on each event */
  while (SDL_PollEvent(&g_game->event))
  {
    if (g_game->event.type == SDL_QUIT)
      return -1;
    else if (g_game->event.type == SDL_KEYDOWN)
      add_player_action();
    else if (g_game->event.type == SDL_KEYUP)
      remove_player_action();
  }

  /* some examples for dying */
  if (g_game->player.hitbox.x + g_game->player.hitbox.w <= 0)
    return -1;
  if (g_game->player.hp <= 0)
    return -1;

  /* going through each performable action */
  player_actions();
  /* check enemy actions. {shoot, take damage} */
  enemies_actions();
  /* check game actions. {animate background, change music, powerUps} */
  game_actions();
  return 0;
}

int error() {
  printf("some sort of error message g_game->error\n");
  return -1;
}
