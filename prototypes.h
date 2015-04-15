#ifndef SPACE_H_
# define SPACE_H_

struct  s_game;
struct  s_player;
struct  s_bullet;
struct  s_background;
struct  s_enemy;
struct  s_block;
struct  s_landscape;
struct  s_enemies;

typedef struct s_block {
  /* block hitbox */
  SDL_Rect              hitbox;
  /* block hp (-1 if unbreakable) */
  int                   hp;
  /* block type (solid top, solid bottom, breakable) */
  int                   type;
  /* previous block */
  struct s_block*  prev;
  /* next block */
  struct s_block*  next;
}t_block;

typedef struct s_bullet {
  /* bullet hitbox */
  SDL_Rect              hitbox;
  /* bullet direction x */
  int                   x;
  /* bullet direction x */
  int                   y;
  /* previous bullet */
  struct s_bullet* prev;
  /* next bullet */
  struct s_bullet* next;
}t_bullet;

typedef struct s_player {
  /* player hitbox */
  SDL_Rect      hitbox;
  /* player sprite */
  SDL_Texture*  texture;
  /* movement speed */
  int           speed;
  /* player hit points */
  int           hp;
  /* list of player actions */
  void          (*action_list[200])();
  /* active actions */
  int           active_actions[200];
  /* time for next shot */
  Uint32        cooldown;
  /* invulnerability period after taking period */
  Uint32        damage_cooldown;
  /* pointer on first bullet of list list */
  t_bullet*     bullet_list;
  /* bullet texture (not in bullet struc because we only need one texture for all bullets) */
  SDL_Texture   *bullet_texture;
}t_player;

typedef struct s_enemy {
  /* enemy hitbox */
  SDL_Rect              hitbox;
  /* enemy type : runner, jumper, flyer, mine, this will define his attack and movement paternes */
  int                   type;
  /* enemy life points */
  int                   hp;
  /* time for next shot */
  Uint32                cooldown;
  /* pointer on previous enemy */
  struct s_enemy*  prev;
  /* pointer on next enemy */
  struct s_enemy*  next;
}t_enemy;


typedef struct s_enemies {
  /* list of enemies */
  t_enemy*     enemy_list;
  /* mine texture */
  SDL_Texture    *mine_texture;
  /* runner texture */
  SDL_Texture    *runner_texture;
  /* jumper texture */
  SDL_Texture    *jumper_texture;
  /* flyer texture */
  SDL_Texture    *flyer_texture;
  /* enemies bullet list */
  t_bullet*    bullet_list;
}t_enemies;

typedef struct s_background {
  /* near */
  SDL_Rect       near;
  /* near texture */
  SDL_Texture    *near_texture;
  /* mid */
  SDL_Rect       mid;
  /* mid texture */
  SDL_Texture    *mid_texture;
  /* far */
  SDL_Rect       far;
  /* far texture */
  SDL_Texture    *far_texture;
}t_background;

typedef struct s_landscape {
  /* list of blocks */
  t_block*     block;
  /* breakable block texture */
  SDL_Texture    *breakable_texture;
  /* solid block top texture */
  SDL_Texture    *top_texture;
  /* solid block bottom texture */
  SDL_Texture    *bottom_texture;
}t_landscape;

typedef struct s_game {
  /* main screen */
  SDL_Window*    window;
  /* rendering tool */
  SDL_Renderer*  renderer;
  /* variable used to quit game */
  int            running;
  /* player */
  t_player     player;
  /* player input event */
  SDL_Event      event;
  /* duration of game */
  Uint32         timer;
  /* duration of game */
  int            score;
  /* parallax background */
  t_background   background;
  /* landscape */
  t_landscape landscape;
  /* enemies */
  t_enemies*   enemies;
}t_game;

void         init_player();
void         render_player();
void         add_player_action();
void         remove_player_action();
void         move_player_left();
void         move_player_right();
void         move_player_up();
void         move_player_down();
void         init_player_actions();
void         player_fire();
void         init_active_player_actions();
void         player_actions();
int          init_game();
int          init_background();
void         end_game();
void         clear_window();
void         render_window();
void         move_bullet(t_bullet*);
void         render_player_bullet(t_bullet*);
void         delete_player_bullet(t_bullet*);
void         free_player_bullets();
int          event_switcher();
int          error();
void         init_enemies();
void         create_enemy();
void         render_enemy();
void         delete_enemy();
void         free_enemies();
void         player_bullets();
void         game_actions();
void         background_actions();
t_bullet*    get_next_bullet(t_bullet*);
void         delete_enemy_bullet(t_bullet*);
void         enemy_bullets();
void         enemies_actions();
void         landscape_actions();
void         init_landscape();
void         create_landscape_top_block(int, int, int);
void         create_landscape_breakable_block(int, int, int, int);
void         create_landscape_bottom_block(int, int, int);
void         delete_landscape_block();
void         free_landscape_blocks();
void         move_lanscape_block();
void         render_landscape_block();
t_block*     get_next_block(t_block*);
void         move_landscape_block();
void         free_background();
SDL_Texture* get_landscape_block_texture(int);
void         free_landscape_textures();
int          check_landscape_collisions(t_block*);
int          collision_manager(SDL_Rect*, SDL_Rect*);
int          check_top_left_collision(SDL_Rect*, SDL_Rect*);
int          check_top_right_collision(SDL_Rect*, SDL_Rect*);
int          check_bottom_right_collision(SDL_Rect*, SDL_Rect*);
int          check_bottom_left_collision(SDL_Rect*, SDL_Rect*);
void         landscape_collisions();
void         landscape_damage(t_block*);
int          simulate_player_collision();
void         manage_enemy_list();
void         manage_enemy(t_enemy*);
void         move_enemy(t_enemy*);
t_enemy*     get_next_enemy(t_enemy*);
int          check_enemy_collisions(t_enemy*);
void         damage_enemy(t_enemy*);
int          damage_player(int);
void         free_player();
void         free_landscape();
void         free_enemy_list();
void         check_enemy_fire(t_enemy*);
void         custom_enemy_movement(t_enemy*);
void         enemy_fire();
void         move_bullet(t_bullet*);
void         render_enemy_bullet(t_bullet*);
void         enemy_bullet_direction(t_bullet*);
void         player_collisions();
void         enemies_collisions();

t_game* g_game;

int g_window_height;
int g_window_width;

#endif /*!SPACE_H_*/
