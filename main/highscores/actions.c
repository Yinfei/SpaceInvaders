#include "../prototypes.h"

int highscores() {
  render_highscores();
  loop_highscores();
  return 1;
}

int loop_highscores() {
  while(1)
  {
    while (SDL_PollEvent(&g_game->event))
    {
      if (g_game->event.type == SDL_QUIT)
      {
        g_game->running = 0;
        return -1;
      }
      else if (g_game->event.type == SDL_KEYDOWN)
        if (g_game->event.key.keysym.sym == 32)
          return 0;
    }
  }
}

void add_highscore(char* name, int i, int index) {
  t_score* scorebox;

  scorebox = malloc(sizeof(t_score));
  strcpy(scorebox->name, name);
  scorebox->score = i;
  g_game->highscores->score[index] = scorebox;
}

void decode_highscore_format(char* str, int index) {
  char name[4];
  char score[10];
  unsigned long i;

  strncat(name, str, 3);
  for (i = 4; i < strlen(str) - 2; i++)
    score[i - 4] = str[i];
  add_highscore(name, atoi(score), index);
}

void export_highscore_file() {
  FILE* file;
  int i;
  char name[4];
  int score;

  strcpy(name, "");
  file = fopen("assets/datas/highscores.csv", "w");
  for (i = 0; i < 3; i++)
  {
    score = g_game->highscores->score[i]->score;
    strcat(name, g_game->highscores->score[i]->name);
    fprintf(file, "%s;%d;\n", name, score);
    strcpy(name, "");
  }
  fclose(file);
}







