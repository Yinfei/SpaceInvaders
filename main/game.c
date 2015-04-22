#include "prototypes.h"

int init_game() {
  g_window_height = 420;
  g_window_width = 640;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0)
    return -1;

  g_game->window = SDL_CreateWindow("DUBSTEP CAT !",100,200,g_window_width,g_window_height,0);
  g_game->renderer = SDL_CreateRenderer(g_game->window,-1,0);
  g_game->score = 0;
  g_game->timer = SDL_GetTicks();
  init_audio();
  init_menu();
  return 0;
}

int init_game_elements() {
  init_score();
  init_element_conditions();
  init_element_collisions();
  init_textures();
  init_background();
  init_player();
  init_landscape();
  init_enemies();
  return 0;
}

int game_state() {
  int state;

  state = 0;
  if (g_game->player->hitbox.x + g_game->player->hitbox.w <= 0)
    state++;
  else if (g_game->player->hp <= 0)
    state++;
  return state;
}

void game_actions() {
  background_actions();
  element_actions(&g_game->landscape->block_list);
  render_score();
  /* manage powerups appearing ? manage powerups moving forwards ... */
  /* changing music ? (for boss ...) */
}

void free_game() {
  if (g_game->player->killed_by != -1)
    printf("killed by %d\n", g_game->player->killed_by);

  free_player();
  free_landscape();
  free_enemies();
  free_background();
  free_audio();
  free_score();
}
