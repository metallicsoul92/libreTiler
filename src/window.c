#include "../include/graphics_common.h"
#include "../include/window.h"
#include "../include/gui.h"

#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480

//Foward Declarations
void InitializeToolbar(toolbar_t * toolbar);
void InitializeFrames(window_t * out);


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

//create GUI??
out->gui = malloc(sizeof(toolbar_t));

allocateToolbar(out->gui , out , 3);
InitializeToolbar(out->gui);
out->isRunning = true;
out->frameMax = 8;
out->frameCount = 0;
out->frames = malloc(sizeof(frame_t) * out->frameMax);
InitializeFrames(out);
}


void resizeWindow(window_t * out, int ox, int oy, int x, int y){
  out->width = x;
  out->height = y;
  int dx = x - ox;
  int dy = y - oy;

  SDL_SetWindowSize(out->window,out->width, out->height);
  SDL_RenderClear(out->renderer);
  for(uint8_t i = 0; i < out->frameCount;i++){
    out->frames[i].onResize(&out->frames[i],out->frames[i].width+dx,
                            out->frames[i].height+dy);
  }
  renderWindow(out);
}


void deleteWindow(window_t * out){
  free(out->title);
  SDL_DestroyRenderer(out->renderer);
  SDL_DestroyWindow(out->window);
  free(out);
}

void renderWindow(window_t * out){
  renderBackground(out);
  renderFrame(&out->frames[0]);
  renderToolbar(out->gui);

}
//Callbacks
int toolbar_onclick_callback(toolbarItem_t * data){
  for(int i = 0; i < data->parent->count; i++){
    if(data->parent->toolbarItemList[i].isHighlighted){
      data->parent->toolbarItemList[i].isHighlighted = !data->parent->toolbarItemList[i].isHighlighted;
    }
  }
  data->isHighlighted = !data->isHighlighted;
}

int new_callback(void * data){
  (void)data;
  //implement this
  return -1;
}


int quit_callback(void * data){
  menuItemVariant_t * list = data;
  list->parent->data.asToolbarItem->parent->parent->isRunning = false;
  return 0;
}


// TOOLBAR ITEMS
toolbarItem_t File;
toolbarItem_t Edit;
toolbarItem_t Settings;

menuItemVariant_t New;
menuItemVariant_t Quit;

menuParentVariant_t FileVar;
menuParentVariant_t EditVar;
menuParentVariant_t SettingsVar;

//frames
frame_t MapView;
frame_t ToolView;


void InitializeToolbar(toolbar_t * toolbar){


  allocateToolbarItem(&File,"File",&toolbar_onclick_callback,5,toolbar);
  allocateParentVariant(&FileVar,TYPE_PARENT_TOOLBARITEM, &File);
  allocateMenuVariant(&New,TYPE_MENU_MENUITEM,"New Project",&new_callback,NULL, &FileVar);
  addVariantToToolbarItem(&File,&New);
  allocateMenuVariant(&Quit,TYPE_MENU_MENUITEM,"Quit",&quit_callback,NULL, &FileVar);
  addVariantToToolbarItem(&File,&Quit);
  attachToolbarItem(toolbar, &File);

  allocateToolbarItem(&Edit,"Edit",&toolbar_onclick_callback,5,toolbar);
  allocateParentVariant(&EditVar,TYPE_PARENT_TOOLBARITEM, &Edit);
  attachToolbarItem(toolbar, &Edit);

  allocateToolbarItem(&Settings,"Settings",&toolbar_onclick_callback,5,toolbar);
  allocateParentVariant(&SettingsVar,TYPE_PARENT_TOOLBARITEM, &Settings);
  attachToolbarItem(toolbar, &Settings);
}

void InitializeFrames(window_t * out){
  int mapFrameWidth = (out->width/2) + 100;
  int mapFrameHeight = out->height - 20;
  color_t black;
  black.r = 0; black.g = 0 ; black.b = 0 ; black.a  = 0;
  color_t lightBlue;
  lightBlue.r = 50; lightBlue.g = 50; lightBlue.b = 255; lightBlue.a = 50;

  allocateFrame(&MapView, out, 0, 20, mapFrameWidth,mapFrameHeight);
  setBorder(&MapView,black);
  setBackground(&MapView,lightBlue);
  attachFrame(out,&MapView);
}
