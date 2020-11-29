#include "../include/graphics_common.h"
#include "../include/window.h"


#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480


//Remember, this implies the window_t is malloced or already in memory
void setupWindowEnvironment(window_t * out, const char * name, int height, int width){

//make sure valid height and width
//set outs width and height
  if(height == (int)NULL){
    out->height = DEFAULT_SCREEN_HEIGHT;
  }else
    out->height = height;


  if(width == (int)NULL){
    out->width = DEFAULT_SCREEN_WIDTH;
  }else
    out->width = width;


//set out's title
out->title = malloc(sizeof(char)* strlen(name)+1);
strcpy(out->title, name);


//create the window
out->window = SDL_CreateWindow(out->title,SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, out->width, out->height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
if(out->window == NULL){
              printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
}


//create renderer NOTE: SDL_RENDERER_ACCELERATED fails currently. i need drivers i guess
out->renderer = SDL_CreateRenderer(out->window,-1, 0 );
//create UI??

}


void resizeWindow(window_t * out, int x, int y){
  out->width = x;
  out->height = y;
  SDL_SetWindowSize(out->window,out->width, out->height);
  SDL_RenderClear(out->renderer);
  SDL_RenderPresent(out->renderer);
}


void deleteWindow(window_t * out){
  free(out->title);
  SDL_DestroyRenderer(out->renderer);
  SDL_DestroyWindow(out->window);
  free(out);
}
