#include <SDL2/SDL.h>
#include <SDL_image.h>
#include "space.h"
#include <stdio.h>

void free_enemy_list() {
  enemy_stc* current;
  enemy_stc* toFree;

  if (game->enemies->enemy_list != NULL)
  {
    /* creating value to parsethough */
    current = game->enemies->enemy_list;
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

void free_enemies() {
  /* free all enemies */
  free_enemy_list();

  /* free all textures */
  /* SDL_DestroyTexture(game->enemies->mine_texture); */
  /* SDL_DestroyTexture(game->enemies->runner_texture); */
  /* SDL_DestroyTexture(game->enemies->jumper_texture); */
  SDL_DestroyTexture(game->enemies->flyer_texture);
}

void execute_custom_enemy_movement(enemy_stc* enemy) {

  /* change this to some sort of custom movement (oscilation, rotation, linear) */
  enemy->hitbox.y = enemy->hitbox.y;


}

void set_enemy_bullet_direction(bullet_stc* bullet) {
  int x;
  int y;
  int angle;

  /* get x distance between two */
  x = bullet->hitbox.x - game->player.hitbox.x;
  /* get y distance between two */
  if (bullet->hitbox.y >= game->player.hitbox.y)
    y = - (bullet->hitbox.y - game->player.hitbox.y);
  else
    y = game->player.hitbox.y - bullet->hitbox.y;

  /* setting angle; */
  if (x != 0)
    angle = (3 * y) / x;
  else
    angle = y;

  bullet->x = -3;
  bullet->y = angle;
}

void enemy_fire(enemy_stc* enemy) {
  bullet_stc* bullet;

  bullet = malloc(sizeof(bullet_stc));
  bullet->hitbox.x = enemy->hitbox.x;
  bullet->hitbox.y = enemy->hitbox.y + (enemy->hitbox.h / 2);
  bullet->hitbox.w = 3;
  bullet->hitbox.h = 3;

  /* setting direction of shot */
  set_enemy_bullet_direction(bullet);

  bullet->prev = NULL;
  /* checking if bullet list is empty */
  if (game->enemies->bullet_list != NULL)
  {
    bullet->next = game->enemies->bullet_list;
    game->enemies->bullet_list->prev = bullet;
  }
  else
    bullet->next = NULL;
  /* setting start of bullet list to current bullet */
  game->enemies->bullet_list = bullet;
}

void check_enemy_fire(enemy_stc* enemy) {
  int i;

  /* check if last fire happened recently */
  if (SDL_TICKS_PASSED(SDL_GetTicks(), enemy->cooldown) == 1)
  {
    i = rand() % 100;

    /* 1/100 chance to fire, every 16 ms (if no cooldown) */
    if (i == 1 && enemy->hitbox.x >= game->player.hitbox.x)
    {
      /* shooting bullet */
      enemy_fire(enemy);
      /* setting enemy cool */
      enemy->cooldown = SDL_GetTicks() + 700;
    }
  }
}

void manage_enemies_actions() {
  enemy_stc* current;

  /* moving each enemy / deleting ones offscreen */
  manage_enemy_list();

  /* parse though enemies, check if they shoot / move (specific movement) or not */
  if (game->enemies->enemy_list != NULL)
  {
    current = game->enemies->enemy_list;
    while (current != NULL)
    {
      /* trigger movement */
      execute_custom_enemy_movement(current);

      /* if on shot, give possibility to shoot */
      if (current->hitbox.x > 0 && current->hitbox.x < GAMEWIDTH)
        check_enemy_fire(current);
      current = get_next_enemy(current);
    }
  }
  /* parse though enemy bullets */
  manage_enemy_bullets();
}

void manage_enemy_damage(enemy_stc* enemy) {
  enemy->hp -= 1;

  if (enemy->hp == 0)
    delete_enemy(enemy);

  /* add game score */
  game->score += 10;
}

int check_enemy_collisions(enemy_stc* enemy) {
  bullet_stc* current;
  int collision;

  collision = 0;
  /* check collisions with player */
  if (game_collision_manager(&enemy->hitbox, &game->player.hitbox) > 0)
    collision += player_take_damage(1);

  /* check collisions with bullets */
  if (game->player.bullet_list != NULL)
  {
    current = game->player.bullet_list;
    while (current != NULL)
    {
      if (game_collision_manager(&enemy->hitbox, &current->hitbox) > 0)
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

void manage_enemies_collisions() {
  enemy_stc* current;
  enemy_stc* next;

  if (game->enemies->enemy_list != NULL)
  {
    current = game->enemies->enemy_list;
    while (current != NULL)
    {
      /* check if out of shot */
      if (check_enemy_collisions(current) > 0)
      {
        next = get_next_enemy(current);
        manage_enemy_damage(current);
        current = next;
      }
      else
        current = get_next_enemy(current);
    }
  }
}

void delete_enemy(enemy_stc* enemy) {
  /* setting the previous enemy pointer for "next enemy" as current enemy "next enemy" pointer */
  if (enemy->prev != NULL)
  {
    enemy->prev->next = enemy->next;
    if (enemy->next != NULL)
      enemy->next->prev = enemy->prev;
  }
  else
  {
    game->enemies->enemy_list = enemy->next;
    if (enemy->next != NULL)
      game->enemies->enemy_list->prev = NULL;
  }
  /* freeing enemy space */
  free(enemy);
}

void move_enemy(enemy_stc* enemy) {
  enemy->hitbox.x -= 1;
}

void render_enemy(enemy_stc* enemy) {
  SDL_RenderCopy(game->renderer, game->enemies->flyer_texture, NULL, &enemy->hitbox);
}

void manage_enemy(enemy_stc* enemy) {
  /* check if off screen on left */
  if (enemy->hitbox.x + enemy->hitbox.w < 0)
  {
    delete_enemy(enemy);
  }
  /* check if off screen on right */
  else if (enemy->hitbox.x > GAMEWIDTH)
  {
    move_enemy(enemy);
  }
  /* else, display */
  else
  {
    move_enemy(enemy);
    render_enemy(enemy);
  }
}

enemy_stc* get_next_enemy(enemy_stc* enemy) {
  return enemy->next;
}

void manage_enemy_list() {
  /* parse though enemies, to move and render them */
  enemy_stc* current;
  enemy_stc* next;

  if (game->enemies->enemy_list != NULL)
  {
    current = game->enemies->enemy_list;
    while (current != NULL)
    {
      next = get_next_enemy(current);
      manage_enemy(current);
      current = next;
    }
  }

  /* managing collisions */
  manage_enemies_collisions();
}

void create_enemy() {
  enemy_stc* enemy;

  /* setting enemy details */
  enemy = malloc(sizeof(enemy_stc));
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
  if (game->enemies->enemy_list != NULL)
  {
    enemy->next = game->enemies->enemy_list;
    game->enemies->enemy_list->prev = enemy;
  }
  else
    enemy->next = NULL;
  /* setting start of enemy list to current enemy */
  game->enemies->enemy_list = enemy;

}

void initialize_enemies() {
  /* initialize enemy list */
  game->enemies->enemy_list = NULL;

  /* loading flyer sprite */
  game->enemies->flyer_texture = IMG_LoadTexture(game->renderer, "img/fatcat.png");

  /* creating enemy for test purposes */
  create_enemy();


  /* setting bullet list to null */
  game->enemies->bullet_list = NULL;
}
