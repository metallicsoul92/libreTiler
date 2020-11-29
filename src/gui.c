#include "../include/gui.h"
#include "../include/graphics_common.h"


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
