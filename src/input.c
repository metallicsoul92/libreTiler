#include "../include/graphics_common.h"
#include "../include/input.h"
#include "../include/window.h"
#include "../include/gui.h"


bool mousePressedRec(SDL_Rect * rect , int x , int y){
    if( (x > rect->x && x < rect->x + rect->w) &&
        (y > rect->y && y < rect->y + rect->h) ){
          return true;
        }
        return false;
}


void setMouseInfo(input_t * out, int x , int y){
    out->mouse_x = x;
    out->mouse_y = y;
}

void determineClick(input_t * out){
  uint8_t tbcount = out->parent->gui->count;
  SDL_Rect toolbarItems[tbcount];
  uint8_t offset = 4;
  for(int i = 0; i < tbcount ; i++){
    toolbarItems[i].x = (65 * i)+ offset;
    toolbarItems[i].y = 0;
    toolbarItems[i].w = 50;
    toolbarItems[i].h = 20;
    if(mousePressedRec(&toolbarItems[i] , out->mouse_x, out->mouse_y)){
      out->parent->gui->toolbarItemList[i].onClick(&out->parent->gui->toolbarItemList[i]);
      printf("Mouse Pressed on %s\n",
      out->parent->gui->toolbarItemList[i].name);
      renderBackground(out->parent);
      renderToolbar(out->parent->gui);
    }
  }
  for(int i = 0; i <tbcount; i++){
    if(out->parent->gui->toolbarItemList[i].isHighlighted){
    int size = out->parent->gui->toolbarItemList[i].count;
    SDL_Rect menuItems[size];
    for(int j = 0; j < size; j++){
      menuItems[j].x =  (65 * i)+ offset;
      menuItems[j].y = 20 + (20 * j);
      menuItems[j].w = 150;
      menuItems[j].h = 20;
      if(mousePressedRec(&menuItems[j] , out->mouse_x, out->mouse_y)){

        switch(out->parent->gui->toolbarItemList[i].menuVariantList[j].type){
          case TYPE_MENU_MENUITEM:
          printf("%s was clicked\n",out->parent->gui->toolbarItemList[i].menuVariantList[j].data.asItem->title);
          out->parent->gui->toolbarItemList[i].menuVariantList[j].data.asItem->onClick(&out->parent->gui->toolbarItemList[i].menuVariantList[j]);
          break;
          case TYPE_MENU_MENUGROUP:
          printf("%s was clicked\n",out->parent->gui->toolbarItemList[i].menuVariantList[j].data.asGroup->title);
          out->parent->gui->toolbarItemList[i].menuVariantList[j].data.asItem->onClick(&out->parent->gui->toolbarItemList[i].menuVariantList[j]);
          break;
          default:
          break;
          }
        }
      }
    }
  }
}
