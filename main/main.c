#include "prototypes.h"

int main ()
{
  t_game new_game;

  g_game = &new_game;
  if (init_game() < 0)
    return error();

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
  return EXIT_SUCCESS;
}
