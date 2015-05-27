#include "prototypes.h"

int init_score(){
  t_writer* writer;
  SDL_Color color = {255,0,51,255};

  g_game->score = 0;
  writer = malloc(sizeof(t_writer));
  writer->font = TTF_OpenFont("assets/fonts/roboto.ttf", 30);
  writer->box.w = 60;
  writer->box.h = 30;
  writer->box.x = g_window_width - writer->box.w - 10;
  writer->box.y = 10;
  g_game->writer = writer;
  g_game->writer->color = color;
  return 0;
}

void free_score(){
  TTF_CloseFont(g_game->writer->font);
  free(g_game->writer);
}

void render_score(){
  SDL_Texture* box;
  SDL_Surface* score;
  char str[16];
  int top_score;
  int i;

  top_score = -1;
  for (i = 2; i >= 0; i--)
    if (g_game->highscores->score[i]->score > g_game->score)
    {
      top_score = g_game->highscores->score[i]->score;
      break;
    }
  if (top_score == -1)
    top_score = g_game->score;

  sprintf(str, "%d / %d", g_game->score, top_score);
  score = TTF_RenderText_Blended(g_game->writer->font, str, g_game->writer->color);
  box = SDL_CreateTextureFromSurface(g_game->renderer, score);
  SDL_RenderCopy(g_game->renderer, box, NULL, &g_game->writer->box);
}
