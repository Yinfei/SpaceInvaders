#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

/* returns next bullet in list */
bullet_stc* get_next_bullet(bullet_stc* bullet) {
  if (bullet->next != NULL)
    bullet = bullet->next;
  else
    bullet = NULL;

  return bullet;
}

/* parses through bullet list, moves and renders them */
void manage_player_bullets() {
  bullet_stc* current;
  bullet_stc* next;

  if (game->player.bullet_list != NULL)
  {
    current = game->player.bullet_list;
    while (current != NULL)
    {
      /* check if out of shot */
      if (current->hitbox.x > GAMEWIDTH)
      {
        /* set next bullet */
        next = get_next_bullet(current);
        /* removing this bullet from list */
        delete_player_bullet(current);
        current = next;
      }
      else
      {
        move_player_bullet(current);
        draw_player_bullet(current);
        current = get_next_bullet(current);
      }
    }
  }
}

/* parsed through enemy bullets, moves and renders them */
void manage_enemy_bullets() {
  bullet_stc* current;
  bullet_stc* next;

  if (game->enemies->enemy_bullet_list != NULL)
  {
    current = game->enemies->enemy_bullet_list;
    while (current != NULL)
    {
      /* check if out of shot */
      if (current->hitbox.x > 0)
      {
        /* set next bullet */
        next = get_next_bullet(current);
        /* removing this bullet from list */
        delete_enemy_bullet(current);
        current = next;
      }
      else
      {
        move_player_bullet(current);
        draw_player_bullet(current);
        current = get_next_bullet(current);
      }
    }
  }
}

/* deletes and frees specific bullet from enemy bullet list */
void delete_enemy_bullet(bullet_stc* bullet) {
  /* setting the previous bullets pointer for "next bullet" as current bullets "next bullet" pointer */
  if (bullet->prev != NULL)
    bullet->prev->next = bullet->next;
  else
    game->enemies->enemy_bullet_list = bullet->next;

  /* freeing bullet space */
  free(bullet);
}

void move_enemy_bullet(bullet_stc* bullet) {
  bullet->hitbox.x -= 3;
}

/* used to animate player bullet */
void move_player_bullet(bullet_stc* bullet) {
  bullet->hitbox.x += 5;
}

/* draws bullet on the screen */
void draw_player_bullet(bullet_stc* bullet) {
  /* Set render color to red (bullet will be rendered in this color) */
  SDL_SetRenderDrawColor(game->renderer,255,0,0,255);
  /* Render player hitbox */
  SDL_RenderFillRect(game->renderer, &bullet->hitbox);
}

/* called when a bullet hits an enemy or when a bullet goes further than the screen */
void delete_player_bullet(bullet_stc* bullet) {
  /* setting the previous bullets pointer for "next bullet" as current bullets "next bullet" pointer */
  if (bullet->prev != NULL)
    bullet->prev->next = bullet->next;
  else
    game->player.bullet_list = bullet->next;

  /* freeing bullet space */
  free(bullet);
}

/* called at the end of the game, to free each bullet */
void free_player_bullets() {
  bullet_stc* current;
  bullet_stc* toFree;

  if (game->player.bullet_list != NULL)
  {
    /* creating value to parsethough */
    current = game->player.bullet_list;
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
