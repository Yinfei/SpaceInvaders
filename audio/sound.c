#include "../main/prototypes.h"

void init_soundboard() {
  int i;

  for (i = 0; i < 10; i++)
    g_game->jukebox.soundboard[i] = NULL;

  g_game->jukebox.soundboard[0] = Mix_LoadWAV("assets/music/test.wav");
}
