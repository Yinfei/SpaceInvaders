#include "../prototypes.h"

int loop_gameover() {
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

void render_gameover_text() {
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
  strcpy(str, "you where killed by ");
  strcat(str, enemy_name(g_game->player->killed_by));
  surface = TTF_RenderText_Blended(writer.font, str, color);
  texture = SDL_CreateTextureFromSurface(g_game->renderer, surface);
  SDL_RenderCopy(g_game->renderer, texture, NULL, &writer.box);
  TTF_CloseFont(writer.font);
}

void render_gameover_background() {
  SDL_Texture* texture;
  SDL_Rect rec;

  rec.x = 0;
  rec.y = 0;
  rec.w = g_window_width;
  rec.h = g_window_height;
  texture = IMG_LoadTexture(g_game->renderer, "assets/images/black.png");
  SDL_RenderCopy(g_game->renderer, texture, NULL, &rec);
  SDL_DestroyTexture(texture);
}

void render_killer() {
  SDL_Rect rec;

  if (g_game->player->killed_by > -1)
  {
    rec.w = 50;
    rec.h = 50;
    rec.x = g_window_width/2 - rec.w/2;
    rec.y = 250;
    SDL_RenderCopy(g_game->renderer, g_game->textures[g_game->player->killed_by], NULL, &rec);
  }
}

void render_gameover() {
  render_gameover_background();
  render_gameover_text();
  render_killer();
  render_window();
  loop_gameover();
}
