#ifndef SPACE_H_
# define SPACE_H_

struct  game_struct;
struct  player_struct;
struct  bullet_struct;
struct  background_struct;
struct  enemy_struct;

typedef struct bullet_struct {
  /* bullet hitbox */
  SDL_Rect              hitbox;
  /* next bullet */
  struct bullet_struct* next;
}bullet_stc;

typedef struct player_struct {
  /* player hitbox */
  SDL_Rect      hitbox;
  /* player sprite */
  SDL_Texture*  image;
  /* movement speed */
  int           speed;
  /* player hit points */
  int           hp;
  /* list of player actions */
  void          (*actionList[200])();
  /* active actions */
  int           activeActions[200];
  /* time for next shot */
  Uint32        cooldown;
  /* pointer on first bullet of list list */
  bullet_stc*   bulletList;
  /* bullet texture (not in bullet struc because we only need one texture for all bullets) */
  SDL_Texture   *bulletTxtr;
}player_stc;

typedef struct enemy_struct {
  /* player hitbox */
  SDL_Rect              hitbox;
  /* player sprite */
  SDL_Texture*          image;
  /* enemy id, to make finding him easier */
  int                   id;
  /* movement speed */
  int                   speed;
  /* time for next shot */
  Uint32                cooldown;
  /* pointer on next enemy */
  struct enemy_struct*  next;
}enemy_stc;

typedef struct background_struct {
  /* near */
  SDL_Rect       near;
  /* near texture */
  SDL_Texture    *nearTxtr;
  /* mid */
  SDL_Rect       mid;
  /* mid texture */
  SDL_Texture    *midTxtr;
  /* far */
  SDL_Rect       far;
  /* far texture */
  SDL_Texture    *farTxtr;
}backgrnd_stc;

typedef struct game_struct {
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
  /* parallax background */
  backgrnd_stc   background;
  /* enemy list */
  enemy_stc*     enemies;
  /* enemy texture */
  SDL_Texture    *enemyTxtr;
  /* enemy bullet list */
  bullet_stc*    enemyBulletList;
}game_stc;

void    initializePlayer();
void    drawPlayer();
void    addPlayerAction();
void    removePlayerAction();
void    movePlayerLeft();
void    movePlayerRight();
void    fire();
void    initializeActiveActions();
void    parsePlayerActions();
int     initializeGame();
int     initializeBackground();
void    endGame(game_stc* game);
void    clearWindow();
void    renderScreen();
void    manageBulletList();
void    moveBullet(bullet_stc*);
void    renderBullet(bullet_stc*);
void    freeBulletList();
int     eventSwitcher();
int     error();

game_stc* game;

#endif /*!SPACE_H_*/
