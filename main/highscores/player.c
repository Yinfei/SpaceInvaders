#include "../prototypes.h"

void input_player_name(char* name) {
  /* get the name here */


  /* event name input switcher */


  strcpy(name, "AAA");
}

void add_player_highscore() {
  int i;
  int j;
  char name[4];

  j = -1;
  for (i = 0; i < 3; i++)
    if (g_game->highscores->score[i]->score < g_game->score)
    {
      j = i;
      break;
    }

  if (j > -1)
  {
    free(g_game->highscores->score[2]);
    for (i = 1; i >= j; i--)
      g_game->highscores->score[i + 1] = g_game->highscores->score[i];
    input_player_name(name);
    add_highscore(name, g_game->score, j);
  }
}
