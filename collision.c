#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "prototypes.h"
#include <stdio.h>

int collision_manager(SDL_Rect* r1, SDL_Rect* r2) {
  /* check all four corners of each rectangle, to see one is inside the other */
  int collision;

  collision = 0;
  collision += check_top_left_collision(r1, r2);
  collision += check_top_right_collision(r1, r2);
  collision += check_bottom_left_collision(r1, r2);
  collision += check_bottom_right_collision(r1, r2);
  /* acually checking only one corner for r2 one should be fine, juste to make sure r2 is not inside r1 */
  collision += check_top_left_collision(r2, r1);
  collision += check_top_right_collision(r2, r1);
  collision += check_bottom_left_collision(r2, r1);
  collision += check_bottom_right_collision(r2, r1);
  return collision;
}

int check_top_left_collision(SDL_Rect* r1, SDL_Rect* r2) {
  if (r1->x >= r2->x && r1->x <= (r2->x + r2->w))
  {
    if (r1->y >= r2->y && r1->y <= (r2->y + r2->h))
      return 1;
    else
      return 0;
  }
  else
    return 0;
}

int check_top_right_collision(SDL_Rect* r1, SDL_Rect* r2) {
  if ((r1->x + r1->w) >= r2->x && (r1->x + r1->w) <= (r2->x + r2->w))
  {
    if (r1->y >= r2->y && r1->y <= (r2->y + r2->h))
      return 1;
    else
      return 0;
  }
  else
    return 0;
}

int check_bottom_left_collision(SDL_Rect* r1, SDL_Rect* r2) {
  if (r1->x >= r2->x && r1->x <= (r2->x + r2->w))
  {
    if ((r1->y + r1->h) >= r2->y && (r1->y + r1->h) <= (r2->y + r2->h))
      return 1;
    else
      return 0;
  }
  else
    return 0;
}

int check_bottom_right_collision(SDL_Rect* r1, SDL_Rect* r2) {
  if ((r1->x + r1->w) >= r2->x && (r1->x + r1->w) <= (r2->x + r2->w))
  {
    if ((r1->y + r1->h) >= r2->y && (r1->y + r1->h) <= (r2->y + r2->h))
      return 1;
    else
      return 0;
  }
  else
    return 0;
}
