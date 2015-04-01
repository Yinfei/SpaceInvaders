#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <stdio.h>

//////////////////////////////////// STRUCTURES and HEADERS ////////////////////////////////////
struct game_struct;
struct player_struct;

// PUT game as a global ?

typedef struct bullet_struct {
  // bullet hitbox
  SDL_Rect              hitbox;
  // texture
  SDL_Texture*          bulletTxtr;
  // next bullet
  struct bullet_struct* next;
}bullet_stc;

typedef struct player_struct {
  // player hitbox
  SDL_Rect      hitbox;
  // player sprite
  SDL_Texture*  image;
  // movement speed
  int           speed;
  // player hit points
  int           hp;
  // list of player actions
  void          (*actionList[200])(struct game_struct*);
  // active actions
  int           activeActions[200];
  // time for next shot
  Uint32        cooldown;
  // pointer on first bullet of list list
  bullet_stc**   bulletList;
}player_stc;

typedef struct background_struct {
  // near
  SDL_Rect       near;
  // near texture
  SDL_Texture    *nearTxtr;
  // mid
  SDL_Rect       mid;
  // mid texture
  SDL_Texture    *midTxtr;
  // far
  SDL_Rect       far;
  // far texture
  SDL_Texture    *farTxtr;
}backgrnd_stc;

typedef struct game_struct {
  // main screen
  SDL_Window*    window;
  // rendering tool
  SDL_Renderer*  renderer;
  // player
  player_stc     player;
  // player input event
  SDL_Event      event;
  // duration of game
  Uint32         timer;
  // parallax background
  backgrnd_stc   background;
}game_stc;

void  endGame(game_stc*);
void  drawPlayer(game_stc*);
void  addPlayerAction(game_stc*);
void  removePlayerAction(game_stc*);
void  movePlayerLeft(game_stc*);
void  movePlayerRight(game_stc*);
void  fire(game_stc*);
void  initializePlayer(game_stc*);
int   initializeBackground(game_stc*);
int   initializeGame(game_stc*);
void  clearWindow(game_stc*);
int   eventSwitcher(game_stc*);
void  renderScreen(game_stc*);
int   error(game_stc*);


///////////////////////////////////////// FUNCTIONS /////////////////////////////////////////

void endGame(game_stc* game) {
  // free background textures
  SDL_DestroyTexture(game->background.nearTxtr);
  SDL_DestroyTexture(game->background.midTxtr);
  SDL_DestroyTexture(game->background.farTxtr);

  // destroy window
  SDL_DestroyWindow(game->window);
  // exit SDL
  SDL_Quit();
}

void drawPlayer(game_stc* game) {
  // Set render color to blue (player will be rendered in this color)
  SDL_SetRenderDrawColor(game->renderer,0,0,255,255);
  // Render player hitbox
  SDL_RenderFillRect(game->renderer, &game->player.hitbox);
}

void addPlayerAction(game_stc* game) {
  // only doing a few, because fuck you for the moment
  if (game->event.key.keysym.sym == 32 || game->event.key.keysym.sym == 113 || game->event.key.keysym.sym == 119)
    game->player.activeActions[game->event.key.keysym.sym] = 1;
}

void removePlayerAction(game_stc* game) {
  // only doing a few, because fuck you for the moment
  if (game->event.key.keysym.sym == 32 || game->event.key.keysym.sym == 113 || game->event.key.keysym.sym == 119)
    game->player.activeActions[game->event.key.keysym.sym] = 0;
}

void movePlayerLeft(game_stc* game) {
  if (game->player.hitbox.x - game->player.speed >= 0)
  {
    game->player.hitbox.x -= game->player.speed;

    // move background;
    game->background.mid.x -= 1;
    game->background.near.x -= 2;
  }
}

void movePlayerRight(game_stc* game) {
  if (game->player.hitbox.x + game->player.hitbox.w + game->player.speed <= 640)
  {
    game->player.hitbox.x += game->player.speed;

    // move background;
    game->background.mid.x += 1;
    game->background.near.x += 2;
  }
}

void renderBullet(game_stc* game, bullet_stc* bullet) {

  printf("bullet x:%d y:%d w:%d h:%d\n", bullet->hitbox.x, bullet->hitbox.y, bullet->hitbox.w, bullet->hitbox.h);

  // Set render color to red (bullet will be rendered in this color)
  SDL_SetRenderDrawColor(game->renderer,255,0,0,255);
  // Render player hitbox
  SDL_RenderFillRect(game->renderer, &bullet->hitbox);
}

void manageBulletList(game_stc* game) {
  if (game->player.bulletList != NULL)
  {
    // save value of first bullet;
    bullet_stc* first;

    first = *game->player.bulletList;

    // creating values to parsethough
    bullet_stc* current = *game->player.bulletList;

    printf("starting loop\n");
    printf("%d\n", current->hitbox.x);

    // parse through each bullet, render each one
    while (current != NULL)
    {
      renderBullet(game, current);
      printf("loop\n");
      if (current->next != NULL)
        current = current->next;
      else
        current = NULL;
    }

    printf("end loop\n");

    // re asign game.bulletList to first bullet occurence.
    game->player.bulletList = &first;
  }
}

void fire(game_stc* game) {
  if (SDL_TICKS_PASSED(SDL_GetTicks(), game->player.cooldown) == 1)
  {
    game->player.cooldown = SDL_GetTicks() + 400;

    printf("FIRE !\n");
    // bullet_stc* bullet;

    // bullet = malloc(sizeof(bullet_stc));

    // bullet->hitbox.x = game->player.hitbox.x;
    // bullet->hitbox.y = game->player.hitbox.y;
    // bullet->hitbox.w = 2;
    // bullet->hitbox.h = 2;

    // if (game->player.bulletList != NULL)
    //   bullet->next = *game->player.bulletList;
    // else
    //   bullet->next = NULL;

    // // setting start of bullet list to current bullet
    // printf("try\n");
    // game->player.bulletList = &bullet;
    // printf("yes\n");
    // printf("%d\n", game->player.bulletList.hitbox.x);






  }
}

void initializePlayer(game_stc* game) {
  // setting initial position
  game->player.hitbox.x = 310;
  game->player.hitbox.y = 380;
  // setting size of hitbox
  game->player.hitbox.w = 30;
  game->player.hitbox.h = 30;

  // how many pixels will he move every 16ms
  game->player.speed    = 3;
  // how many times can he be hit
  game->player.hp       = 3;
  // if ever this time has passed, he can shot again
  game->player.cooldown = 0;

  // Initialize player action list
  game->player.actionList[32]  = &fire;
  game->player.actionList[113] = &movePlayerLeft;
  game->player.actionList[119] = &movePlayerRight;

  // initialize player activeActions to 0;
  int i;
  for (i = 0; i < 200; i++)
    game->player.activeActions[i] = 0;


  // configure bullet;
  game->player.bulletList = NULL;

  // putting player on window, ready for next render
  drawPlayer(game);
}

int initializeBackground(game_stc* game) {
  // setting box for near
  game->background.near.x = -640;
  game->background.near.y = 0;
  game->background.near.w = 1920;
  game->background.near.h = 420;

  // setting box for mid
  game->background.mid.x = -320;
  game->background.mid.y = 0;
  game->background.mid.w = 1280;
  game->background.mid.h = 420;

  // setting box for far
  game->background.far.x = 0;
  game->background.far.y = 0;
  game->background.far.w = 640;
  game->background.far.h = 420;

  // applying textures on boxes
  game->background.nearTxtr  = IMG_LoadTexture(game->renderer, "img/near.png");
  game->background.midTxtr   = IMG_LoadTexture(game->renderer, "img/mid.png");
  game->background.farTxtr   = IMG_LoadTexture(game->renderer, "img/far.png");

  return 0;
}

int initializeGame(game_stc* game) {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVENTS) < 0)
    return -1;

  // initializing window   (title, posx, posy, width, height,  )
  game->window = SDL_CreateWindow("Water Evaders",100,200,640,420,0);

  // initializing renderer   (window, index, rendering flags)
  game->renderer = SDL_CreateRenderer(game->window,-1,0);

  // initialize timer
  game->timer = SDL_GetTicks();

  // setting all textures and loading images
  initializeBackground(game);

  // call to initialize player
  initializePlayer(game);
  return 0;
}

void clearWindow(game_stc* game) {
  // clear screen
  SDL_RenderClear(game->renderer);

  // render each background layer (far to near)
  SDL_RenderCopy(game->renderer, game->background.farTxtr, NULL, &game->background.far);
  SDL_RenderCopy(game->renderer, game->background.midTxtr, NULL, &game->background.mid);
  SDL_RenderCopy(game->renderer, game->background.nearTxtr, NULL, &game->background.near);
}

void parsePlayerActions(game_stc* game) {
  int i;

  for (i = 0; i < 200; i++)
    if (game->player.activeActions[i] == 1)
      game->player.actionList[i](game);
}

int eventSwitcher(game_stc* game) {
  // clear screen
  clearWindow(game);

  // checking if player quits game
  if (SDL_HasEvent(SDL_QUIT) || game->event.type == SDL_QUIT)
    return -1;

  // call to function to add/remove player actions
  if (game->event.type == SDL_KEYDOWN)
    addPlayerAction(game);
  else if (game->event.type == SDL_KEYUP)
    removePlayerAction(game);

  // going through each performable action
  parsePlayerActions(game);

  drawPlayer(game);

  // parse through bullets
  manageBulletList(game);

  // check player actions. {powerup, takeDamage, die}
  // check enemy actions. {move, shoot, die}
  // check game actions. {animate background, change music, powerUps}
  return 0;
}

void renderScreen(game_stc* game) {
  // Render window
  SDL_RenderPresent(game->renderer);
}

int error(game_stc* game) {
  printf("some sort of error message game->error\n");
  return -1;
}


/////////////////////////////////////////// MAIN ///////////////////////////////////////////



int main (int argc, char** argv)
{
  game_stc game;

  // initializing game
  if (initializeGame(&game) < 0)
    return error(&game);
  // starting main game loop
  while (1)
  {
    // catching events
    SDL_PollEvent(&game.event);
    // check if 16 ms have gone by since last render
    if (SDL_TICKS_PASSED(SDL_GetTicks(), game.timer) == 1)
    {
      // setting next game render time
      game.timer = SDL_GetTicks() + 16;
      // check if player quits game, parse game and player actions
      if (eventSwitcher(&game) != -1)
        // render game screen
        renderScreen(&game);
      else
        // exit
        break;
    }
    else
      // waiting 16 ms (to make sure we are around 60 FPS)
      SDL_Delay(16);
  }
  // clean up game, and exit SDL
  endGame(&game);
  // quit
  return EXIT_SUCCESS;
}
