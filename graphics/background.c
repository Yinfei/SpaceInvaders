#include "../main/prototypes.h"

int init_background() {
  SDL_Rect rec;

  rec.x = 0;
  rec.y = 0;
  rec.w = g_window_width;
  rec.h = g_window_height;
  g_game->background.sky = &rec;
  g_game->background.cooldown = 0;
  g_game->background.blue = 160;
  g_game->background.offset = 150;
  g_game->background.current_offset = 0;
  g_game->background.stars  = IMG_LoadTexture(g_game->renderer, "assets/images/stars.png");
  g_game->background.shaded = IMG_LoadTexture(g_game->renderer, "assets/images/black.png");
  return 0;
}

void render_background() {
  SDL_Rect rec;
  int i;
  int j;
  int offset;

  offset = g_game->background.current_offset;
  rec.w = g_game->background.offset;
  rec.h = g_game->background.offset;
  for (i = offset; i <= g_window_width + rec.w; i += rec.w)
    for (j = 0; j <= g_window_height + rec.h; j += rec.h)
    {
      rec.x = i;
      rec.y = j;
      SDL_RenderCopy(g_game->renderer, g_game->background.stars, NULL, &rec);
    }

  SDL_SetRenderDrawColor(g_game->renderer, 0, 25, g_game->background.blue, 255);
  SDL_RenderFillRect(g_game->renderer, g_game->background.sky);
}

void background_actions() {
  if (g_game->background.current_offset <= (-1) * g_game->background.offset)
    g_game->background.current_offset = 0;
  g_game->background.current_offset = g_game->background.current_offset - 1;

  if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->background.cooldown) == 1
   && g_game->background.blue > 0)
  {
    g_game->background.blue -= 1;
    g_game->background.cooldown = SDL_GetTicks() + 100;
  }
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
  SDL_DestroyTexture(g_game->background.stars);
  SDL_DestroyTexture(g_game->background.shaded);
}
