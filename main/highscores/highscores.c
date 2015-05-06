#include "../prototypes.h"

void init_highscores_list() {

}

int init_highscores() {
  t_highscores* highscores;
  SDL_Color color = {12,136,125,255};

  highscores = malloc(sizeof(t_highscores));

  /* init score list */

  highscores->writer = malloc(sizeof(t_writer));
  highscores->writer->font = TTF_OpenFont("assets/fonts/roboto.ttf", 30);
  highscores->writer->box.w = 400;
  highscores->writer->box.h = 25;
  highscores->writer->box.x = g_window_width - highscores->writer->box.w;
  highscores->writer->box.y = 200;
  highscores->writer->color = color;
  g_game->highscores = highscores;
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

void add_highscore() {

}

void render_highscores() {
  SDL_Surface* surface;
  SDL_Texture* texture;
  char* str;

  clear_window();



  /* for HERE ! */
  str = "highscores";
  surface = TTF_RenderText_Blended(g_game->highscores->writer->font, str, g_game->highscores->writer->color);
  texture = SDL_CreateTextureFromSurface(g_game->renderer, surface);
  SDL_RenderCopy(g_game->renderer, texture, NULL, &g_game->highscores->writer->box);



  render_window();
}

void free_highscores() {
  TTF_CloseFont(g_game->highscores->writer->font);
  free(g_game->highscores->writer);
  /* free score list */

  free(g_game->highscores);
}
