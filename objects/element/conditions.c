#include "../../main/prototypes.h"

void init_element_conditions() {
  int i;

  for (i = 0; i < 40; i++)
    g_game->element_conditions[i] = NULL;

  g_game->element_conditions[10] = &off_window_left;
  g_game->element_conditions[11] = &off_window_left;
  g_game->element_conditions[12] = &off_window_left;
  g_game->element_conditions[13] = &displayed_given_time;
  g_game->element_conditions[20] = &off_window_right;
  g_game->element_conditions[21] = &off_window_left;
  g_game->element_conditions[31] = &off_window_left;
  g_game->element_conditions[32] = &off_window_left;
  g_game->element_conditions[33] = &off_window_left;
  g_game->element_conditions[34] = &off_window_left;
  g_game->element_conditions[35] = &off_window_left;
  g_game->element_conditions[36] = &off_window_left;
  g_game->element_conditions[37] = &off_window_left;
}

int element_conditions(t_element* element) {
  int condition;

  condition = 0;
  if (g_game->element_conditions[element->type] != NULL)
    condition += g_game->element_conditions[element->type](element);

  return condition;
}
