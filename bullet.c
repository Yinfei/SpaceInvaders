#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

void manageBulletList(game_stc* game) {
  bullet_stc* first;
  bullet_stc* current;

  if (game->player.bulletList != NULL)
  {
    /* storing index of first bullet */
    first = game->player.bulletList;

    /* creating value to parsethough */
    current = game->player.bulletList;

    /* parse through each bullet, render each one */
    while (current != NULL)
    {
      moveBullet(current);
      renderBullet(game, current);
      if (current->next != NULL)
        current = current->next;
      else
        current = NULL;
    }

    /* re asign game.bulletList to first index.*/
    game->player.bulletList = first;
  }
}

void moveBullet(bullet_stc* bullet) {
  bullet->hitbox.y -= 3;
}

void renderBullet(game_stc* game, bullet_stc* bullet) {
  /* Set render color to red (bullet will be rendered in this color) */
  SDL_SetRenderDrawColor(game->renderer,255,0,0,255);
  /* Render player hitbox */
  SDL_RenderFillRect(game->renderer, &bullet->hitbox);
}

void freeBulletList(game_stc* game) {
  bullet_stc* current;
  bullet_stc* toFree;

  if (game->player.bulletList != NULL)
  {
    /* creating value to parsethough */
    current = game->player.bulletList;
    toFree  = current;

    /* parse through each bullet, free each one */
    while (current != NULL)
    {
      if (current->next != NULL)
      {
        current = current->next;
        free(toFree);
        toFree = current;
      }
      else
      {
        free(current);
        break;
      }
    }
  }
}
