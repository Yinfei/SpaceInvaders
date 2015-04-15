#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

/* returns next bullet in list */
block_stc* get_next_block(block_stc* block) {
  return block->next;
}

void manage_landscape_actions() {
  block_stc* current;
  block_stc* next;

  if (game->landscape.block != NULL)
  {
    current = game->landscape.block;
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

void manage_landscape_damage(block_stc* block) {
  block->hp -= 1;

  if (block->hp == 0)
    delete_landscape_block(block);

  /* add game score */
  game->score += 10;
}

void manage_landscape_collisions() {
  block_stc* current;
  block_stc* next;

  if (game->landscape.block != NULL)
  {
    current = game->landscape.block;
    while (current != NULL)
    {
      /* check if out of shot */
      if (check_landscape_block_collisions(current) > 0)
      {
        next = get_next_block(current);
        manage_landscape_damage(current);
        current = next;
      }
      else
        current = get_next_block(current);
    }
  }
}

int check_landscape_block_collisions(block_stc* block) {
  bullet_stc* current;

  if (game->player.bullet_list != NULL)
  {
    current = game->player.bullet_list;
    while (current != NULL)
    {
      if (game_collision_manager(&block->hitbox, &current->hitbox) > 0)
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
    return game->landscape.top_texture;
  else if (i == 1)
    return game->landscape.bottom_texture;
  else
    return game->landscape.breakable_texture;
}

void render_landscape_block(block_stc* block) {
  SDL_Rect rec;
  if (block->type == 2)
  {
    rec.x = 256 * (block->hp - 1);
    rec.y = 0;
    rec.w = 256;
    rec.h = 256;
    SDL_RenderCopy(game->renderer, get_landscape_block_texture(block->type), &rec, &block->hitbox);
  }
  else
    SDL_RenderCopy(game->renderer, get_landscape_block_texture(block->type), NULL, &block->hitbox);
}

void initialize_landscape() {
  game->landscape.block = NULL;

  /* initialize textures */
  game->landscape.top_texture = IMG_LoadTexture(game->renderer, "img/top_block.png");
  game->landscape.bottom_texture  = IMG_LoadTexture(game->renderer, "img/bottom_block.png");
  game->landscape.breakable_texture  = IMG_LoadTexture(game->renderer, "img/block.png");


  /* creating on of each type, for test purposes */

    create_landscape_top_block(600, 150, 150);
    create_landscape_bottom_block(510, 230, 230);
    create_landscape_breakable_block(640, 150, 40, 40);


  /* render landscape blocks */
  manage_landscape_actions();
}

void create_landscape_top_block(int x, int w, int h) {
  block_stc* block;

  block = malloc(sizeof (block_stc));
  block->hitbox.x = x;
  block->hitbox.y = 0;
  block->hitbox.w = w;
  block->hitbox.h = h;
  block->prev = NULL;
  /* top block type = 0 (for automatic rendering purposes) */
  block->type = 0;
  /* setting block hp to -1 (because unbreakable) */
  block->hp = -1;

  if (game->landscape.block != NULL)
  {
    block->next = game->landscape.block;
    game->landscape.block->prev = block;
  }
  else
    block->next = NULL;
  game->landscape.block = block;
}

void create_landscape_bottom_block(int x, int w, int h) {
  block_stc* block;

  block = malloc(sizeof (block_stc));
  block->hitbox.x = x;
  block->hitbox.y = GAMEHEIGHT - h;
  block->hitbox.w = w;
  block->hitbox.h = h;
  block->prev = NULL;
  /* bottom block type = 1 (for automatic rendering purposes) */
  block->type = 1;
  /* setting block hp to -1 (because unbreakable) */
  block->hp = -1;

  if (game->landscape.block != NULL)
  {
    block->next = game->landscape.block;
    game->landscape.block->prev = block;
  }
  else
    block->next = NULL;

  game->landscape.block = block;
}

void create_landscape_breakable_block(int x, int y, int w, int h) {
  block_stc* block;

  block = malloc(sizeof (block_stc));
  block->hitbox.x = x;
  block->hitbox.y = y;
  block->hitbox.w = w;
  block->hitbox.h = h;
  block->prev = NULL;
  /* block type = 2 (for automatic rendering purposes) */
  block->type = 2;
  /* setting block hp to 3 (three hits to break) */
  block->hp = 3;

  if (game->landscape.block != NULL)
  {
    block->next = game->landscape.block;
    game->landscape.block->prev = block;
  }
  else
    block->next = NULL;

  game->landscape.block = block;
}


void move_landscape_block(block_stc* block) {
  block->hitbox.x -= 1;

  /* check for collisions with player */
  if (game_collision_manager(&game->player.hitbox, &block->hitbox) > 0)
    /* if so, push player */
    game->player.hitbox.x -= 1;
}


void delete_landscape_block(block_stc* block) {
  /* setting the previous block pointer for "next block" as current block "next block" pointer */
  if (block->prev != NULL)
  {
    block->prev->next = block->next;
    if (block->next != NULL)
      block->next->prev = block->prev;
  }
  else
  {
    game->landscape.block = block->next;
    if (block->next != NULL)
      game->landscape.block->prev = NULL;
  }
  /* freeing block space */
  free(block);
}

void free_landscape_blocks() {
  block_stc* current;
  block_stc* toFree;

  if (game->landscape.block != NULL)
  {
    /* creating value to parsethough */
    current = game->landscape.block;
    toFree  = current;
    /* parse through each bullet, free each one */
    while (current != NULL)
    {
      if (current->next != NULL)
      {
        current = current->next;
        free(toFree);
        toFree = current;
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
  SDL_DestroyTexture(game->landscape.top_texture);
  SDL_DestroyTexture(game->landscape.bottom_texture);
  SDL_DestroyTexture(game->landscape.breakable_texture);
}

void free_landscape() {
  /* free landscape blocks ... */
  free_landscape_blocks();
  /* free landscape textures */
  free_landscape_textures();


}
