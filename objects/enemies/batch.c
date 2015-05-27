#include "../../main/prototypes.h"

void enemies_batch1() {
  create_enemy(800, 100, 0);
  create_enemy(800, 200, 0);
  create_enemy(800, 300, 0);
  create_enemy(950, 150, 2);
  create_enemy(1100, 200, 2);
  create_enemy(1000, 350, 2);
  create_enemy(1400, 100, 1);
  create_enemy(1400, 200, 0);
  create_enemy(1400, 300, 1);
  create_enemy(1550, 50, 1);
  create_enemy(1650, 300, 1);
  create_enemy(1750, 100, 1);
  create_enemy(1850, 200, 1);
  create_enemy(2600, 50, 2);
  create_enemy(2600, 150, 2);
  create_enemy(2600, 250, 2);
  create_enemy(2600, 350, 2);
  create_enemy(2700, 0, 2);
}

void enemies_batch2() {
  create_enemy(2700, 100, 2);
  create_enemy(2700, 200, 2);
  create_enemy(2700, 300, 2);
  create_enemy(2800, 50, 2);
  create_enemy(2800, 150, 2);
  create_enemy(2800, 250, 2);
  create_enemy(2800, 350, 2);
  create_enemy(2900, 0, 2);
  create_enemy(2900, 100, 2);
  create_enemy(2900, 200, 2);
  create_enemy(2900, 300, 2);
  create_enemy(3300, 50, 0);
  create_enemy(3300, 150, 0);
  create_enemy(3300, 250, 0);
  create_enemy(3300, 350, 0);
  create_enemy(3400, 50, 1);
  create_enemy(3400, 350, 1);
  create_enemy(4300, 200, 9);
}

void enemies_batch() {
  enemies_batch1();
  enemies_batch2();
}
