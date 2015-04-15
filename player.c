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

void free_player() {
  /* delete all bullets */
  free_player_bullets();

  /* freeing all textures */
  SDL_DestroyTexture(game->player.texture);
  /* SDL_DestroyTexture(game->player.bullet_texture); */
}

void initialize_player() {
  /* setting initial position */
  game->player.hitbox.x = 10;
  game->player.hitbox.y = 200;
  game->player.hitbox.w = 45;
  game->player.hitbox.h = 30;

  /* how many pixels will he move every 16ms */
  game->player.speed    = 3;
  /* how many times can he be hit */
  game->player.hp       = 3;
  /* if ever this time has passed, he can shot again */
  game->player.cooldown = 0;
  /* if ever this time has passed, he can take damage again */
  game->player.damage_cooldown = 0;

  /* loading player sprite */
  game->player.texture = IMG_LoadTexture(game->renderer, "img/dubstepcat.png");

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

void manage_player_collisions() {
  /* go through enemy bullets */
  bullet_stc* current;
  bullet_stc* next;

  if (game->enemies->bullet_list != NULL)
  {
    current = game->enemies->bullet_list;
    while (current != NULL)
    {
      next = get_next_bullet(current);
      if (game_collision_manager(&current->hitbox, &game->player.hitbox) > 0)
      {
        player_take_damage(1);
        delete_enemy_bullet(current);
      }
      current = next;
    }
  }

  /* go through power ups ? */
}

void manage_player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    if (game->player.active_actions[i] == 1 && game->player.action_list[i] != NULL)
      game->player.action_list[i]();


  /* check for taking damage/power up here ? */
  manage_player_collisions();

  /* parse through bullets */
  manage_player_bullets();

  draw_player();
}

void draw_player() {
  SDL_Rect rect;
  rect.x = ((SDL_GetTicks() / 50) % 3) * 150;
  rect.y = 0;
  rect.w = 150;
  rect.h = 100;

  SDL_RenderCopy(game->renderer, game->player.texture, &rect, &game->player.hitbox);
}

void add_player_action() {
  if (game->event.key.keysym.sym <= 200)
    game->player.active_actions[game->event.key.keysym.sym] = 1;
}

void remove_player_action() {
  if (game->event.key.keysym.sym <= 200)
    game->player.active_actions[game->event.key.keysym.sym] = 0;
}

int simulate_player_collision() {
  /* parse through landscape, to see if player is allowed to move there */
  block_stc* current;

  if (game->landscape.block != NULL)
  {
    current = game->landscape.block;
    while (current != NULL)
    {
      /* check if out of shot */
      if (game_collision_manager(&game->player.hitbox, &current->hitbox) > 0)
        return 1;
      else
        current = get_next_block(current);
    }
  }
  return 0;
}

void move_player_left() {
  game->player.hitbox.x -= game->player.speed;

  if (game->player.hitbox.x < 0)
    game->player.hitbox.x += game->player.speed;
  else if (simulate_player_collision() > 0)
    game->player.hitbox.x += game->player.speed;
}

void move_player_right() {
  game->player.hitbox.x += game->player.speed;

  if (game->player.hitbox.x + game->player.hitbox.w > GAMEWIDTH)
    game->player.hitbox.x -= game->player.speed;
  else if (simulate_player_collision() > 0)
    game->player.hitbox.x -= game->player.speed;
}

void move_player_up() {
  game->player.hitbox.y -= game->player.speed;

  if (game->player.hitbox.y < 0)
    game->player.hitbox.y += game->player.speed;
  else if (simulate_player_collision() > 0)
    game->player.hitbox.y += game->player.speed;
}

void move_player_down() {
  game->player.hitbox.y += game->player.speed;

  if (game->player.hitbox.y + game->player.hitbox.h > GAMEHEIGHT)
    game->player.hitbox.y -= game->player.speed;
  else if (simulate_player_collision() > 0)
    game->player.hitbox.y -= game->player.speed;
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
    /* setting bullet vector (vector = speed and direction) */
    bullet->x = 5;
    bullet->y = 0;
    bullet->prev = NULL;
    /* checking if bullet list is empty */
    if (game->player.bullet_list != NULL)
    {
      bullet->next = game->player.bullet_list;
      game->player.bullet_list->prev = bullet;
    }
    else
      bullet->next = NULL;
    /* setting start of bullet list to current bullet */
    game->player.bullet_list = bullet;
  }
}

int player_take_damage(int i) {
  if (SDL_TICKS_PASSED(SDL_GetTicks(), game->player.damage_cooldown) == 1)
  {
    game->player.hp -= i;
    game->player.damage_cooldown = SDL_GetTicks() + 500;
    return 1;
  }
  else
    return 0;
}

