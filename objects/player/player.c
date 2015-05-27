#include "../../main/prototypes.h"

void init_player() {
  t_player* player;

  player = malloc(sizeof (t_player));
  g_game->player = player;
  player->hitbox.x = 10;
  player->hitbox.y = 200;
  player->hitbox.w = 45;
  player->hitbox.h = 30;
  player->speed    = 3;
  player->hp       = 3;
  player->fire_rate = 300;
  player->bullet_speed = 5;
  player->cooldown = 0;
  player->damage_cooldown = 0;
  player->killed_by = -1;
  player->won = 0;
  player->bullet_direction = 0;
  player->texture = IMG_LoadTexture(g_game->renderer, "assets/images/player.png");
  init_player_lifebox();
  init_player_actions();
  init_active_player_actions();
  player->bullet_list = NULL;
  render_player();
}

void init_player_lifebox() {
  t_lifebox* lifebox;

  lifebox = malloc(sizeof(t_lifebox));
  lifebox->box.x = 10;
  lifebox->box.y = 10;
  lifebox->box.w = 90;
  lifebox->box.h = 30;
  lifebox->texture = IMG_LoadTexture(g_game->renderer, "assets/images/lives.png");
  g_game->player->lifebox = lifebox;
}

void free_player() {
  free_element_list(&g_game->player->bullet_list);
  SDL_DestroyTexture(g_game->player->texture);
  SDL_DestroyTexture(g_game->player->lifebox->texture);
  free(g_game->player->lifebox);
  free(g_game->player);
}
