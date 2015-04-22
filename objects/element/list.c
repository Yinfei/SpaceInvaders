#include "../../main/prototypes.h"

void add_element(t_element** list, t_element* element) {
  t_element* first_element;

  first_element = *list;
  element->prev = NULL;
  if (first_element != NULL)
  {
    element->next = first_element;
    first_element->prev = element;
  }
  else
    element->next = NULL;
  *list = element;
}

void remove_element(t_element** list, t_element* element) {
  if (element->prev != NULL)
  {
    element->prev->next = element->next;
    if (element->next != NULL)
      element->next->prev = element->prev;
  }
  else
  {
    if (element->next == NULL)
      *list = NULL;
    else
    {
      element->next->prev = NULL;
      *list = element->next;
    }
  }
  free(element);
}

int element_list_collision(t_element** list, t_element* element) {
  t_element* current;

  current = *list;
  while (current != NULL)
  {
    if (collision_manager(&element->hitbox, &current->hitbox) > 0)
    {
      remove_element(list, current);
      return 1;
    }
    else
      current = next_element(current);
  }
  return 0;
}

void free_element_list(t_element** list) {
  t_element* current;

  current = *list;
  while (current != NULL)
  {
    if (current->next != NULL)
    {
      current = current->next;
      remove_element(list, current->prev);
    }
    else
    {
      remove_element(list, current);
      break;
    }
  }
}
