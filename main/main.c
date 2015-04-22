#include "prototypes.h"

void launch_game() {
  init_game_elements();

  while (1)
  {
    if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->timer) == 1)
    {
      g_game->timer = SDL_GetTicks() + 16;
      if (event_switcher() != -1)
        render_window();
      else
        break;
    }
    else
      SDL_Delay(2);
  }
  free_game();
}


int main ()
{
  t_game new_game;

  g_game = &new_game;
  if (init_game() < 0)
    return error();

  if (launch_menu() != -1)
    launch_game();


  free_menu();
  SDL_DestroyWindow(g_game->window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
