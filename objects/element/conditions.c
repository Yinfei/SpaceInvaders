#include "../../main/prototypes.h"

void init_element_conditions() {
  int i;

  for (i = 0; i < 30; i++)
    g_game->element_conditions[i] = NULL;

  g_game->element_conditions[10] = &off_window_left;
  g_game->element_conditions[11] = &off_window_left;
  g_game->element_conditions[12] = &off_window_left;
  g_game->element_conditions[20] = &off_window_right;
  g_game->element_conditions[21] = &off_window_left;
}

int element_conditions(t_element* element) {
  int condition;

  condition = 0;
  if (g_game->element_conditions[element->type] != NULL)
    condition += g_game->element_conditions[element->type](element);

  return condition;
}