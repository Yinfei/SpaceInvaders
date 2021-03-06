#include "../prototypes.h"

int game_state() {
  int state;

  state = 0;
  if (g_game->player->hitbox.x + g_game->player->hitbox.w <= 0)
    state++;
  else if (g_game->player->hp <= 0 || g_game->player->won == 1)
    state++;
  else if (strcmp(SDL_GetError(), "") != 0
    && strcmp(SDL_GetError(), "Unknown touch device") != 0
    && strcmp(SDL_GetError(), "ERROR: NumPoints = 0\n") != 0)
  {
    g_game->running = 0;
    printf("%s\n", SDL_GetError());
    state++;
  }
  return state;
}

void game_actions() {
  background_actions();
  element_actions(&g_game->landscape->block_list);
  render_score();
  element_actions(&g_game->bonus->bonus_list);
}

int launch_game() {
  init_game_elements();
  Mix_PlayMusic(g_game->jukebox.music[1], -1);
  while (1)
  {
    if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->timer) == 1)
    {
      g_game->timer = SDL_GetTicks() + 16;
      if (event_switcher() != -1)
        render_window();
      else
        break;
    }
    else
      SDL_Delay(2);
  }
  free_game();
  return 1;
}
