#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "prototypes.h"
#include <stdio.h>

/* global t_game* game defined in prototypes.h */

int main ()
{
  /* creating a game structure */
  t_game new_game;
  /* initializing global game "object" */
  g_game = &new_game;
  /* initializing game */
  if (init_game() < 0)
    return error();
  /* starting main game loop */
  while (g_game->running)
  {
    /* check if 16 ms have gone by since last render */
    if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->timer) == 1)
    {
      /* setting next game render time */
      g_game->timer = SDL_GetTicks() + 16;
      /* check if player quits game, parse game and player actions */
      if (event_switcher() != -1)
        /* render game screen */
        render_window();
      else
        /* exit */
        break;
    }
    else
      /* waiting 16 ms (to make sure we are around 60 FPS) */
      SDL_Delay(16);
  }
  /* clean up game, and exit SDL */
  end_game();
  /* quit */
  return EXIT_SUCCESS;
}
