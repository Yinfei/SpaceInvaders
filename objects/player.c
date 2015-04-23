#include "../main/prototypes.h"

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
  player->cooldown = 0;
  player->damage_cooldown = 0;
  player->killed_by = -1;
  player->won = 0;
  player->bullet_direction = 0;
  player->texture = IMG_LoadTexture(g_game->renderer, "assets/images/dubstepcat.png");
  init_player_actions();
  init_active_player_actions();
  player->bullet_list = NULL;
  render_player();
}

void free_player() {
  free_element_list(&g_game->player->bullet_list);
  SDL_DestroyTexture(g_game->player->texture);
  free(g_game->player);
}
