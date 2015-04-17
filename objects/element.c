#include "../main/prototypes.h"

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

void init_element_collisions() {
  int i;

  for (i = 0; i < 30; i++)
    g_game->element_collisions[i] = NULL;

  g_game->element_collisions[0] = &enemy_collision;
  g_game->element_collisions[10] = &landscape_collision;
  g_game->element_collisions[11] = &landscape_collision;
  g_game->element_collisions[12] = &landscape_collision;
}

t_element* next_element(t_element* element) {
  return element->next;
}

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

int element_conditions(t_element* element) {
  int condition;

  condition = 0;
  if (g_game->element_conditions[element->type] != NULL)
    condition += g_game->element_conditions[element->type](element);

  return condition;
}

int element_collisions(t_element* element) {
  int collision;

  collision = 0;
  if (g_game->element_collisions[element->type] != NULL)
    collision += g_game->element_collisions[element->type](element);

  return collision;
}

void extra_actions(t_element* element) {
  if (element->type >= 0 && element->type < 10)
  {
    enemy_movement(element);
    if (element->hitbox.x > 0 && element->hitbox.x < g_window_width)
      enemy_fire(element);
  }
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

SDL_Texture* element_texture(t_element* element) {
  return g_game->textures[element->type];
}

SDL_Rect crop_texture(t_element* element, SDL_Rect rec) {
  if (element->type == 12)
  {
    rec.x = 256 * (element->hp - 1);
    rec.y = 0;
    rec.w = 256;
    rec.h = 256;
  }
  return rec;
}

int is_animated(t_element* element) {
  int i;
  int allowed[1];

  allowed[0] = 12;
  for (i = 0; i < 1; i++)
    if (allowed[i] == element->type)
      return 1;
  return 0;
}

void render_element(t_element* element) {
  SDL_Rect rec;

  if (is_animated(element) == 1)
  {
    rec = crop_texture(element, rec);
    SDL_RenderCopy(g_game->renderer, element_texture(element), &rec, &element->hitbox);
  }
  else
    SDL_RenderCopy(g_game->renderer, element_texture(element), NULL, &element->hitbox);
}
