#include "prototypes.h"

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

void init_menu_textures() {
  int i;

  for (i = 0; i < 6; i++)
    g_game->menu->textures[i] = NULL;

  g_game->menu->textures[0] = IMG_LoadTexture(g_game->renderer, "assets/images/mid.png");
  g_game->menu->textures[1] = IMG_LoadTexture(g_game->renderer, "assets/images/mid.png");
  g_game->menu->textures[2] = IMG_LoadTexture(g_game->renderer, "assets/images/mid.png");
  g_game->menu->textures[3] = IMG_LoadTexture(g_game->renderer, "assets/images/far.png");
  g_game->menu->textures[4] = IMG_LoadTexture(g_game->renderer, "assets/images/far.png");
  g_game->menu->textures[5] = IMG_LoadTexture(g_game->renderer, "assets/images/far.png");
}

void free_menu_textures() {
  int i;

  for (i = 0; i < 6; i++)
    if (g_game->menu->textures[i] != NULL)
      SDL_DestroyTexture(g_game->menu->textures[i]);
}

void render_menu() {
  /* verif if selected */
  int i;

  for (i = 0; i < 6; i++)
    if (i != g_game->menu->selected)
      SDL_RenderCopy(g_game->renderer, g_game->menu->textures[i], NULL, &g_game->menu->buttons[i]);
}

int init_menu() {
  t_menu* menu;
  int i;

  menu = malloc(sizeof(t_menu));
  g_game->menu = menu;

  for(i = 0; i < 6; i++)
    create_menu_button(i);

  init_menu_textures();
  menu->selected = 3;

  return 0;
}

void free_menu() {
  free_menu_textures();
  free(g_game->menu);
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
