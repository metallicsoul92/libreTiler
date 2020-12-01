#include "../../include/gui.h"
//#include "../../include/graphics_common.h"
#include "../../include/window.h"


void allocateFrame(frame_t * out,window_t * parent , uint16_t x,
                    uint16_t y, uint16_t w, uint16_t h){
  out->posX = x;
  out->posY = y;
  out->width = w;
  out->height = h;
  out->parent = parent;
  out->onResize = &resizeFrame;
}

void setBorder(frame_t * out,color_t c){
  out->border.r = c.r;
  out->border.g = c.g;
  out->border.b = c.b;
  out->border.a = c.a;
}
void setBackground(frame_t * out, color_t c){
  out->background.r = c.r;
  out->background.g = c.g;
  out->background.b = c.b;
  out->background.a = c.a;
}

void attachFrame(window_t * window , frame_t * frame){
  if(window->frameCount < window->frameMax){
    memcpy(&window->frames[window->frameCount],frame,sizeof(frame_t));
    window->frameCount++;
    frame->parent = window;
  }else{
    printf("Could Not attach frame to window.\n");
  }
}

void resizeFrame(frame_t * frame, uint16_t width, uint16_t height){
  frame->width = width;
  frame->height = height;
  //renderFrame(frame);
}

void renderFrame(frame_t * frame){
  //Set the background color
  if(SDL_SetRenderDrawColor(frame->parent->renderer,
                        frame->background.r,
                        frame->background.g,
                        frame->background.b,
                        frame->background.a) != 0){
                          printf("There is an error with SDL_SetRenderDrawColor! \n");
                          printf("%s\n",SDL_GetError());
                        }
  SDL_Rect area;
  area.x = frame->posX;
  area.y = frame->posY;
  area.h = frame->height;
  area.w = frame->width;

  SDL_RenderFillRect(frame->parent->renderer, &area);
//set the border
  if(SDL_SetRenderDrawColor(frame->parent->renderer,
                        frame->border.r,
                        frame->border.g,
                        frame->border.b,
                        frame->border.a) != 0){
                          printf("There is an error with SDL_SetRenderDrawColor! \n");
                          printf("%s\n",SDL_GetError());
                        }
  SDL_RenderDrawRect(frame->parent->renderer, &area);
}
