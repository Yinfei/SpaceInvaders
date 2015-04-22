#include "../main/prototypes.h"

int init_audio() {
  if(Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) == -1)
  {
     printf("%s", Mix_GetError());
     return -1;
  }

  Mix_AllocateChannels(8);
  init_music();
  init_soundboard();
  Mix_PlayMusic(g_game->jukebox.music[0], -1);
  return 0;
}

void free_audio() {
  int i;

  for (i = 0; i < 3; i++)
    if (g_game->jukebox.music[i] != NULL)
      Mix_FreeMusic(g_game->jukebox.music[i]);

  for (i = 0; i < 10; i++)
    if (g_game->jukebox.soundboard[i] != NULL)
      Mix_FreeChunk(g_game->jukebox.soundboard[i]);

  Mix_CloseAudio();
}
