#ifndef WINDOW_H_
#define WINDOW_H_

struct _toolbar;

struct _window{
  char * title;
  int height;
  int width;
  SDL_Window * window;
  SDL_Renderer * renderer;
  struct _toolbar * gui;
};

typedef struct _window window_t;


void setupWindowEnvironment(window_t * out, const char * name, int height, int width);
void deleteWindow(window_t * out);
void resizeWindow(window_t * out, int x, int y);
#endif
