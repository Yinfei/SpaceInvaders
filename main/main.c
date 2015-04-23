#include "prototypes.h"

int main ()
{
  t_game new_game;

  g_game = &new_game;
  if (init_game() < 0)
    return error();

  launcher_loop();
  free_menu();
  SDL_DestroyWindow(g_game->window);
  SDL_Quit();
  return EXIT_SUCCESS;
}
