#include "../main/prototypes.h"

void init_player() {
  t_player* player;

  player = malloc(sizeof (t_player));
  g_game->player = player;
  player->hitbox.x = 10;
  player->hitbox.y = 200;
  player->hitbox.w = 45;
  player->hitbox.h = 30;
  player->speed    = 3;
  player->hp       = 3;
  player->cooldown = 0;
  player->damage_cooldown = 0;
  player->killed_by = -1;
  player->bullet_direction = 0;
  player->texture = IMG_LoadTexture(g_game->renderer, "assets/images/dubstepcat.png");
  init_player_actions();
  init_active_player_actions();
  player->bullet_list = NULL;
  render_player();
}

int player_bullet_direction() {
  return g_game->player->bullet_direction;
}

void set_bullet_direction_up() {
  if (g_game->player->bullet_direction > -1)
    g_game->player->bullet_direction -= 1;
}

void set_bullet_direction_down() {
  if (g_game->player->bullet_direction < 1)
    g_game->player->bullet_direction += 1;
}

void reset_bullet_direction() {
  g_game->player->bullet_direction = 0;
}

void init_player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    g_game->player->action_list[i] = NULL;

  g_game->player->action_list[32]  = &player_fire;
  g_game->player->action_list[97]  = &move_player_left;
  g_game->player->action_list[100] = &move_player_right;
  g_game->player->action_list[119] = &move_player_up;
  g_game->player->action_list[115] = &move_player_down;
  g_game->player->action_list[108] = &set_bullet_direction_down;
  g_game->player->action_list[111] = &set_bullet_direction_up;
}

void init_active_player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    g_game->player->active_actions[i] = 0;
}

void add_player_action() {
  if (g_game->event.key.keysym.sym <= 200)
    g_game->player->active_actions[g_game->event.key.keysym.sym] = 1;
}

void remove_player_action() {
  if (g_game->event.key.keysym.sym <= 200)
    g_game->player->active_actions[g_game->event.key.keysym.sym] = 0;
  if (g_game->event.key.keysym.sym == 108 || g_game->event.key.keysym.sym == 112)
    reset_bullet_direction();
}

void player_actions() {
  int i;

  for (i = 0; i < 200; i++)
    if (g_game->player->active_actions[i] == 1 && g_game->player->action_list[i] != NULL)
      g_game->player->action_list[i]();

  player_collisions();
  element_actions(&g_game->player->bullet_list);
  render_player();
}

int simulate_player_collision() {
  t_element* current;

  current = g_game->landscape->block_list;
  while (current != NULL)
  {
    if (collision_manager(&g_game->player->hitbox, &current->hitbox) > 0)
      return 1;
    else
      current = next_element(current);
  }
  return 0;
}

void player_collisions() {
  t_element* bullet;
  t_element* next;

  bullet = g_game->enemies->bullet_list;
  while (bullet != NULL)
  {
    next = next_element(bullet);
    if (collision_manager(&bullet->hitbox, &g_game->player->hitbox) > 0)
    {
      damage_player(1, bullet);
      remove_element(&g_game->enemies->bullet_list, bullet);
    }
    bullet = next;
  }
  /* go through power ups ? */
}

void move_player_left() {
  g_game->player->hitbox.x -= g_game->player->speed;

  if (g_game->player->hitbox.x < 0)
    g_game->player->hitbox.x += g_game->player->speed;
  else if (simulate_player_collision() > 0)
    g_game->player->hitbox.x += g_game->player->speed;
}

void move_player_right() {
  g_game->player->hitbox.x += g_game->player->speed;

  if (g_game->player->hitbox.x + g_game->player->hitbox.w > g_window_width)
    g_game->player->hitbox.x -= g_game->player->speed;
  else if (simulate_player_collision() > 0)
    g_game->player->hitbox.x -= g_game->player->speed;
}

void move_player_up() {
  g_game->player->hitbox.y -= g_game->player->speed;

  if (g_game->player->hitbox.y < 0)
    g_game->player->hitbox.y += g_game->player->speed;
  else if (simulate_player_collision() > 0)
    g_game->player->hitbox.y += g_game->player->speed;
}

void move_player_down() {
  g_game->player->hitbox.y += g_game->player->speed;

  if (g_game->player->hitbox.y + g_game->player->hitbox.h > g_window_height)
    g_game->player->hitbox.y -= g_game->player->speed;
  else if (simulate_player_collision() > 0)
    g_game->player->hitbox.y -= g_game->player->speed;
}

void player_fire() {
  t_element* bullet;

  if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->player->cooldown) == 1)
  {
    g_game->player->cooldown = SDL_GetTicks() + 300;
    bullet = malloc(sizeof(t_element));
    bullet->hitbox.x = g_game->player->hitbox.x + g_game->player->hitbox.w;
    bullet->hitbox.y = g_game->player->hitbox.y + (g_game->player->hitbox.h / 2);
    bullet->hitbox.w = 5;
    bullet->hitbox.h = 5;
    bullet->x = 5;
    bullet->y = 5 * player_bullet_direction();
    bullet->prev = NULL;
    bullet->type = 20;
    add_element(&g_game->player->bullet_list, bullet);
  }
}

void render_player() {
  SDL_Rect rect;

  rect.x = ((SDL_GetTicks() / 50) % 3) * 150;
  rect.y = 0;
  rect.w = 150;
  rect.h = 100;
  SDL_RenderCopy(g_game->renderer, g_game->player->texture, &rect, &g_game->player->hitbox);
}

int damage_player(int i, t_element* element) {
  if (SDL_TICKS_PASSED(SDL_GetTicks(), g_game->player->damage_cooldown) == 1)
  {
    g_game->player->hp -= i;
    if (g_game->player->hp <= 0)
      g_game->player->killed_by = element->parent;

    g_game->player->damage_cooldown = SDL_GetTicks() + 500;
    return 1;
  }
  else
    return 0;
}

void free_player() {
  free_element_list(&g_game->player->bullet_list);
  SDL_DestroyTexture(g_game->player->texture);
  free(g_game->player);
}
