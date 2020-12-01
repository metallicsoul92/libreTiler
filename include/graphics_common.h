#ifndef GRAPHICS_COMMON_H_
#define GRAPHICS_COMMON_H_

//Library headers
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

struct _color{
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

typedef struct _color color_t;

#endif
