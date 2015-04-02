#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>



void initializePlayer() {
  /* setting initial position */
  game->player.hitbox.x = 310;
  game->player.hitbox.y = 380;
  game->player.hitbox.w = 30;
  game->player.hitbox.h = 30;

  /* how many pixels will he move every 16ms */
  game->player.speed    = 3;
  /* how many times can he be hit */
  game->player.hp       = 3;
  /* if ever this time has passed, he can shot again */
  game->player.cooldown = 0;

  /* Initialize player action list */
  game->player.actionList[32]  = &fire;
  game->player.actionList[113] = &movePlayerLeft;
  game->player.actionList[119] = &movePlayerRight;

  /* initialize player activeActions to 0; */
  initializeActiveActions();

  /* configure bullet; */
  game->player.bulletList = NULL;

  /* putting player on window, ready for next render */
  drawPlayer();
}

void initializeActiveActions() {
  int i;

  for (i = 0; i < 200; i++)
    game->player.activeActions[i] = 0;
}

void parsePlayerActions() {
  int i;

  for (i = 0; i < 200; i++)
    if (game->player.activeActions[i] == 1)
      game->player.actionList[i]();
}

void drawPlayer() {
  /* Set render color to blue (player will be rendered in this color) */
  SDL_SetRenderDrawColor(game->renderer,0,0,255,255);
  /* Render player hitbox */
  SDL_RenderFillRect(game->renderer, &game->player.hitbox);
}

void addPlayerAction() {
  /* only doing a few, because fuck you for the moment */
  if (game->event.key.keysym.sym == 32 || game->event.key.keysym.sym == 113 || game->event.key.keysym.sym == 119)
    game->player.activeActions[game->event.key.keysym.sym] = 1;
}

void removePlayerAction() {
  /* only doing a few, because fuck you for the moment */
  if (game->event.key.keysym.sym == 32 || game->event.key.keysym.sym == 113 || game->event.key.keysym.sym == 119)
    game->player.activeActions[game->event.key.keysym.sym] = 0;
}

void movePlayerLeft() {
  if (game->player.hitbox.x - game->player.speed >= 0)
  {
    game->player.hitbox.x -= game->player.speed;

    /* move background; */
    game->background.mid.x -= 1;
    game->background.near.x -= 2;
  }
}

void movePlayerRight() {
  if (game->player.hitbox.x + game->player.hitbox.w + game->player.speed <= 640)
  {
    game->player.hitbox.x += game->player.speed;

    /* move background; */
    game->background.mid.x += 1;
    game->background.near.x += 2;
  }
}

void fire() {
  bullet_stc* bullet;

  if (SDL_TICKS_PASSED(SDL_GetTicks(), game->player.cooldown) == 1)
  {
    game->player.cooldown = SDL_GetTicks() + 400;

    /* setting bullet details */
    bullet = malloc(sizeof(bullet_stc));
    bullet->hitbox.x = game->player.hitbox.x + (game->player.hitbox.w / 2);
    bullet->hitbox.y = game->player.hitbox.y;
    bullet->hitbox.w = 3;
    bullet->hitbox.h = 3;

    /* checking if bullet list is empty */
    if (game->player.bulletList != NULL)
      bullet->next = game->player.bulletList;
    else
      bullet->next = NULL;

    /* setting start of bullet list to current bullet */
    game->player.bulletList = bullet;
  }
}

