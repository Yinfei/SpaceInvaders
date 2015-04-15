#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "../main/prototypes.h"
#include <stdio.h>

void init_player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    g_game->player.action_list[i] = NULL;

  g_game->player.action_list[32]  = &player_fire;
  g_game->player.action_list[97]  = &move_player_left;
  g_game->player.action_list[100] = &move_player_right;
  g_game->player.action_list[119] = &move_player_up;
  g_game->player.action_list[115] = &move_player_down;
}

void free_player() {
  /* delete all bullets */
  free_player_bullets();
  /* freeing all textures */
  SDL_DestroyTexture(g_game->player.texture);
  /* SDL_DestroyTexture(g_game->player.bullet_texture); */
}

void init_player() {
  /* setting initial position */
  g_game->player.hitbox.x = 10;
  g_game->player.hitbox.y = 200;
  g_game->player.hitbox.w = 45;
  g_game->player.hitbox.h = 30;
  /* how many pixels will he move every 16ms */
  g_game->player.speed    = 3;
  /* how many times can he be hit */
  g_game->player.hp       = 3;
  /* if ever this time has passed, he can shot again */
  g_game->player.cooldown = 0;
  /* if ever this time has passed, he can take damage again */
  g_game->player.damage_cooldown = 0;
  /* loading player sprite */
  g_game->player.texture = IMG_LoadTexture(g_game->renderer, "assets/images/dubstepcat.png");
  /* Initialize player action list */
  init_player_actions();
  /* initialize player active_actions to 0; */
  init_active_player_actions();
  /* configure bullet list */
  g_game->player.bullet_list = NULL;
  /* putting player on window, ready for next render */
  render_player();
}

void init_active_player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    g_game->player.active_actions[i] = 0;
}

void player_collisions() {
  /* go through enemy bullets */
  t_bullet* current;
  t_bullet* next;

  if (g_game->enemies->bullet_list != NULL)
  {
    current = g_game->enemies->bullet_list;
    while (current != NULL)
    {
      next = get_next_bullet(current);
      if (collision_manager(&current->hitbox, &g_game->player.hitbox) > 0)
      {
        damage_player(1);
        delete_enemy_bullet(current);
      }
      current = next;
    }
  }
  /* go through power ups ? */
}

void player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    if (g_game->player.active_actions[i] == 1 && g_game->player.action_list[i] != NULL)
      g_game->player.action_list[i]();

  /* check for taking damage/power up here ? */
  player_collisions();
  /* parse through bullets */
  player_bullets();
  render_player();
}

void render_player() {
  SDL_Rect rect;

  rect.x = ((SDL_GetTicks() / 50) % 3) * 150;
  rect.y = 0;
  rect.w = 150;
  rect.h = 100;
  SDL_RenderCopy(g_game->renderer, g_game->player.texture, &rect, &g_game->player.hitbox);
}

void add_player_action() {
  if (g_game->event.key.keysym.sym <= 200)
    g_game->player.active_actions[g_game->event.key.keysym.sym] = 1;
}

void remove_player_action() {
  if (g_game->event.key.keysym.sym <= 200)
    g_game->player.active_actions[g_game->event.key.keysym.sym] = 0;
}

int simulate_player_collision() {
  /* parse through landscape, to see if player is allowed to move there */
  t_block* current;

  if (g_game->landscape.block != NULL)
  {
    current = g_game->landscape.block;
    while (current != NULL)
    {
      /* check if out of shot */
      if (collision_manager(&g_game->player.hitbox, &current->hitbox) > 0)
        return 1;
      else
        current = get_next_block(current);
    }
  }
  return 0;
}

void move_player_left() {
  g_game->player.hitbox.x -= g_game->player.speed;

  if (g_game->player.hitbox.x < 0)
    g_game->player.hitbox.x += g_game->player.speed;
  else if (simulate_player_collision() > 0)
    g_game->player.hitbox.x += g_game->player.speed;
}

void move_player_right() {
  g_game->player.hitbox.x += g_game->player.speed;

  if (g_game->player.hitbox.x + g_game->player.hitbox.w > g_window_width)
    g_game->player.hitbox.x -= g_game->player.speed;
  else if (simulate_player_collision() > 0)
    g_game->player.hitbox.x -= g_game->player.speed;
}

void move_player_up() {
  g_game->player.hitbox.y -= g_game->player.speed;

  if (g_game->player.hitbox.y < 0)
    g_game->player.hitbox.y += g_game->player.speed;
  else if (simulate_player_collision() > 0)
    g_game->player.hitbox.y += g_game->player.speed;
}

void move_player_down() {
  g_game->player.hitbox.y += g_game->player.speed;

  if (g_game->player.hitbox.y + g_game->player.hitbox.h > g_window_height)
    g_game->player.hitbox.y -= g_game->player.speed;
  else if (simulate_player_collision() > 0)
    g_game->player.hitbox.y -= g_game->player.speed;
}

void player_fire() {
  t_bullet* bullet;

  if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->player.cooldown) == 1)
  {
    g_game->player.cooldown = SDL_GetTicks() + 300;
    /* setting bullet details */
    bullet = malloc(sizeof(t_bullet));
    bullet->hitbox.x = g_game->player.hitbox.x + g_game->player.hitbox.w;
    bullet->hitbox.y = g_game->player.hitbox.y + (g_game->player.hitbox.h / 2);
    bullet->hitbox.w = 3;
    bullet->hitbox.h = 3;
    /* setting bullet vector (vector = speed and direction) */
    bullet->x = 5;
    bullet->y = 0;
    bullet->prev = NULL;
    /* checking if bullet list is empty */
    if (g_game->player.bullet_list != NULL)
    {
      bullet->next = g_game->player.bullet_list;
      g_game->player.bullet_list->prev = bullet;
    }
    else
      bullet->next = NULL;
    /* setting start of bullet list to current bullet */
    g_game->player.bullet_list = bullet;
  }
}

int damage_player(int i) {
  if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->player.damage_cooldown) == 1)
  {
    g_game->player.hp -= i;
    g_game->player.damage_cooldown = SDL_GetTicks() + 500;
    return 1;
  }
  else
    return 0;
}
