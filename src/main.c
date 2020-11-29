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
bool isRunning = true;

if(TTF_Init()==-1) {
    printf("TTF_Init: %s\n", TTF_GetError());
    exit(2);
}
font_Load();
setupWindowEnvironment(g_window,name,(int)NULL,(int)NULL);

renderWindow(g_window);
SDL_RenderPresent(g_window->renderer);

SDL_Event event;
  while(isRunning){
    if(SDL_PollEvent(&event)){

      if(event.type == SDL_QUIT){
        isRunning=false;
      }

      if(event.type == SDL_WINDOWEVENT){
        if(event.window.event == SDL_WINDOWEVENT_RESIZED){
          printf("Window resized to : %dx %dy\n",event.window.data1, event.window.data2);
          resizeWindow(g_window,event.window.data1, event.window.data2);
          renderToolbar(g_window->gui);
          SDL_RenderPresent(g_window->renderer);
        }
      }


      if(event.type == SDL_MOUSEMOTION){
        setMouseInfo(&g_input,event.motion.x, event.motion.y);
        printf("Mouse moved to X:%d , Y:%d\n",g_input.mouse_x , g_input.mouse_y);
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
