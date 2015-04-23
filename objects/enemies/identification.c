#include "../../main/prototypes.h"

char* enemy_name(int type) {
  if (type > -1)
    return g_game->enemies->names[type];
  else
    return "the landscape";
}

