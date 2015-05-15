#include "../../main/prototypes.h"

void init_landscape() {
  t_landscape* landscape;

  landscape = malloc(sizeof (t_landscape));
  g_game->landscape = landscape;
  landscape->block_list = NULL;
  landscape_batch();
}

void create_block(int x, int y, int type) {
  t_element* block;

  block = malloc(sizeof (t_element));
  block->hitbox.x = x;
  block->hitbox.y = y;
  block->hitbox.w = 50;
  block->hitbox.h = 50;
  block->prev = NULL;
  block->type = type;
  if (type != 12)
    block->hp = -1;
  else
  {
    block->hp = 3;
    block->points = 5;
  }
  block->x = -1;
  block->y = 0;
  add_element(&g_game->landscape->block_list, block);
}

int landscape_collision(t_element* element) {
  int collision;

  collision = 0;
  if (element_list_collision(&g_game->player->bullet_list, element) > 0)
    collision += damage_element(&g_game->landscape->block_list, element);

  return collision;
}

void free_landscape() {
  free_element_list(&g_game->landscape->block_list);
  free(g_game->landscape);
}
