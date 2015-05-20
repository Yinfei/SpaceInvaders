#include "../../main/prototypes.h"

SDL_Texture* element_texture(t_element* element) {
  return g_game->textures[element->type];
}

SDL_Rect crop_texture(t_element* element, SDL_Rect rec) {
  if (element->type == 12)
  {
    rec.x = 200 * (element->hp - 1);
    rec.y = 0;
    rec.w = 200;
    rec.h = 200;
  }
  return rec;
}

int is_animated(t_element* element) {
  int i;
  int allowed[1];

  allowed[0] = 12;
  for (i = 0; i < 1; i++)
    if (allowed[i] == element->type)
      return 1;
  return 0;
}

void render_element(t_element* element) {
  SDL_Rect rec;

  if (is_animated(element) == 1)
  {
    rec = crop_texture(element, rec);
    SDL_RenderCopy(g_game->renderer, element_texture(element), &rec, &element->hitbox);
  }
  else
    SDL_RenderCopy(g_game->renderer, element_texture(element), NULL, &element->hitbox);
}
