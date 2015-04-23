#include "../prototypes.h"

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

int launch_game() {
  init_game_elements();
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
