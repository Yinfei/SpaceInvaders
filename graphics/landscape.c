#include "../main/prototypes.h"

/* returns next bullet in list */
t_block* get_next_block(t_block* block) {
  return block->next;
}

void landscape_actions() {
  t_block* current;
  t_block* next;

  if (g_game->landscape.block != NULL)
  {
    current = g_game->landscape.block;
    while (current != NULL)
    {
      /* check if out of shot */
      if (current->hitbox.x + current->hitbox.w < 0)
      {
        /* set next bullet */
        next = get_next_block(current);
        /* removing this bullet from list */
        delete_landscape_block(current);
        current = next;
      }
      else
      {
        move_landscape_block(current);
        render_landscape_block(current);
        current = get_next_block(current);
      }
    }
  }
}

void landscape_damage(t_block* block) {
  block->hp -= 1;

  if (block->hp == 0)
    delete_landscape_block(block);

  /* add game score */
  g_game->score += 10;
}

void landscape_collisions() {
  t_block* current;
  t_block* next;

  if (g_game->landscape.block != NULL)
  {
    current = g_game->landscape.block;
    while (current != NULL)
    {
      /* check if out of shot */
      if (check_landscape_collisions(current) > 0)
      {
        next = get_next_block(current);
        landscape_damage(current);
        current = next;
      }
      else
        current = get_next_block(current);
    }
  }
}

int check_landscape_collisions(t_block* block) {
  t_bullet* current;

  if (g_game->player.bullet_list != NULL)
  {
    current = g_game->player.bullet_list;
    while (current != NULL)
    {
      if (collision_manager(&block->hitbox, &current->hitbox) > 0)
      {
        delete_player_bullet(current);
        return 1;
      }
      else
        current = get_next_bullet(current);
    }
  }
  return 0;
}

SDL_Texture* get_landscape_block_texture(int i) {
  if (i == 0)
    return g_game->landscape.top_texture;
  else if (i == 1)
    return g_game->landscape.bottom_texture;
  else
    return g_game->landscape.breakable_texture;
}

void render_landscape_block(t_block* block) {
  SDL_Rect rec;
  if (block->type == 2)
  {
    rec.x = 256 * (block->hp - 1);
    rec.y = 0;
    rec.w = 256;
    rec.h = 256;
    SDL_RenderCopy(g_game->renderer, get_landscape_block_texture(block->type), &rec, &block->hitbox);
  }
  else
    SDL_RenderCopy(g_game->renderer, get_landscape_block_texture(block->type), NULL, &block->hitbox);
}

void init_landscape() {
  g_game->landscape.block = NULL;

  /* initialize textures */
  g_game->landscape.top_texture = IMG_LoadTexture(g_game->renderer, "assets/images/top_block.png");
  g_game->landscape.bottom_texture  = IMG_LoadTexture(g_game->renderer, "assets/images/bottom_block.png");
  g_game->landscape.breakable_texture  = IMG_LoadTexture(g_game->renderer, "assets/images/block.png");

  /* creating on of each type, for test purposes */
  create_landscape_top_block(600, 150, 150);
  create_landscape_bottom_block(510, 230, 230);
  create_landscape_breakable_block(640, 150, 40, 40);

  /* render landscape blocks */
  landscape_actions();
}

void create_landscape_top_block(int x, int w, int h) {
  t_block* block;

  block = malloc(sizeof (t_block));
  block->hitbox.x = x;
  block->hitbox.y = 0;
  block->hitbox.w = w;
  block->hitbox.h = h;
  block->prev = NULL;
  /* top block type = 0 (for automatic rendering purposes) */
  block->type = 0;
  /* setting block hp to -1 (because unbreakable) */
  block->hp = -1;

  if (g_game->landscape.block != NULL)
  {
    block->next = g_game->landscape.block;
    g_game->landscape.block->prev = block;
  }
  else
    block->next = NULL;
  g_game->landscape.block = block;
}

void create_landscape_bottom_block(int x, int w, int h) {
  t_block* block;

  block = malloc(sizeof (t_block));
  block->hitbox.x = x;
  block->hitbox.y = g_window_height - h;
  block->hitbox.w = w;
  block->hitbox.h = h;
  block->prev = NULL;
  /* bottom block type = 1 (for automatic rendering purposes) */
  block->type = 1;
  /* setting block hp to -1 (because unbreakable) */
  block->hp = -1;

  if (g_game->landscape.block != NULL)
  {
    block->next = g_game->landscape.block;
    g_game->landscape.block->prev = block;
  }
  else
    block->next = NULL;

  g_game->landscape.block = block;
}

void create_landscape_breakable_block(int x, int y, int w, int h) {
  t_block* block;

  block = malloc(sizeof (t_block));
  block->hitbox.x = x;
  block->hitbox.y = y;
  block->hitbox.w = w;
  block->hitbox.h = h;
  block->prev = NULL;
  /* block type = 2 (for automatic rendering purposes) */
  block->type = 2;
  /* setting block hp to 3 (three hits to break) */
  block->hp = 3;

  if (g_game->landscape.block != NULL)
  {
    block->next = g_game->landscape.block;
    g_game->landscape.block->prev = block;
  }
  else
    block->next = NULL;

  g_game->landscape.block = block;
}

void move_landscape_block(t_block* block) {
  block->hitbox.x -= 1;

  /* check for collisions with player */
  if (collision_manager(&g_game->player.hitbox, &block->hitbox) > 0)
    /* if so, push player */
    g_game->player.hitbox.x -= 1;
}


void delete_landscape_block(t_block* block) {
  /* setting the previous block pointer for "next block" as current block "next block" pointer */
  if (block->prev != NULL)
  {
    block->prev->next = block->next;
    if (block->next != NULL)
      block->next->prev = block->prev;
  }
  else
  {
    g_game->landscape.block = block->next;
    if (block->next != NULL)
      g_game->landscape.block->prev = NULL;
  }
  /* freeing block space */
  free(block);
}

void free_landscape_blocks() {
  t_block* current;
  t_block* to_free;

  if (g_game->landscape.block != NULL)
  {
    /* creating value to parsethough */
    current = g_game->landscape.block;
    to_free  = current;
    /* parse through each bullet, free each one */
    while (current != NULL)
    {
      if (current->next != NULL)
      {
        current = current->next;
        free(to_free);
        to_free = current;
      }
      else
      {
        free(current);
        break;
      }
    }
  }
}

void free_landscape_textures() {
  SDL_DestroyTexture(g_game->landscape.top_texture);
  SDL_DestroyTexture(g_game->landscape.bottom_texture);
  SDL_DestroyTexture(g_game->landscape.breakable_texture);
}

void free_landscape() {
  /* free landscape blocks ... */
  free_landscape_blocks();
  /* free landscape textures */
  free_landscape_textures();
}
