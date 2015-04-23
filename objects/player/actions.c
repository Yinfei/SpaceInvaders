#include "../../main/prototypes.h"

void init_player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    g_game->player->action_list[i] = NULL;

  g_game->player->action_list[32]  = &player_fire;
  g_game->player->action_list[97]  = &move_player_left;
  g_game->player->action_list[100] = &move_player_right;
  g_game->player->action_list[119] = &move_player_up;
  g_game->player->action_list[115] = &move_player_down;
  g_game->player->action_list[108] = &set_bullet_direction_down;
  g_game->player->action_list[111] = &set_bullet_direction_up;
}

void init_active_player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    g_game->player->active_actions[i] = 0;
}

void add_player_action() {
  if (g_game->event.key.keysym.sym <= 200)
    g_game->player->active_actions[g_game->event.key.keysym.sym] = 1;
}

void remove_player_action() {
  if (g_game->event.key.keysym.sym <= 200)
    g_game->player->active_actions[g_game->event.key.keysym.sym] = 0;
  if (g_game->event.key.keysym.sym == 108 || g_game->event.key.keysym.sym == 112)
    reset_bullet_direction();
}

void player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    if (g_game->player->active_actions[i] == 1 && g_game->player->action_list[i] != NULL)
      g_game->player->action_list[i]();

  player_collisions();
  element_actions(&g_game->player->bullet_list);
  render_player();
}
