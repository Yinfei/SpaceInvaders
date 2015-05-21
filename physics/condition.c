#include "../main/prototypes.h"

int off_window_left(t_element* element) {
  if (element->hitbox.x + element->hitbox.w < 0)
    return 1;
  else
    return 0;
}

int off_window_right(t_element* element) {
  if (element->hitbox.x > g_window_width)
    return 1;
  else
    return 0;
}

int displayed_one_second(t_element* element) {
  if (SDL_TICKS_PASSED(SDL_GetTicks(), element->cooldown) == 1)
    return 1;
  else
    return 0;
}
