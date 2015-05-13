#include "../prototypes.h"

int init_highscores() {
  t_highscores* highscores;
  SDL_Color color = {12,136,125,255};

  highscores = malloc(sizeof(t_highscores));
  highscores->writer = malloc(sizeof(t_writer));
  highscores->writer->font = TTF_OpenFont("assets/fonts/lekton.ttf", 50);
  highscores->writer->box.w = 150;
  highscores->writer->box.h = 30;
  highscores->writer->box.x = g_window_width / 2 - highscores->writer->box.w / 2;
  highscores->writer->box.y = 100;
  highscores->writer->color = color;
  g_game->highscores = highscores;
  init_highscores_list();
  return 1;
}

int init_highscores_list() {
  FILE* file;
  char str[40];
  int i;

  i = 0;
  file = fopen("assets/datas/highscores.csv", "r+");
  if (file == NULL)
  {
    printf("did not open\n");
    return -1;
  }
  while (fgets(str, 40, file) != NULL && i < 3)
  {
    decode_highscore_format(str, i);
    i++;
  }
  fclose(file);
  return 0;
}

void render_highscores() {
  SDL_Surface* surface;
  SDL_Texture* texture;
  char str[80];
  char tmp[80];
  int i;

  g_game->highscores->writer->box.w = 150;
  g_game->highscores->writer->box.h = 30;
  g_game->highscores->writer->box.x = g_window_width / 2 - (150 / 2);
  g_game->highscores->writer->box.y = 100;
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

  export_highscore_file();
  TTF_CloseFont(g_game->highscores->writer->font);
  free(g_game->highscores->writer);
  for (i = 0; i < 3; i++)
    free(g_game->highscores->score[i]);
  free(g_game->highscores);
}
