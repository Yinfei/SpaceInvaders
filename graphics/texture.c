#include "../main/prototypes.h"

void init_textures() {
  int i;

  for (i = 0; i < 40; i++)
    g_game->textures[i] = NULL;

  g_game->textures[0]  = IMG_LoadTexture(g_game->renderer, "assets/images/enemy1.png");
  g_game->textures[1]  = IMG_LoadTexture(g_game->renderer, "assets/images/enemy2.png");
  g_game->textures[2]  = IMG_LoadTexture(g_game->renderer, "assets/images/enemy3.png");
  g_game->textures[9]  = IMG_LoadTexture(g_game->renderer, "assets/images/boss.png");
  g_game->textures[10] = IMG_LoadTexture(g_game->renderer, "assets/images/block1.png");
  g_game->textures[11] = IMG_LoadTexture(g_game->renderer, "assets/images/block2.png");
  g_game->textures[12] = IMG_LoadTexture(g_game->renderer, "assets/images/block3.png");
  g_game->textures[13] = IMG_LoadTexture(g_game->renderer, "assets/images/explosion.png");
  g_game->textures[14] = IMG_LoadTexture(g_game->renderer, "assets/images/boss_block.png");
  g_game->textures[20] = IMG_LoadTexture(g_game->renderer, "assets/images/player_bullet.png");
  g_game->textures[21] = IMG_LoadTexture(g_game->renderer, "assets/images/enemy_bullet.png");
  g_game->textures[22] = IMG_LoadTexture(g_game->renderer, "assets/images/boss_bullet.png");
  g_game->textures[31] = IMG_LoadTexture(g_game->renderer, "assets/images/speed_up.png");
  g_game->textures[32] = IMG_LoadTexture(g_game->renderer, "assets/images/speed_down.png");
  g_game->textures[33] = IMG_LoadTexture(g_game->renderer, "assets/images/fire_rate_up.png");
  g_game->textures[34] = IMG_LoadTexture(g_game->renderer, "assets/images/fire_rate_down.png");
  g_game->textures[35] = IMG_LoadTexture(g_game->renderer, "assets/images/life.png");
  g_game->textures[36] = IMG_LoadTexture(g_game->renderer, "assets/images/bullet_speed_up.png");
  g_game->textures[37] = IMG_LoadTexture(g_game->renderer, "assets/images/bullet_speed_down.png");
}

void free_textures() {
  int i;

  for (i = 0; i < 40; i++)
    if (g_game->textures[i] != NULL)
      SDL_DestroyTexture(g_game->textures[i]);
}
