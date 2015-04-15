#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "../main/prototypes.h"
#include <stdio.h>

/* returns next bullet in list */
t_bullet* get_next_bullet(t_bullet* bullet) {
  return bullet->next;
}

/* parses through bullet list, moves and renders them */
void player_bullets() {
  t_bullet* current;
  t_bullet* next;

  if (g_game->player.bullet_list != NULL)
  {
    current = g_game->player.bullet_list;
    while (current != NULL)
    {
      /* check if out of shot */
      if (current->hitbox.x > g_window_width)
      {
        /* set next bullet */
        next = get_next_bullet(current);
        /* removing this bullet from list */
        delete_player_bullet(current);
        current = next;
      }
      else
      {
        move_bullet(current);
        render_player_bullet(current);
        current = get_next_bullet(current);
      }
    }
  }
}

/* parsed through enemy bullets, moves and renders them */
void enemy_bullets() {
  t_bullet* current;
  t_bullet* next;

  if (g_game->enemies->bullet_list != NULL)
  {
    current = g_game->enemies->bullet_list;
    while (current != NULL)
    {
      /* check if out of shot */
      if (current->hitbox.x < 0)
      {
        /* set next bullet */
        next = get_next_bullet(current);
        /* removing this bullet from list */
        delete_enemy_bullet(current);
        current = next;
      }
      else
      {
        move_bullet(current);
        render_enemy_bullet(current);
        current = get_next_bullet(current);
      }
    }
  }
}

/* deletes and frees specific bullet from enemy bullet list */
void delete_enemy_bullet(t_bullet* bullet) {
  /* setting the previous bullet pointer for "next bullet" as current bullet "next bullet" pointer */
  if (bullet->prev != NULL)
  {
    bullet->prev->next = bullet->next;
    if (bullet->next != NULL)
      bullet->next->prev = bullet->prev;
  }
  else
  {
    g_game->enemies->bullet_list = bullet->next;
    if (bullet->next != NULL)
      g_game->enemies->bullet_list->prev = NULL;
  }
  /* freeing bullet space */
  free(bullet);
}

void move_bullet(t_bullet* bullet) {
  bullet->hitbox.x += bullet->x;
  bullet->hitbox.y += bullet->y;
}

/* draws bullet on the screen */
void render_player_bullet(t_bullet* bullet) {
  /* Set render color to red (bullet will be rendered in this color) */
  SDL_SetRenderDrawColor(g_game->renderer,255,0,0,255);
  /* Render player hitbox */
  SDL_RenderFillRect(g_game->renderer, &bullet->hitbox);
}

/* draws bullet on the screen */
void render_enemy_bullet(t_bullet* bullet) {
  /* Set render color to red (bullet will be rendered in this color) */
  SDL_SetRenderDrawColor(g_game->renderer,0,255,0,255);
  /* Render player hitbox */
  SDL_RenderFillRect(g_game->renderer, &bullet->hitbox);
}

/* called when a bullet hits an enemy or when a bullet goes further than the screen */
void delete_player_bullet(t_bullet* bullet) {
  /* setting the previous bullets pointer for "next bullet" as current bullets "next bullet" pointer */
  if (bullet->prev != NULL)
  {
    bullet->prev->next = bullet->next;
    if (bullet->next != NULL)
      bullet->next->prev = bullet->prev;
  }
  else
  {
    g_game->player.bullet_list = bullet->next;
    if (bullet->next != NULL)
      g_game->player.bullet_list->prev = NULL;
  }
  /* freeing bullet space */
  free(bullet);
}

/* called at the end of the game, to free each bullet */
void free_player_bullets() {
  t_bullet* current;
  t_bullet* next;

  if (g_game->player.bullet_list != NULL)
  {
    /* creating value to parsethough */
    current = g_game->player.bullet_list;
    next = current;
    /* parse through each bullet, free each one */
    while (current != NULL)
    {
      if (current->next != NULL)
      {
        next = current->next;
        free(current);
        current = next;
      }
      else
      {
        free(current);
        break;
      }
    }
  }
}
