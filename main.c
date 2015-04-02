#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

/* global game_stc* game defined in space.h */

int main ()
{
  /* creating a game structure */
  game_stc newGame;
  /* initializing global game "object" */
  game = &newGame;
  /* initializing game */
  if (initializeGame(game) < 0)
    return error(game);
  /* starting main game loop */
  while (game->running)
  {
    /* catching events */
    SDL_PollEvent(&game->event);
    /* check if 16 ms have gone by since last render */
    if (SDL_TICKS_PASSED(SDL_GetTicks(), game->timer) == 1)
    {
      /* setting next game render time */
      game->timer = SDL_GetTicks() + 16;
      /* check if player quits game, parse game and player actions */
      if (eventSwitcher(game) != -1)
        /* render game screen */
        renderScreen(game);
      else
        /* exit */
        break;
    }
    else
      /* waiting 16 ms (to make sure we are around 60 FPS) */
      SDL_Delay(16);
  }
  /* clean up game, and exit SDL */
  endGame(game);
  /* quit */
  return EXIT_SUCCESS;
}
