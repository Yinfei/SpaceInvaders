#include "../main/prototypes.h"

void init_textures() {
  int i;

  for (i = 0; i < 30; i++)
    g_game->textures[i] = NULL;

  g_game->textures[0]  = IMG_LoadTexture(g_game->renderer, "assets/images/fatcat.png");
  g_game->textures[1]  = IMG_LoadTexture(g_game->renderer, "assets/images/enemy1.png");
  g_game->textures[2]  = IMG_LoadTexture(g_game->renderer, "assets/images/bomb.png");
  g_game->textures[10] = IMG_LoadTexture(g_game->renderer, "assets/images/solid_block.png");
  g_game->textures[11] = IMG_LoadTexture(g_game->renderer, "assets/images/solid_block2.png");
  g_game->textures[12] = IMG_LoadTexture(g_game->renderer, "assets/images/block.png");
  g_game->textures[20] = IMG_LoadTexture(g_game->renderer, "assets/images/player_bullet.png");
  g_game->textures[21] = IMG_LoadTexture(g_game->renderer, "assets/images/enemy_bullet.png");
}

void free_textures() {
  int i;

  for (i = 0; i < 30; i++)
    if (g_game->textures[i] != NULL)
      SDL_DestroyTexture(g_game->textures[i]);
}
