#include "../../main/prototypes.h"

void move_player_left() {
  g_game->player->hitbox.x -= g_game->player->speed;

  if (g_game->player->hitbox.x < 0)
    g_game->player->hitbox.x += g_game->player->speed;
  else if (simulate_player_collision() > 0)
    g_game->player->hitbox.x += g_game->player->speed;
}

void move_player_right() {
  g_game->player->hitbox.x += g_game->player->speed;

  if (g_game->player->hitbox.x + g_game->player->hitbox.w > g_window_width)
    g_game->player->hitbox.x -= g_game->player->speed;
  else if (simulate_player_collision() > 0)
    g_game->player->hitbox.x -= g_game->player->speed;
}

void move_player_up() {
  g_game->player->hitbox.y -= g_game->player->speed;

  if (g_game->player->hitbox.y < 0)
    g_game->player->hitbox.y += g_game->player->speed;
  else if (simulate_player_collision() > 0)
    g_game->player->hitbox.y += g_game->player->speed;
}

void move_player_down() {
  g_game->player->hitbox.y += g_game->player->speed;

  if (g_game->player->hitbox.y + g_game->player->hitbox.h > g_window_height)
    g_game->player->hitbox.y -= g_game->player->speed;
  else if (simulate_player_collision() > 0)
    g_game->player->hitbox.y -= g_game->player->speed;
}

void player_fire() {
  t_element* bullet;

  if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->player->cooldown) == 1)
  {
    g_game->player->cooldown = SDL_GetTicks() + g_game->player->fire_rate;
    bullet = malloc(sizeof(t_element));
    bullet->hitbox.x = g_game->player->hitbox.x + g_game->player->hitbox.w;
    bullet->hitbox.y = g_game->player->hitbox.y + (g_game->player->hitbox.h / 2);
    bullet->hitbox.w = 20;
    bullet->hitbox.h = 7;
    bullet->x = g_game->player->bullet_speed;
    bullet->y = g_game->player->bullet_speed * player_bullet_direction();
    bullet->prev = NULL;
    bullet->type = 20;
    add_element(&g_game->player->bullet_list, bullet);
    Mix_PlayChannel(1, g_game->jukebox.soundboard[0], 0);
  }
}
