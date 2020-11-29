#ifndef WINDOW_H_
#define WINDOW_H_

#ifndef STDBOOL_DEFINED
#include <stdbool.h>
#define STDBOOL_DEFINED 1
#endif

struct _toolbar;
struct _window{
  char * title;
  int height;
  int width;
  SDL_Window * window;
  SDL_Renderer * renderer;
  struct _toolbar * gui;
  bool isRunning;
};

typedef struct _window window_t;


void setupWindowEnvironment(window_t * out, const char * name, int height, int width);
void deleteWindow(window_t * out);
void resizeWindow(window_t * out, int x, int y);
void renderWindow(window_t * out);


#endif
