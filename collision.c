#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

int game_collision_manager(SDL_Rect* first, SDL_Rect* second) {
  /* check all four corners of each rectangle, to see one is inside the other */
  int collision;

  collision = 0;
  collision += check_top_left_collision(first, second);
  collision += check_top_right_collision(first, second);
  collision += check_bottom_left_collision(first, second);
  collision += check_bottom_right_collision(first, second);

  /* acually checking only one corner for second one should be fine, juste to make sure second is not inside first */

  collision += check_top_left_collision(second, first);
  collision += check_top_right_collision(second, first);
  collision += check_bottom_left_collision(second, first);
  collision += check_bottom_right_collision(second, first);

  return collision;
}

int check_top_left_collision(SDL_Rect* r, SDL_Rect* s) {
  if (r->x >= s->x && r->x <= (s->x + s->w))
  {
    if (r->y >= s->y && r->y <= (s->y + s->h))
      return 1;
    else
      return 0;
  }
  else
    return 0;
}

int check_top_right_collision(SDL_Rect* r, SDL_Rect* s) {
  if ((r->x + r->w) >= s->x && (r->x + r->w) <= (s->x + s->w))
  {
    if (r->y >= s->y && r->y <= (s->y + s->h))
      return 1;
    else
      return 0;
  }
  else
    return 0;
}

int check_bottom_left_collision(SDL_Rect* r, SDL_Rect* s) {

  if (r->x >= s->x && r->x <= (s->x + s->w))
  {
    if ((r->y + r->h) >= s->y && (r->y + r->h) <= (s->y + s->h))
      return 1;
    else
      return 0;
  }
  else
    return 0;
}

int check_bottom_right_collision(SDL_Rect* r, SDL_Rect* s) {
  if ((r->x + r->w) >= s->x && (r->x + r->w) <= (s->x + s->w))
  {
    if ((r->y + r->h) >= s->y && (r->y + r->h) <= (s->y + s->h))
      return 1;
    else
      return 0;
  }
  else
    return 0;
}
