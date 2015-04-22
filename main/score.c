#include "prototypes.h"

int init_score(){
  t_writer* writer;
  SDL_Color color = {12,36,125,255};

  TTF_Init();
  writer = malloc(sizeof(t_writer));
  writer->font = TTF_OpenFont("assets/fonts/roboto.ttf", 30);
  writer->scorebox.w = 60;
  writer->scorebox.h = 30;
  writer->scorebox.x = g_window_width - writer->scorebox.w;
  writer->scorebox.y = 0;
  g_game->writer = writer;
  g_game->writer->color = &color;
  return 0;
}

void free_score(){
  TTF_CloseFont(g_game->writer->font);
  free(g_game->writer);
  TTF_Quit();
}

void render_score(){
  SDL_Texture* scorebox;
  SDL_Surface* score;
  char str[8];

  sprintf(str, "%d", g_game->score);
  score = TTF_RenderText_Blended(g_game->writer->font, str, *g_game->writer->color);
  scorebox = SDL_CreateTextureFromSurface(g_game->renderer, score);
  SDL_RenderCopy(g_game->renderer, scorebox, NULL, &g_game->writer->scorebox);
}