#include "../prototypes.h"

void input_player_name(char* name) {
  int running;
  int selected;

  g_game->highscores->writer->box.w = 100;
  g_game->highscores->writer->box.h = 50;
  g_game->highscores->writer->box.x = g_window_width / 2 - g_game->highscores->writer->box.w / 2;
  g_game->highscores->writer->box.y = g_window_height / 2 - g_game->highscores->writer->box.h / 2;
  running = 1;
  selected = 0;
  strcpy(name, "AAA");
  while(running > 0){
    if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->timer) == 1)
    {
      g_game->timer = SDL_GetTicks() + 16;
      running = highscore_event_switcher(&selected, name);
      render_window();
    }
    else
      SDL_Delay(2);
  }
}

void render_name_input_screen(int* selected, char* name) {
  SDL_Surface* surface;
  SDL_Texture* texture;
  SDL_Color color = {123,12,125,255};
  char tmp[4];
  int i;

  surface = TTF_RenderText_Blended(g_game->highscores->writer->font, name, g_game->highscores->writer->color);
  texture = SDL_CreateTextureFromSurface(g_game->renderer, surface);
  SDL_RenderCopy(g_game->renderer, texture, NULL, &g_game->highscores->writer->box);

  strcpy(tmp, name);
  for (i = 0; i < 3; i++)
    if (i != *selected)
      tmp[i] = ' ';
  surface = TTF_RenderText_Blended(g_game->highscores->writer->font, tmp, color);
  texture = SDL_CreateTextureFromSurface(g_game->renderer, surface);
  SDL_RenderCopy(g_game->renderer, texture, NULL, &g_game->highscores->writer->box);
}

void add_player_highscore() {
  int i;
  int j;
  char name[4];

  j = -1;
  for (i = 0; i < 3; i++)
    if (g_game->highscores->score[i]->score < g_game->score)
    {
      j = i;
      break;
    }
  if (j > -1)
  {
    free(g_game->highscores->score[2]);
    for (i = 1; i >= j; i--)
      g_game->highscores->score[i + 1] = g_game->highscores->score[i];
    input_player_name(name);
    add_highscore(name, g_game->score, j);
  }
}

void edit_selected_char(int* selected, char* name) {
  if (g_game->event.key.keysym.sym == SDLK_UP && name[*selected] < 90)
    name[*selected]++;
  else if (g_game->event.key.keysym.sym == SDLK_DOWN && name[*selected] > 65)
    name[*selected]--;
}

void switch_selected_char(int* selected) {
  if (g_game->event.key.keysym.sym == SDLK_RIGHT && *selected < 2)
    *selected = *selected + 1;
  else if (g_game->event.key.keysym.sym == SDLK_LEFT && *selected > 0)
    *selected = *selected - 1;
}
