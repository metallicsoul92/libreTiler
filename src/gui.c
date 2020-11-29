#include "../include/gui.h"
#include "../include/graphics_common.h"
#include "../include/window.h"

void allocateMenuItem(menuItem_t * out, const char * title,int (*func)(void * data)){
      out->title = malloc(sizeof(char) * strlen(title));
      strcpy(out->title, title);
      out->onClick = func;
}

void allocateMenuGroup(menuItemGroup_t * out , const char * title,
                       uint8_t initialsize){
      out->title = malloc(sizeof(char) * strlen(title));
      strcpy(out->title, title);
      out->max = initialsize;
      out->count = 0;
      out->items = malloc(sizeof(menuItem_t) * initialsize);
      out->isHighlighted = false;
}

void addMenuItemToGroup(menuItemGroup_t * out, menuItem_t * item){
  if(out->count < out->max){
    memcpy(&out->items[out->count],item,sizeof(menuItem_t));
    out->count++;
  }else{
    printf("Error. Cannot Attach %s to %s",item->title, out->title);
  }
}

void allocateMenuVariant(menuItemVariant_t * out, enum MenuItemType t, const char * title,
                          int (*func)(void * data) ,uint8_t initialsize, menuParentVariant_t * parent){
  out->type = t;
  out->parent = parent;
  switch(t){
    case TYPE_MENU_MENUITEM:
    //unused variable
    (void)initialsize;
    out->data.asItem = malloc(sizeof(menuItem_t));
    allocateMenuItem(out->data.asItem,title, func);
    break;
    case TYPE_MENU_MENUGROUP:
    //unused variable
    (void)func;
    out->data.asGroup = malloc(sizeof(menuItemGroup_t));
    allocateMenuGroup(out->data.asGroup,title,initialsize);
    break;
    default:
    break;
  }
}

void allocateToolbarItem(toolbarItem_t * out, const char * title,
                         uint8_t max, toolbar_t * parent){

  out->name = malloc(sizeof(char) * strlen(title));
  strcpy(out->name, title);
  out->count = 0;
  out->max = max;
  out->menuVariantList = malloc(sizeof(menuItemVariant_t) * max);
  out->isHighlighted = false;
  out->parent = parent;
}

void addVariantToToolbarItem(toolbarItem_t * out , menuItemVariant_t * data){

  char * name;
  switch(data->type){
    case TYPE_MENU_MENUITEM:
    name = data->data.asItem->title;
    break;
    case TYPE_MENU_MENUGROUP:
    name = data->data.asGroup->title;
    break;
    default:
    break;
  }

  if(out->count < out->max){
  memcpy(&out->menuVariantList[out->count],data,sizeof(menuItemVariant_t));
  out->count++;
  }else{
  printf("Error. Cannot Attach %s to %s",name, out->name);
  }
}

void allocateParentVariant(menuParentVariant_t * out, enum MenuParentType t, void *data){
  out->type = t;
  switch(t){
    case TYPE_PARENT_MENUITEM:
    out->data.asMenuItem = data;
    break;
    case TYPE_PARENT_TOOLBARITEM:
    out->data.asToolbarItem = data;
    break;
    default:
    break;
  }
}


void allocateToolbar(toolbar_t * out, window_t * parent, uint8_t maxSize){
  out->parent = parent;
  out->count = 0;
  out->max = maxSize;
  out->toolbarItemList = malloc(sizeof(toolbarItem_t) * maxSize);
  out->onClick = NULL;
}

void attachToolbarItem(toolbar_t * out, toolbarItem_t * item){
  if(out->count <= out->max){
    memcpy(&out->toolbarItemList[out->count],item,sizeof(toolbarItem_t));
    out->count++;
  }else
    printf("Cannot attach %s to toolbar", item->name);
}

/**
    GUI SECTION
**/

TTF_Font * font;
void font_Load(){
    font=TTF_OpenFont("OpenSans-Regular.ttf", 32);
    if(!font) {
    printf("TTF_OpenFont: %s\n", TTF_GetError());
    // handle error
    exit(-2);
}
}

void closeFont(){
  TTF_CloseFont(font);
}

void renderBackground(window_t * window){
  //Sets the color of the renderer
  if(SDL_SetRenderDrawColor(window->renderer,0,0,255,255) != 0){
    printf("There is an error with SDL_SetRenderDrawColor! \n");
    printf("%s\n",SDL_GetError());
  }

  //Draws the background to the renderer
  if(SDL_RenderClear(window->renderer) !=0){
    printf("There is an error with SDL_RenderClear \n");
    printf("%s\n",SDL_GetError());
  }
}


void renderToolbar(toolbar_t * bar){
  uint8_t offset = 4;
  SDL_Rect area;
  area.x = 0;
  area.y = 0;
  area.w = bar->parent->width;
  area.h = 20;
  SDL_SetRenderDrawColor(bar->parent->renderer,55,55,55,255);
  SDL_RenderFillRect(bar->parent->renderer, &area);
  SDL_Rect toolbarItems[bar->count];
  SDL_Surface ** fontSurface = malloc(sizeof(SDL_Surface*) * bar->count);
  SDL_Texture ** fontTexture = malloc(sizeof(SDL_Texture*) * bar->count);
  SDL_Color fontColor = {255,255,255,255};
  char fontText[8];
  for(int i = 0; i < bar->count; i++){
    toolbarItems[i].x = (65 * i)+ offset;
    toolbarItems[i].y = 0;
    toolbarItems[i].w = 50;
    toolbarItems[i].h = 20;
    memset(&fontText,' ',8);
    memcpy(&fontText ,bar->toolbarItemList[i].name,strlen(bar->toolbarItemList[i].name));
    fontSurface[i] = TTF_RenderText_Blended(font,fontText, fontColor);
    fontTexture[i] = SDL_CreateTextureFromSurface(bar->parent->renderer, fontSurface[i]);
    SDL_RenderCopy(bar->parent->renderer, fontTexture[i], NULL, &toolbarItems[i]);
    free(fontSurface[i]);
  }

    free(fontSurface);

}
