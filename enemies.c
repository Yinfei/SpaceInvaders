#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>


void free_enemies() {

}

void delete_enemy() {

}

void render_enemy() {

}

void manage_enemy_actions() {

}

void create_enemy(int id, int* x, int* y) {
  /* giving each enemy an id, to make `find and delete` easier */
  printf("%d %d %d\n", id, *x, *y);


  /* create enemy sctructure */

  /* set enemy->next to first occurence of list */

  /* set list to start at this enemy */
}

void initialize_enemies() {
  /* i is the number of enemies we need to create */
  int i;
  /* x is a track of where we placed the last enemy on X axe */
  int x;
  /* y is a track of where we placed the last enemy on Y axe */
  int y;

  /* setting first enemy position */
  x = 10;
  y = 10;
  /* creating 50 enemies */
  for (i = 0; i < 50; i++)
  {
    /* given as pointer, so we can modify it later */
    create_enemy(i, &x, &y);
  }
}
