#include "prototypes.h"

int event_switcher() {
  clear_window();

  if (game_state() > 0)
    return -1;

  while (SDL_PollEvent(&g_game->event))
  {
    if (g_game->event.type == SDL_QUIT)
      return -1;
    else if (g_game->event.type == SDL_KEYDOWN)
      add_player_action();
    else if (g_game->event.type == SDL_KEYUP)
      remove_player_action();
  }
  player_actions();
  enemies_actions();
  game_actions();
  return 0;
}

int error() {
  printf("some sort of error message g_game->error\n");
  return -1;
}
