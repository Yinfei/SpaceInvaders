#ifndef SPACE_H_
# define SPACE_H_

struct  game_struct;
struct  player_struct;
struct  bullet_struct;
struct  background_struct;

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
  void          (*actionList[200])(struct game_struct*);
  /* active actions */
  int           activeActions[200];
  /* time for next shot */
  Uint32        cooldown;
  /* pointer on first bullet of list list */
  bullet_stc*   bulletList;
  /* bullet texture (not in bullet struc because we only need one texture for all bullets) */
  SDL_Texture   *bulletTxtr;
}player_stc;

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
  /* player */
  player_stc     player;
  /* player input event */
  SDL_Event      event;
  /* duration of game */
  Uint32         timer;
  /* parallax background */
  backgrnd_stc   background;
}game_stc;

void    initializePlayer(game_stc*);
void    drawPlayer(game_stc*);
void    addPlayerAction(game_stc*);
void    removePlayerAction(game_stc*);
void    movePlayerLeft(game_stc*);
void    movePlayerRight(game_stc*);
void    fire(game_stc*);
void initializeActiveActions(game_stc*);
void    parsePlayerActions(game_stc*);
int     initializeGame(game_stc*);
int     initializeBackground(game_stc*);
void    endGame(game_stc* game);
void    clearWindow(game_stc*);
void    renderScreen(game_stc*);
void    manageBulletList(game_stc*);
void    moveBullet(bullet_stc*);
void    renderBullet(game_stc*, bullet_stc*);
void    freeBulletList(game_stc*);
int     eventSwitcher(game_stc*);
int     error();

#endif /*!SPACE_H_*/
