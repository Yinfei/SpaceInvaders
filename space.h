#ifndef SPACE_H_
# define SPACE_H_

struct  Game_struct;
struct  Player_struct;
struct  Bullet_struct;
struct  Background_struct;
struct  Enemy_struct;
struct  Block_struct;
struct  Landscape_struct;
struct  Enemies_struct;

typedef struct Block_struct {
  /* block hitbox */
  SDL_Rect              hitbox;
  /* block texture */
  SDL_Texture           *texture;
  /* block hp (-1 if unbreakable) */
  int                   hp;
  /* block type (solid top, solid bottom, breakable) */
  int                   type;
  /* previous block */
  struct Block_struct*  prev;
  /* next block */
  struct Block_struct*  next;
}block_stc;

typedef struct Bullet_struct {
  /* bullet hitbox */
  SDL_Rect              hitbox;
  /* bullet texture */
  SDL_Texture           *texture;
  /* bullet direction x */
  int                   x;
  /* bullet direction x */
  int                   y;
  /* previous bullet */
  struct Bullet_struct* prev;
  /* next bullet */
  struct Bullet_struct* next;
}bullet_stc;

typedef struct Player_struct {
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
  bullet_stc*   bullet_list;
  /* bullet texture (not in bullet struc because we only need one texture for all bullets) */
  SDL_Texture   *bullet_texture;
}player_stc;

typedef struct Enemy_struct {
  /* enemy hitbox */
  SDL_Rect              hitbox;
  /* enemy type : runner, jumper, flyer, mine, this will define his attack and movement paternes */
  int                   type;
  /* enemy life points */
  int                   hp;
  /* time for next shot */
  Uint32                cooldown;
  /* pointer on previous enemy */
  struct Enemy_struct*  prev;
  /* pointer on next enemy */
  struct Enemy_struct*  next;
}enemy_stc;


typedef struct Enemies_struct {
  /* list of enemies */
  enemy_stc*     enemy_list;
  /* mine texture */
  SDL_Texture    *mine_texture;
  /* runner texture */
  SDL_Texture    *runner_texture;
  /* jumper texture */
  SDL_Texture    *jumper_texture;
  /* flyer texture */
  SDL_Texture    *flyer_texture;
  /* enemies bullet list */
  bullet_stc*    bullet_list;
}enemies_stc;

typedef struct Background_struct {
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
}backgrnd_stc;

typedef struct Landscape_struct {
  /* list of blocks */
  block_stc*     block;
  /* breakable block texture */
  SDL_Texture    *breakable_texture;
  /* solid block top texture */
  SDL_Texture    *top_texture;
  /* solid block bottom texture */
  SDL_Texture    *bottom_texture;
}landscape_stc;

typedef struct Game_struct {
  /* main screen */
  SDL_Window*    window;
  /* rendering tool */
  SDL_Renderer*  renderer;
  /* variable used to quit game */
  int            running;
  /* player */
  player_stc     player;
  /* player input event */
  SDL_Event      event;
  /* duration of game */
  Uint32         timer;
  /* duration of game */
  int            score;
  /* parallax background */
  backgrnd_stc   background;
  /* landscape */
  landscape_stc landscape;
  /* enemies */
  enemies_stc*   enemies;
}game_stc;

void         initialize_player();
void         draw_player();
void         add_player_action();
void         remove_player_action();
void         move_player_left();
void         move_player_right();
void         move_player_up();
void         move_player_down();
void         initialize_player_actions();
void         fire();
void         initialize_active_player_actions();
void         manage_player_actions();
int          initialize_game();
int          initialize_background();
void         end_game();
void         clear_window();
void         render_screen();
void         move_bullet(bullet_stc*);
void         draw_player_bullet(bullet_stc*);
void         delete_player_bullet(bullet_stc*);
void         free_player_bullets();
int          event_switcher();
int          error();
void         initialize_enemies();
void         create_enemy();
void         render_enemy();
void         delete_enemy();
void         free_enemies();
void         manage_player_bullets();
void         manage_game_actions();
void         manage_background_actions();
bullet_stc*  get_next_bullet(bullet_stc*);
void         delete_enemy_bullet(bullet_stc*);
void         manage_enemy_bullets();
void         manage_enemies_actions();
void         manage_landscape_actions();
void         initialize_landscape();
void         create_landscape_top_block(int, int, int);
void         create_landscape_breakable_block(int, int, int, int);
void         create_landscape_bottom_block(int, int, int);
void         delete_landscape_block();
void         free_landscape_blocks();
void         move_lanscape_block();
void         render_landscape_block();
block_stc*   get_next_block(block_stc*);
void         move_landscape_block();
void         free_background();
SDL_Texture* get_landscape_block_texture(int);
void         free_landscape_textures();
int          check_landscape_block_collisions(block_stc*);
int          game_collision_manager(SDL_Rect*, SDL_Rect*);
int          check_top_left_collision(SDL_Rect*, SDL_Rect*);
int          check_top_right_collision(SDL_Rect*, SDL_Rect*);
int          check_bottom_right_collision(SDL_Rect*, SDL_Rect*);
int          check_bottom_left_collision(SDL_Rect*, SDL_Rect*);
void         manage_landscape_collisions();
void         manage_landscape_damage(block_stc*);
int          simulate_player_collision();
void         manage_enemy_list();
void         manage_enemy(enemy_stc*);
void         move_enemy(enemy_stc*);
enemy_stc*   get_next_enemy(enemy_stc*);
int          check_enemy_collisions(enemy_stc*);
void         manage_enemy_damage(enemy_stc*);
int          player_take_damage(int);
void         free_player();
void         free_landscape();
void         free_enemy_list();
void         check_enemy_fire(enemy_stc*);
void         execute_custom_enemy_movement(enemy_stc*);
void         enemy_fire();
void         move_bullet(bullet_stc*);
void         draw_enemy_bullet(bullet_stc*);
void         set_enemy_bullet_direction(bullet_stc*);
void         manage_player_collisions();

game_stc* game;

int GAMEHEIGHT;
int GAMEWIDTH;

#endif /*!SPACE_H_*/
