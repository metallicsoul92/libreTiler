#ifndef INPUT_H_
#define INPUT_H_

#ifndef STDINT_DEFINED
#include <stdint.h>
#define STDINT_DEFINED 1
#endif


struct _input{
  uint16_t mouse_x;
  uint16_t mouse_y;
};

typedef struct _input input_t;

void setMouseInfo(input_t * out, int x , int y);

#endif
