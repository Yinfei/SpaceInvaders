#include "../main/prototypes.h"

void init_soundboard() {
  int i;

  for (i = 0; i < 10; i++)
    g_game->jukebox.soundboard[i] = NULL;

  /* sound player fire */
  g_game->jukebox.soundboard[0] = Mix_LoadWAV("assets/music/utini.wav");
  /* sound for powerup */
  g_game->jukebox.soundboard[1] = Mix_LoadWAV("assets/music/utini.wav");
  /* sound for power down */
  g_game->jukebox.soundboard[2] = Mix_LoadWAV("assets/music/utini.wav");
  /* player lives up */
  g_game->jukebox.soundboard[3] = Mix_LoadWAV("assets/music/utini.wav");
  /* sound for losing life */
  g_game->jukebox.soundboard[4] = Mix_LoadWAV("assets/music/utini.wav");
  /* sound for enemy dying */
  g_game->jukebox.soundboard[5] = Mix_LoadWAV("assets/music/utini.wav");

}
