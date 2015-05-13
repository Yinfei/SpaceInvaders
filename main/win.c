#include "prototypes.h"

void render_win_screen() {
  render_shaded_background();
  render_win_text();
  render_window();
  loop_gameover();
}

int loop_win_screen() {
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

void render_win_text() {
  t_writer writer;
  SDL_Color color = {255,255,255,255};
  SDL_Texture* texture;
  SDL_Surface* surface;
  char str[80];

  writer.font = TTF_OpenFont("assets/fonts/roboto.ttf", 10);
  writer.box.w = 500;
  writer.box.h = 50;
  writer.box.x = g_window_width/2 - writer.box.w/2;
  writer.box.y = 100;
  strcpy(str, "Congratulations ! you Won !");
  surface = TTF_RenderText_Blended(writer.font, str, color);
  texture = SDL_CreateTextureFromSurface(g_game->renderer, surface);
  SDL_RenderCopy(g_game->renderer, texture, NULL, &writer.box);
  TTF_CloseFont(writer.font);
}
