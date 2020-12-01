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

#include "graphics_common.h"
#include "gui/toolbar.h"
#include "gui/frame.h"

/**
    Graphical functions of the GUI
**/
void font_Load();
void closeFont();


#endif
