#include "../../main/prototypes.h"

void alter_speed(t_element* bonus) {
  if (bonus->type == 31)
    {
      g_game->player->speed += 2;
      Mix_PlayChannel(1, g_game->jukebox.soundboard[1], 0);
      g_game->score += 2;
    }
  else if (bonus->type == 32 && g_game->player->speed > 2)
    {
      g_game->player->speed -= 2;
      Mix_PlayChannel(1, g_game->jukebox.soundboard[2], 0);
    }
}

void alter_hp() {
  if (g_game->player->hp < 3)
    g_game->player->hp += 1;
  Mix_PlayChannel(1, g_game->jukebox.soundboard[3], 0);
  g_game->score += 2;
}

void alter_fire(t_element* bonus) {
  if (bonus->type == 33)
  {
    g_game->player->fire_rate -= 100;
    Mix_PlayChannel(1, g_game->jukebox.soundboard[1], 0);
    g_game->score += 2;
  }
  else if (bonus->type == 34 && g_game->player->fire_rate < 400)
  {
    g_game->player->fire_rate += 100;
    Mix_PlayChannel(1, g_game->jukebox.soundboard[2], 0);
  }
}

void alter_bullet_speed(t_element* bonus) {
  if (bonus->type == 36 && g_game->player->bullet_speed < 7)
  {
    g_game->player->bullet_speed += 2;
    Mix_PlayChannel(1, g_game->jukebox.soundboard[1], 0);
    g_game->score += 2;
  }
  else if (bonus->type == 37 && g_game->player->bullet_speed > 3)
  {
    g_game->player->bullet_speed -= 2;
    Mix_PlayChannel(1, g_game->jukebox.soundboard[2], 0);
  }
}
