#ifndef GUI_H_
#define GUI_H_

#ifndef STDBOOL_DEFINED
#include <stdbool.h>
#define STDBOOL_DEFINED 1
#endif

#ifndef STDINT_DEFINED
#include <stdint.h>
#define STDINT_DEFINED 1
#endif


//menuItem represents a basic toolbar action
struct _menuItem{
  char * title;
  int (*onClick)(void * data);
};

typedef struct _menuItem menuItem_t;

void allocateMenuItem(menuItem_t * out, const char * title,int (*func)(void * data));

//menuItemGroup represents a button that spawns multiple menuItems to
//represent
struct _menuItemGroup{
  char * title;
  int (*onClick)(void * data);
  uint8_t count;
  uint8_t max;
  menuItem_t * items;
  bool isHighlighted;
};

typedef struct _menuItemGroup menuItemGroup_t;

void allocateMenuGroup(menuItemGroup_t * out , const char * title, uint8_t initialsize);
void addMenuItemToGroup(menuItemGroup_t * out, menuItem_t * item);

enum MenuItemType {
  TYPE_MENU_MENUITEM = 0,
  TYPE_MENU_MENUGROUP = 1
};

//foward declare
struct _menuParentVariant;
typedef struct _menuParentVariant menuParentVariant_t;

union internalVariant{
  menuItem_t *asItem;
  menuItemGroup_t *asGroup;
};

typedef union internalVariant mivariant_t;

//Variant used within the toolitem structure to represent either a
//single menu item or an item group
struct _menuitemVariant{
    enum MenuItemType type;
    mivariant_t data;
    menuParentVariant_t * parent;
};
typedef struct _menuitemVariant menuItemVariant_t;

void allocateMenuVariant(menuItemVariant_t * out, enum MenuItemType t, const char * title,
                          int (*func)(void * data) ,uint8_t initialsize, menuParentVariant_t * parent);

//foward declare
struct _toolbar;
typedef struct _toolbar toolbar_t;
//Toolbar item represents the top level buttons used to navigate the gui
//for example, the "File" button would be considered a toolbarItem_t
struct _toolbarItem{
    char * name;
    uint8_t count;
    uint8_t max;
    menuItemVariant_t * menuVariantList;
    int (*onClick)(void * data);
    bool isHighlighted;
    toolbar_t * parent;
};

typedef struct _toolbarItem toolbarItem_t;

void allocateToolbarItem(toolbarItem_t * out, const char * title,
                         uint8_t max, toolbar_t * parent);

void addVariantToToolbarItem(toolbarItem_t * out , menuItemVariant_t * data);


struct _toolbar{
  uint8_t count;
  uint8_t max;
  toolbarItem_t * toolbarItemList;
  int (*onClick)(void * data);
};

enum MenuParentType {
  TYPE_PARENT_MENUITEM = 0,
  TYPE_PARENT_TOOLBARITEM = 1
};


union mpvariant{
  toolbarItem_t *asToolbarItem;
  menuItem_t *asMenuItem;
};

typedef union mpvariant mpvariant_t;

struct _menuParentVariant{
  enum MenuParentType type;
  mpvariant_t data;
};
typedef struct _menuParentVariant menuParentVariant_t;

void allocateParentVariant(menuParentVariant_t * out, enum MenuParentType t, void *data);


#endif
