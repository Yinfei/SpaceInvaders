#include "../main/prototypes.h"

t_element* next_element(t_element* element) {
  return element->next;
}

void element_actions(t_element** list) {
  t_element* current;
  t_element* next;

  current = *list;
  while (current != NULL)
  {
    if (element_conditions(current) > 0)
    {
      next = next_element(current);
      remove_element(list, current);
      current = next;
    }
    else
    {
      next = next_element(current);
      extra_actions(current);
      if (element_collisions(current) == 0)
      {
        move_element(current);
        render_element(current);
      }
      current = next;
    }
  }
}

void move_element(t_element* element) {
  element->hitbox.x += element->x;
  element->hitbox.y += element->y;

  if (element->type > 9 && element->type < 20)
    if (collision_manager(&g_game->player->hitbox, &element->hitbox) > 0)
      g_game->player->hitbox.x -= 1;
}

int damage_element(t_element** list, t_element* element) {
  int critical;

  critical = 0;
  element->hp -= 1;
  if (element->hp == 0)
  {
    remove_element(list, element);
    critical = 1;
  }
  /* add game score */
  g_game->score += 10;
  return critical;
}

void extra_actions(t_element* element) {
  if (element->type >= 0 && element->type < 10)
  {
    enemy_movement(element);
    if (element->hitbox.x > 0 && element->hitbox.x < g_window_width)
      enemy_fire(element);
  }
}
