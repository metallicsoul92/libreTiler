// Standard headers
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>



//User Defined Headers
#include "../include/graphics_common.h"
#include "../include/window.h"
#include "../include/gui.h"
#include "../include/input.h"
//constants
const char * name = "Libre Tiler 0.0";

//globals
window_t * g_window;
input_t g_input;
int main(int argc, char *argv[]){

g_window = malloc(sizeof(window_t));
printf("%s\n" ,name);
if(SDL_Init(SDL_INIT_VIDEO) < 0 ){
  printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
}else{


if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
}
font_Load();
setupWindowEnvironment(g_window,name,(int)NULL,(int)NULL);
g_input.parent = g_window;
renderWindow(g_window);
SDL_RenderPresent(g_window->renderer);

SDL_Event event;
  while(g_window->isRunning){
    if(SDL_PollEvent(&event)){

      if(event.type == SDL_QUIT){
        g_window->isRunning=false;
      }

      if(event.type == SDL_WINDOWEVENT){
        if(event.window.event == SDL_WINDOWEVENT_RESIZED){
          printf("Window resized to : %dx %dy\n",event.window.data1, event.window.data2);
          uint16_t oldw = g_window->width;
          uint16_t oldh = g_window->height;
          resizeWindow(g_window,oldw, oldh, event.window.data1, event.window.data2);
          SDL_RenderPresent(g_window->renderer);
        }
      }


      if(event.type == SDL_MOUSEMOTION){
        setMouseInfo(&g_input,event.motion.x, event.motion.y);
        printf("Mouse moved to X:%d , Y:%d\n",g_input.mouse_x , g_input.mouse_y);
      }

      if(event.type == SDL_MOUSEBUTTONDOWN){
        if(event.button.button == SDL_BUTTON_LEFT){
          setMouseInfo(&g_input,event.button.x, event.button.y);
          printf("Left mouse pressed at %d , %d\n",g_input.mouse_x, g_input.mouse_y);
          determineClick(&g_input);
          SDL_RenderPresent(g_window->renderer);
          for(int i = 0; i < g_window->gui->count; i++){
            printf("%s %s", g_window->gui->toolbarItemList[i].name ,
            g_window->gui->toolbarItemList[i].isHighlighted ? "is highlighted\n" :
            "is not highlighted\n");
          }
      }
    }


  }

}
  //Destroy window
  deleteWindow(g_window);
  closeFont();
  //Quit TTF
  TTF_Quit();
  //Quit SDL subsystems
  SDL_Quit();
}
  printf("Closed Successfully.\n");
  return 0;
}
