#include "../prototypes.h"

void init_highscores_list() {
  int i;

  for (i = 0; i < 3; i++)
    add_highscore("CAT", 10 * i, i);
}

int init_highscores() {
  t_highscores* highscores;
  SDL_Color color = {12,136,125,255};

  highscores = malloc(sizeof(t_highscores));
  highscores->writer = malloc(sizeof(t_writer));
  highscores->writer->font = TTF_OpenFont("assets/fonts/roboto.ttf", 50);
  highscores->writer->box.w = 150;
  highscores->writer->box.h = 30;
  highscores->writer->box.x = g_window_width / 2 - highscores->writer->box.w / 2;
  highscores->writer->box.y = 100;
  highscores->writer->color = color;
  g_game->highscores = highscores;
  init_highscores_list();
  return 1;
}

int loop_highscores() {
  while(1)
  {
    while (SDL_PollEvent(&g_game->event))
    {
      if (g_game->event.type == SDL_QUIT)
      {
        g_game->running = 0;
        return -1;
      }
      else if (g_game->event.type == SDL_KEYDOWN)
        if (g_game->event.key.keysym.sym == 32)
          return 0;
    }
  }
}

int highscores() {
  init_highscores();
  render_highscores();
  loop_highscores();
  free_highscores();

  return 1;
}

int is_highscore() {
  return 1;
}

void add_highscore(char* name, int i, int index) {
  t_score* scorebox;

  scorebox = malloc(sizeof(t_score));
  strcpy(scorebox->name, name);
  scorebox->score = i;
  g_game->highscores->score[index] = scorebox;
}

void render_highscores() {
  SDL_Surface* surface;
  SDL_Texture* texture;
  char str[80];
  char tmp[80];
  int i;

  clear_window();

  for (i = 0; i < 3; i++)
  {
    strcpy(str, "");
    sprintf(tmp, "%d", g_game->highscores->score[i]->score);
    strcat(str, g_game->highscores->score[i]->name);
    strcat(str, "           ");
    strcat(str, tmp);
    surface = TTF_RenderText_Blended(g_game->highscores->writer->font, str, g_game->highscores->writer->color);
    texture = SDL_CreateTextureFromSurface(g_game->renderer, surface);
    g_game->highscores->writer->box.y = i * 100;
    SDL_RenderCopy(g_game->renderer, texture, NULL, &g_game->highscores->writer->box);
  }
  render_window();
}

void free_highscores() {
  int i;
  TTF_CloseFont(g_game->highscores->writer->font);
  free(g_game->highscores->writer);

  /* write score csv */

  for (i = 0; i < 3; i++)
    free(g_game->highscores->score[i]);
  free(g_game->highscores);
}
