#include "../main/prototypes.h"

void init_soundboard() {
  int i;

  for (i = 0; i < 10; i++)
    g_game->jukebox.soundboard[i] = NULL;

  g_game->jukebox.soundboard[0] = Mix_LoadWAV("assets/music/player_fire.wav");
  g_game->jukebox.soundboard[1] = Mix_LoadWAV("assets/music/power_up.wav");
  g_game->jukebox.soundboard[2] = Mix_LoadWAV("assets/music/power_down.wav");
  g_game->jukebox.soundboard[3] = Mix_LoadWAV("assets/music/utini.wav");
  g_game->jukebox.soundboard[4] = Mix_LoadWAV("assets/music/tut.wav");
  g_game->jukebox.soundboard[5] = Mix_LoadWAV("assets/music/enemy_killed.wav");
  g_game->jukebox.soundboard[6] = Mix_LoadWAV("assets/music/fatality.wav");
  Mix_VolumeChunk(g_game->jukebox.soundboard[0], 30);
  Mix_VolumeChunk(g_game->jukebox.soundboard[5], 50);
}
