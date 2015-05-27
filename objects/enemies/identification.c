#include "../../main/prototypes.h"

void init_enemies_names() {
  g_game->enemies->names[0] = "Johnny";
  g_game->enemies->names[1] = "Bobby";
  g_game->enemies->names[2] = "Fatty";
  g_game->enemies->names[9] = "Edwardo";
}

char* enemy_name(int type) {
  if (type > -1)
    return g_game->enemies->names[type];
  else
    return "the landscape";
}

