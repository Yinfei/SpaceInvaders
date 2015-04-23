#include "../prototypes.h"

int launcher_loop() {
  if (launch_menu() > -1)
  {
    if (g_game->menu->launcher[g_game->menu->selected - 3]() != 0)
      launcher_loop();
    return 1;
  }
  else
    return 0;
}

void create_menu_button(int type) {
  int i;

  if (type <= 2)
    i = type;
  else
    i = type - 3;
  g_game->menu->buttons[type].w = 300;
  g_game->menu->buttons[type].h = 70;
  g_game->menu->buttons[type].x = g_window_width/2 - g_game->menu->buttons[i].w/2;
  g_game->menu->buttons[type].y = (i * (g_game->menu->buttons[i].h + 30)) + 50;
}

void render_choice_screen() {
  int i;

  for (i = 0; i < 6; i++)
    if (i != g_game->menu->selected)
      SDL_RenderCopy(g_game->renderer, g_game->menu->textures[i], NULL, &g_game->menu->buttons[i]);
}

int launch_menu() {
  int i;

  i = 0;
  while(1){
    if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->timer) == 1)
    {
      g_game->timer = SDL_GetTicks() + 16;
      i = menu_event_switcher();
      if (i > 0)
        render_window();
      else
        break;
    }
    else
      SDL_Delay(2);
  }
  return i;
}
