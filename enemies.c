#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>


void freeAllEnemies() {

}

void deleteEnemy() {

}

void renderEnemies() {

}

void moveEnemies() {

}

void createEnemy(int id, int* x, int* y) {

  /* giving each enemy an id, to make `find and delete` easier */

  printf("%d %d %d\n", i, *x, *y);

  /* save first occurence of enemy list */

  /* create enemy sctructure */

  /* set enemy->next to first occurence of list */

  /* set list to start at this enemy */
}

void initializeEnemies() {
  /* i is the number of enemies we need to create */
  int i;
  /* x is a track of where we placed the last enemy on X axe */
  int x;
  /* y is a track of where we placed the last enemy on Y axe */
  int y;

  /* setting first enemy position */
  x = 10;
  y = 10;
  /* creating 30 enemies */
  for (i = 0; i < 30; i++)
  {
    /* given as pointer, so we can modify it later */
    createEnemy(i, &x, &y);
  }

  /*  */
}
