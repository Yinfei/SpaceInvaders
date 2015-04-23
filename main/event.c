#include "prototypes.h"

int menu_event_switcher() {
  clear_window();
  while (SDL_PollEvent(&g_game->event))
  {
    if (g_game->event.type == SDL_QUIT)
      return -1;
    else if (g_game->event.type == SDL_KEYDOWN)
    {
      if (g_game->event.key.keysym.sym == 32)
        return 0;
      else if (g_game->event.key.keysym.sym == SDLK_UP && g_game->menu->selected > 3)
        g_game->menu->selected -= 1;
      else if (g_game->event.key.keysym.sym == SDLK_DOWN && g_game->menu->selected < 5)
        g_game->menu->selected += 1;
    }
  }
  render_choice_screen(g_game->menu);
  return 1;
}

int event_switcher() {
  clear_window();
  render_background();

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
