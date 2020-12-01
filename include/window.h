#ifndef WINDOW_H_
#define WINDOW_H_

#ifndef STDBOOL_DEFINED
#include <stdbool.h>
#define STDBOOL_DEFINED 1
#endif

typedef struct _toolbar toolbar_t;
typedef struct _frame frame_t;



struct _window{
  char * title;
  int height;
  int width;
  SDL_Window * window;
  SDL_Renderer * renderer;
  toolbar_t * gui;
  uint8_t frameCount;
  uint8_t frameMax;
  frame_t *frames;
  bool isRunning;
};

typedef struct _window window_t;


void setupWindowEnvironment(window_t * out, const char * name, int height, int width);
void deleteWindow(window_t * out);
void resizeWindow(window_t * out, int dx, int dy, int x, int y);
void renderWindow(window_t * out);


#endif
