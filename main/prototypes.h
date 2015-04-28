#ifndef SPACE_H_
# define SPACE_H_
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2_Mixer/SDL_Mixer.h>
#include <stdio.h>
#include <stdlib.h>

struct  s_game;
struct  s_player;
struct  s_background;
struct  s_element;
struct  s_landscape;
struct  s_enemies;

typedef struct s_element {
  SDL_Rect              hitbox;
  int                   type;
  int                   parent;
  int                   hp;
  struct s_element*     prev;
  struct s_element*     next;
  int                   x;
  int                   y;
  int                   init_x;
  int                   init_y;
  Uint32                cooldown;
  int                   points;
  float                 timeline;
}t_element;

typedef struct s_lifebox {
  SDL_Rect      box;
  SDL_Texture*  texture;
}t_lifebox;

typedef struct s_player {
  SDL_Rect      hitbox;
  SDL_Texture*  texture;
  int           speed;
  int           hp;
  t_lifebox*    lifebox;
  void          (*action_list[200])();
  int           active_actions[200];
  Uint32        cooldown;
  Uint32        damage_cooldown;
  t_element*    bullet_list;
  SDL_Texture   *bullet_texture;
  int           killed_by;
  int           won;
  int           bullet_direction;
}t_player;

typedef struct s_enemies {
  t_element*     enemy_list;
  t_element*     bullet_list;
  char*          names[10];
  int            hp[10];
  int            points[10];
  void           (*movements[10])();
  void           (*fire[10])();
}t_enemies;

typedef struct s_background {
  SDL_Rect       near;
  SDL_Texture    *near_texture;
  SDL_Rect       mid;
  SDL_Texture    *mid_texture;
  SDL_Rect       far;
  SDL_Texture    *far_texture;
}t_background;

typedef struct s_landscape {
  t_element*     block_list;
  SDL_Texture    *breakable_texture;
  SDL_Texture    *top_texture;
  SDL_Texture    *bottom_texture;
}t_landscape;

typedef struct s_jukebox {
  Mix_Music*     music[3];
  Mix_Chunk*     soundboard[10];
}t_jukebox;

typedef struct s_writer {
  TTF_Font*   font;
  SDL_Color   color;
  SDL_Rect    box;
}t_writer;

typedef struct s_choice_screen {
  int           (*launcher[6])();
  SDL_Texture*  textures[6];
  SDL_Rect      buttons[6];
  int           selected;
}t_choice_screen;

typedef struct s_game {
  SDL_Window*       window;
  SDL_Renderer*     renderer;
  t_choice_screen*  menu;
  t_choice_screen*  gameover;
  t_choice_screen*  congratulations;
  t_player*         player;
  SDL_Event         event;
  Uint32            timer;
  int               score;
  int               running;
  t_writer*         writer;
  t_background      background;
  t_landscape*      landscape;
  t_enemies*        enemies;
  SDL_Texture*      textures[30];
  int               (*element_conditions[30])();
  int               (*element_collisions[30])();
  t_jukebox         jukebox;
}t_game;

void         init_player();
void         init_player_actions();
void         init_active_player_actions();
void         add_player_action();
void         remove_player_action();
void         move_player_left();
void         move_player_right();
void         move_player_up();
void         move_player_down();
void         player_fire();
void         player_actions();
int          simulate_player_collision();
void         render_player();
void         free_player();
void         init_enemies();
void         create_enemy();
void         enemies_actions();
int          init_game();
void         init_textures();
void         clear_window();
void         render_window();
int          event_switcher();
void         game_actions();
t_element*   next_element(t_element*);
int          collision_manager(SDL_Rect*, SDL_Rect*);
int          check_top_left_collision(SDL_Rect*, SDL_Rect*);
int          check_top_right_collision(SDL_Rect*, SDL_Rect*);
int          check_bottom_right_collision(SDL_Rect*, SDL_Rect*);
int          check_bottom_left_collision(SDL_Rect*, SDL_Rect*);
void         init_element_conditions();
void         init_element_collisions();
void         add_element(t_element**, t_element*);
void         remove_element(t_element**, t_element*);
int          damage_element(t_element**, t_element*);
void         free_element_list(t_element**);
void         element_actions(t_element**);
int          element_conditions(t_element*);
int          element_collisions(t_element*);
int          element_list_collision(t_element**, t_element*);
void         move_element(t_element*);
SDL_Texture* element_texture(t_element*);
void         render_element(t_element*);
int          is_animated(t_element*);
SDL_Rect     crop_texture(t_element*, SDL_Rect);
int          off_window_left(t_element*);
int          off_window_right(t_element*);
int          init_background();
void         background_actions();
void         free_background();
void         init_landscape();
void         free_landscape();
int          landscape_collision(t_element*);
int          damage_player(int, t_element*);
void         free_enemies();
void         free_game();
int          game_state();
void         create_block(int, int, int);
void         extra_actions(t_element*);
void         enemy_fire(t_element*);
void         enemy_bullet_direction(t_element*, t_element*);
int          enemy_collision(t_element*);
void         enemy_movement(t_element*);
void         player_collisions();
void         init_enemies_hp(t_enemies*);
int          player_bullet_direction();
void         set_bullet_direction_up();
void         set_bullet_direction_down();
void         reset_bullet_direction();
int          enemy_hp(int);
int          error();
int          init_audio();
void         init_music();
void         init_soundboard();
void         free_audio();
int          init_score();
void         free_score();
void         render_score();
int          enemy_points(int);
void         init_enemies_points(t_enemies*);
int          init_score();
void         free_score();
void         render_score();
int          init_game_elements();
int          launch_game();
int          menu_event_switcher();
int          init_menu();
void         create_menu_button(int);
void         init_menu_textures();
void         free_menu_textures();
void         free_menu();
void         render_background();
void         render_choice_screen();
int          launch_menu();
int          exit_game();
int          highscores();
int          launcher_loop();
char*        enemy_name(int);
void         init_enemies_names();
void         render_gameover();
void         render_gameover_text();
int          loop_gameover();
void         render_killer();
void         render_gameover_background();
void         init_enemies_movements();
void         enemy_mouvement_vertical();
void         enemy_mouvement_none();
void         enemy_movement_rotate();
void         init_enemy_fire();
void         enemy_default_fire(t_element*);
void         init_player_lifebox();
void         render_player_hp();

t_game*      g_game;
int          g_window_height;
int          g_window_width;

#endif /*!SPACE_H_*/
