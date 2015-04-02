#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

int eventSwitcher() {
  /* clear screen */
  clearWindow(game);

  /* checking if player quits game */
  if (SDL_HasEvent(SDL_QUIT) || game->event.type == SDL_QUIT)
    return -1;

  /* call to function to add/remove player actions */
  if (game->event.type == SDL_KEYDOWN)
    addPlayerAction(game);
  else if (game->event.type == SDL_KEYUP)
    removePlayerAction(game);

  /* going through each performable action */
  parsePlayerActions(game);

  drawPlayer(game);

  /* parse through bullets */
  manageBulletList(game);

  /* check player actions. {powerup, takeDamage, die} */
  /* check enemy actions. {move, shoot, die} */
  /* check game actions. {animate background, change music, powerUps} */
  return 0;
}

int error() {
  printf("some sort of error message game->error\n");
  return -1;
}
