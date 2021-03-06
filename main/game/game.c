#include "../prototypes.h"

int init_game() {
  g_window_height = 400;
  g_window_width = 640;

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_EVENTS) < 0)
    return -1;

  g_game->window = SDL_CreateWindow("Space Invaders !",100,200,g_window_width,g_window_height,0);
  g_game->renderer = SDL_CreateRenderer(g_game->window,-1,0);
  g_game->running = 1;
  g_game->timer = SDL_GetTicks();
  init_audio();
  init_menu();
  TTF_Init();
  init_highscores();
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
  init_bonus();
  init_enemies();
  return 0;
}

void free_game() {
  Mix_PlayMusic(g_game->jukebox.music[0], -1);
  if (g_game->running != 0)
  {
    if (g_game->player->won == 0)
      render_gameover();
    else
    {
      render_win_screen();
      g_game->score += g_game->player->hp * 15;
    }
    add_player_highscore();
  }
  free_player();
  free_landscape();
  free_enemies();
  free_background();
  free_score();
  free_bonus();
}
