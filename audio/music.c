#include "../main/prototypes.h"

void init_music() {
  int i;

  for (i = 0; i < 3; i++)
    g_game->jukebox.music[i] = NULL;

  g_game->jukebox.music[0] = Mix_LoadMUS("assets/music/music.wav");
}
