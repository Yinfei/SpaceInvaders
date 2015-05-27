#include "../../main/prototypes.h"

void init_player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    g_game->player->action_list[i] = NULL;

  g_game->player->action_list[44]  = &player_fire;
  g_game->player->action_list[80]  = &move_player_left;
  g_game->player->action_list[79] = &move_player_right;
  g_game->player->action_list[82] = &move_player_up;
  g_game->player->action_list[81] = &move_player_down;
  g_game->player->action_list[15] = &set_bullet_direction_down;
  g_game->player->action_list[18] = &set_bullet_direction_up;
}

void init_active_player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    g_game->player->active_actions[i] = 0;
}

void add_player_action() {
  if (g_game->event.key.keysym.scancode <= 200)
    g_game->player->active_actions[g_game->event.key.keysym.scancode] = 1;
}

void remove_player_action() {
  if (g_game->event.key.keysym.scancode <= 200)
    g_game->player->active_actions[g_game->event.key.keysym.scancode] = 0;
  if (g_game->event.key.keysym.scancode == 15 || g_game->event.key.keysym.scancode == 18)
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
