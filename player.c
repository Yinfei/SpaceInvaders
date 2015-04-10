#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

void initialize_player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    game->player.action_list[i] = NULL;

  game->player.action_list[32]  = &fire;
  game->player.action_list[97] = &move_player_left;
  game->player.action_list[100] = &move_player_right;
  game->player.action_list[119] = &move_player_up;
  game->player.action_list[115] = &move_player_down;
}

void initialize_player() {
  /* setting initial position */
  game->player.hitbox.x = 10;
  game->player.hitbox.y = 200;
  game->player.hitbox.w = 30;
  game->player.hitbox.h = 30;

  /* how many pixels will he move every 16ms */
  game->player.speed    = 3;
  /* how many times can he be hit */
  game->player.hp       = 3;
  /* if ever this time has passed, he can shot again */
  game->player.cooldown = 0;

  /* Initialize player action list */
  initialize_player_actions();
  /* initialize player active_actions to 0; */
  initialize_active_player_actions();

  /* configure bullet list */
  game->player.bullet_list = NULL;

  /* putting player on window, ready for next render */
  draw_player();
}

void initialize_active_player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    game->player.active_actions[i] = 0;
}

void manage_player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    if (game->player.active_actions[i] == 1 && game->player.action_list[i] != NULL)
      game->player.action_list[i]();


  /* check for taking damage/power up here ? */


  draw_player();
}

void draw_player() {
  /* Set render color to blue (player will be rendered in this color) */
  SDL_SetRenderDrawColor(game->renderer,0,0,255,255);
  /* Render player hitbox */
  SDL_RenderFillRect(game->renderer, &game->player.hitbox);
}

void add_player_action() {
  if (game->event.key.keysym.sym <= 200)
    game->player.active_actions[game->event.key.keysym.sym] = 1;
}

void remove_player_action() {
  if (game->event.key.keysym.sym <= 200)
    game->player.active_actions[game->event.key.keysym.sym] = 0;
}

void move_player_left() {
  if (game->player.hitbox.x - game->player.speed >= 0)
    game->player.hitbox.x -= game->player.speed;
}

void move_player_right() {
  if (game->player.hitbox.x + game->player.hitbox.w + game->player.speed <= 640)
    game->player.hitbox.x += game->player.speed;
}

void move_player_up() {
  if (game->player.hitbox.y - game->player.speed >= 0)
    game->player.hitbox.y -= game->player.speed;
}

void move_player_down() {
  if (game->player.hitbox.y + game->player.hitbox.h + game->player.speed <= 420)
    game->player.hitbox.y += game->player.speed;
}

void fire() {
  bullet_stc* bullet;

  if (SDL_TICKS_PASSED(SDL_GetTicks(), game->player.cooldown) == 1)
  {
    game->player.cooldown = SDL_GetTicks() + 300;
    /* setting bullet details */
    bullet = malloc(sizeof(bullet_stc));
    bullet->hitbox.x = game->player.hitbox.x + game->player.hitbox.w;
    bullet->hitbox.y = game->player.hitbox.y + (game->player.hitbox.h / 2);
    bullet->hitbox.w = 3;
    bullet->hitbox.h = 3;
    bullet->prev = NULL;
    /* checking if bullet list is empty */
    if (game->player.bullet_list != NULL)
    {
      bullet->next = game->player.bullet_list;
      bullet->id   = game->player.bullet_list->id + 1;
      game->player.bullet_list->prev = bullet;
    }
    else
    {
      bullet->next = NULL;
      bullet->id   = 0;
    }
    /* setting start of bullet list to current bullet */
    game->player.bullet_list = bullet;
  }
}

