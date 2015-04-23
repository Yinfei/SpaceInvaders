#include "../prototypes.h"

int init_menu() {
  t_choice_screen* menu;
  int i;

  menu = malloc(sizeof(t_choice_screen));
  g_game->menu = menu;
  for(i = 0; i < 6; i++)
    create_menu_button(i);
  init_menu_textures();
  menu->selected = 3;
  menu->launcher[0] = &launch_game;
  menu->launcher[1] = &highscores;
  menu->launcher[2] = &exit_game;
  return 0;
}

void free_menu() {
  free_menu_textures();
  free_audio();
  free(g_game->menu);
}

void init_menu_textures() {
  int i;

  for (i = 0; i < 6; i++)
    g_game->menu->textures[i] = NULL;
  g_game->menu->textures[0] = IMG_LoadTexture(g_game->renderer, "assets/images/play_selected.png");
  g_game->menu->textures[1] = IMG_LoadTexture(g_game->renderer, "assets/images/highscores_selected.png");
  g_game->menu->textures[2] = IMG_LoadTexture(g_game->renderer, "assets/images/exit_selected.png");
  g_game->menu->textures[3] = IMG_LoadTexture(g_game->renderer, "assets/images/play.png");
  g_game->menu->textures[4] = IMG_LoadTexture(g_game->renderer, "assets/images/highscores.png");
  g_game->menu->textures[5] = IMG_LoadTexture(g_game->renderer, "assets/images/exit.png");
}

void free_menu_textures() {
  int i;

  for (i = 0; i < 6; i++)
    if (g_game->menu->textures[i] != NULL)
      SDL_DestroyTexture(g_game->menu->textures[i]);
}
