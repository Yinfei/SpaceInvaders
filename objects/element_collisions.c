#include "../main/prototypes.h"

void init_element_collisions() {
  int i;

  for (i = 0; i < 30; i++)
    g_game->element_collisions[i] = NULL;

  g_game->element_collisions[0] = &enemy_collision;
  g_game->element_collisions[10] = &landscape_collision;
  g_game->element_collisions[11] = &landscape_collision;
  g_game->element_collisions[12] = &landscape_collision;
}

int element_collisions(t_element* element) {
  int collision;

  collision = 0;
  if (g_game->element_collisions[element->type] != NULL)
    collision += g_game->element_collisions[element->type](element);

  return collision;
}
