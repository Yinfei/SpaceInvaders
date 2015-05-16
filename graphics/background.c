#include "../main/prototypes.h"

int init_background() {
  g_game->background.near.x = 0;
  g_game->background.near.y = 0;
  g_game->background.near.w = 1920;
  g_game->background.near.h = 420;

  g_game->background.mid.x = 0;
  g_game->background.mid.y = 0;
  g_game->background.mid.w = 1280;
  g_game->background.mid.h = 420;

  g_game->background.far.x = 0;
  g_game->background.far.y = 0;
  g_game->background.far.w = 640;
  g_game->background.far.h = 420;

  g_game->background.near_texture = IMG_LoadTexture(g_game->renderer, "assets/images/near.png");
  g_game->background.mid_texture  = IMG_LoadTexture(g_game->renderer, "assets/images/mid.png");
  g_game->background.far_texture  = IMG_LoadTexture(g_game->renderer, "assets/images/far.png");
  g_game->background.shaded       = IMG_LoadTexture(g_game->renderer, "assets/images/black.png");
  return 0;
}

void render_background() {
  SDL_RenderCopy(g_game->renderer, g_game->background.far_texture, NULL, &g_game->background.far);
  SDL_RenderCopy(g_game->renderer, g_game->background.mid_texture, NULL, &g_game->background.mid);
  SDL_RenderCopy(g_game->renderer, g_game->background.near_texture, NULL, &g_game->background.near);
}

void background_actions() {
  if (g_game->background.near.x <= -1280)
    g_game->background.near.x = 0;
  if (g_game->background.mid.x <= -640)
    g_game->background.mid.x = 0;

  g_game->background.near.x -= 2;
  g_game->background.mid.x -= 1;
}

void render_shaded_background() {
  SDL_Rect rec;

  rec.x = 0;
  rec.y = 0;
  rec.w = g_window_width;
  rec.h = g_window_height;
  SDL_RenderCopy(g_game->renderer, g_game->background.shaded, NULL, &rec);
}

void free_background() {
  SDL_DestroyTexture(g_game->background.near_texture);
  SDL_DestroyTexture(g_game->background.mid_texture);
  SDL_DestroyTexture(g_game->background.far_texture);
    SDL_DestroyTexture(g_game->background.shaded);
}
