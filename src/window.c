#include "../include/graphics_common.h"
#include "../include/window.h"
#include "../include/gui.h"

#define DEFAULT_SCREEN_WIDTH 640
#define DEFAULT_SCREEN_HEIGHT 480

//Foward Declarations 
void InitializeToolbar(toolbar_t * toolbar);



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
}


void resizeWindow(window_t * out, int x, int y){
  out->width = x;
  out->height = y;
  SDL_SetWindowSize(out->window,out->width, out->height);
  SDL_RenderClear(out->renderer);
  renderBackground(out);
  renderToolbar(out->gui);
}


void deleteWindow(window_t * out){
  free(out->title);
  SDL_DestroyRenderer(out->renderer);
  SDL_DestroyWindow(out->window);
  free(out);
}

void renderWindow(window_t * out){
  renderBackground(out);
  renderToolbar(out->gui);
}
//Callbacks

int new_callback(void * data){
  (void)data;
  //implement this
  return -1;
}

//I wonder if this will work. We will pass in the boolean isRunning and set it
//to false.
int quit_callback(void * data){
  bool * running = data;
  running = false;
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

void InitializeToolbar(toolbar_t * toolbar){


  allocateToolbarItem(&File,"File",5,toolbar);
  allocateParentVariant(&FileVar,TYPE_PARENT_TOOLBARITEM, &File);
  attachToolbarItem(toolbar, &File);

  allocateMenuVariant(&New,TYPE_MENU_MENUITEM,"New Project",&new_callback,NULL, &FileVar);
  addVariantToToolbarItem(&File,&New);

  allocateMenuVariant(&Quit,TYPE_MENU_MENUITEM,"New Project",&quit_callback,NULL, &FileVar);
  addVariantToToolbarItem(&File,&Quit);

  allocateToolbarItem(&Edit,"Edit",5,toolbar);
  allocateParentVariant(&EditVar,TYPE_PARENT_TOOLBARITEM, &Edit);
  attachToolbarItem(toolbar, &Edit);

  allocateToolbarItem(&Settings,"Settings",5,toolbar);
  allocateParentVariant(&SettingsVar,TYPE_PARENT_TOOLBARITEM, &Settings);
  attachToolbarItem(toolbar, &Settings);
}
