#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

void free_enemy_list() {
  t_enemy* current;
  t_enemy* to_free;

  if (g_game->enemies->enemy_list != NULL)
  {
    /* creating value to parsethough */
    current = g_game->enemies->enemy_list;
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

void free_enemies() {
  /* free all enemies */
  free_enemy_list();

  /* free all textures */
  /* SDL_DestroyTexture(g_game->enemies->mine_texture); */
  /* SDL_DestroyTexture(g_game->enemies->runner_texture); */
  /* SDL_DestroyTexture(g_game->enemies->jumper_texture); */
  SDL_DestroyTexture(g_game->enemies->flyer_texture);
}

void custom_enemy_movement(t_enemy* enemy) {

  /* change this to some sort of custom movement (oscilation, rotation, linear) */
  enemy->hitbox.y = enemy->hitbox.y;


}

void enemy_bullet_direction(t_bullet* bullet) {
  int x;
  int y;
  int angle;

  /* get x distance between two */
  x = bullet->hitbox.x - g_game->player.hitbox.x;
  /* get y distance between two */
  if (bullet->hitbox.y >= g_game->player.hitbox.y)
    y = - (bullet->hitbox.y - g_game->player.hitbox.y);
  else
    y = g_game->player.hitbox.y - bullet->hitbox.y;

  /* setting angle; */
  if (x != 0)
    angle = (3 * y) / x;
  else
    angle = y;

  bullet->x = -3;
  bullet->y = angle;
}

void enemy_fire(t_enemy* enemy) {
  t_bullet* bullet;

  bullet = malloc(sizeof(t_bullet));
  bullet->hitbox.x = enemy->hitbox.x;
  bullet->hitbox.y = enemy->hitbox.y + (enemy->hitbox.h / 2);
  bullet->hitbox.w = 3;
  bullet->hitbox.h = 3;

  /* setting direction of shot */
  enemy_bullet_direction(bullet);

  bullet->prev = NULL;
  /* checking if bullet list is empty */
  if (g_game->enemies->bullet_list != NULL)
  {
    bullet->next = g_game->enemies->bullet_list;
    g_game->enemies->bullet_list->prev = bullet;
  }
  else
    bullet->next = NULL;
  /* setting start of bullet list to current bullet */
  g_game->enemies->bullet_list = bullet;
}

void check_enemy_fire(t_enemy* enemy) {
  int i;

  /* check if last fire happened recently */
  if (SDL_TICKS_PASSED(SDL_GetTicks(), enemy->cooldown) == 1)
  {
    i = rand() % 100;

    /* 1/100 chance to fire, every 16 ms (if no cooldown) */
    if (i == 1 && enemy->hitbox.x >= g_game->player.hitbox.x)
    {
      /* shooting bullet */
      enemy_fire(enemy);
      /* setting enemy cool */
      enemy->cooldown = SDL_GetTicks() + 700;
    }
  }
}

void enemies_actions() {
  t_enemy* current;

  /* moving each enemy / deleting ones offscreen */
  manage_enemy_list();

  /* parse though enemies, check if they shoot / move (specific movement) or not */
  if (g_game->enemies->enemy_list != NULL)
  {
    current = g_game->enemies->enemy_list;
    while (current != NULL)
    {
      /* trigger movement */
      custom_enemy_movement(current);

      /* if on shot, give possibility to shoot */
      if (current->hitbox.x > 0 && current->hitbox.x < g_window_width)
        check_enemy_fire(current);
      current = get_next_enemy(current);
    }
  }
  /* parse though enemy bullets */
  enemy_bullets();
}

void damage_enemy(t_enemy* enemy) {
  enemy->hp -= 1;

  if (enemy->hp == 0)
    delete_enemy(enemy);

  /* add game score */
  g_game->score += 10;
}

int check_enemy_collisions(t_enemy* enemy) {
  t_bullet* current;
  int collision;

  collision = 0;
  /* check collisions with player */
  if (collision_manager(&enemy->hitbox, &g_game->player.hitbox) > 0)
    collision += damage_player(1);

  /* check collisions with bullets */
  if (g_game->player.bullet_list != NULL)
  {
    current = g_game->player.bullet_list;
    while (current != NULL)
    {
      if (collision_manager(&enemy->hitbox, &current->hitbox) > 0)
      {
        delete_player_bullet(current);
        return 1;
      }
      else
        current = get_next_bullet(current);
    }
  }
  return collision;
}

void enemies_collisions() {
  t_enemy* current;
  t_enemy* next;

  if (g_game->enemies->enemy_list != NULL)
  {
    current = g_game->enemies->enemy_list;
    while (current != NULL)
    {
      /* check if out of shot */
      if (check_enemy_collisions(current) > 0)
      {
        next = get_next_enemy(current);
        damage_enemy(current);
        current = next;
      }
      else
        current = get_next_enemy(current);
    }
  }
}

void delete_enemy(t_enemy* enemy) {
  /* setting the previous enemy pointer for "next enemy" as current enemy "next enemy" pointer */
  if (enemy->prev != NULL)
  {
    enemy->prev->next = enemy->next;
    if (enemy->next != NULL)
      enemy->next->prev = enemy->prev;
  }
  else
  {
    g_game->enemies->enemy_list = enemy->next;
    if (enemy->next != NULL)
      g_game->enemies->enemy_list->prev = NULL;
  }
  /* freeing enemy space */
  free(enemy);
}

void move_enemy(t_enemy* enemy) {
  enemy->hitbox.x -= 1;
}

void render_enemy(t_enemy* enemy) {
  SDL_RenderCopy(g_game->renderer, g_game->enemies->flyer_texture, NULL, &enemy->hitbox);
}

void manage_enemy(t_enemy* enemy) {
  /* check if off screen on left */
  if (enemy->hitbox.x + enemy->hitbox.w < 0)
    delete_enemy(enemy);
  /* check if off screen on right */
  else if (enemy->hitbox.x > g_window_width)
    move_enemy(enemy);
  /* else, display */
  else
  {
    move_enemy(enemy);
    render_enemy(enemy);
  }
}

t_enemy* get_next_enemy(t_enemy* enemy) {
  return enemy->next;
}

void manage_enemy_list() {
  /* parse though enemies, to move and render them */
  t_enemy* current;
  t_enemy* next;

  if (g_game->enemies->enemy_list != NULL)
  {
    current = g_game->enemies->enemy_list;
    while (current != NULL)
    {
      next = get_next_enemy(current);
      manage_enemy(current);
      current = next;
    }
  }

  /* managing collisions */
  enemies_collisions();
}

void create_enemy() {
  t_enemy* enemy;

  /* setting enemy details */
  enemy = malloc(sizeof(t_enemy));
  enemy->hitbox.x = 1200;
  enemy->hitbox.y = 250;
  enemy->hitbox.w = 70;
  enemy->hitbox.h = 50;
  enemy->prev = NULL;

  enemy->hp = 2;
  enemy->cooldown = 0;

  /* trying with enemy time = 0 (flyer?) */
  enemy->type = 0;

  /* checking if enemy list is empty */
  if (g_game->enemies->enemy_list != NULL)
  {
    enemy->next = g_game->enemies->enemy_list;
    g_game->enemies->enemy_list->prev = enemy;
  }
  else
    enemy->next = NULL;
  /* setting start of enemy list to current enemy */
  g_game->enemies->enemy_list = enemy;

}

void init_enemies() {
  /* initialize enemy list */
  g_game->enemies->enemy_list = NULL;

  /* loading flyer sprite */
  g_game->enemies->flyer_texture = IMG_LoadTexture(g_game->renderer, "img/fatcat.png");

  /* creating enemy for test purposes */
  create_enemy();


  /* setting bullet list to null */
  g_game->enemies->bullet_list = NULL;
}
