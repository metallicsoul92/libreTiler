#ifndef GUI_FRAME_H_
#define GUI_FRAME_H_



typedef struct _window window_t;
typedef struct _color color_t;

/**
  Frame Structure
**/
struct _frame {
  uint16_t posX;
  uint16_t posY;
  uint16_t width;
  uint16_t height;

  color_t border;
  color_t background;
  window_t * parent;
  void (*onResize)(struct _frame * frame, uint16_t w, uint16_t h);
};

typedef struct _frame frame_t;

//assumes the frame is already malloc'd
void allocateFrame(frame_t * out, window_t * parent, uint16_t x,
                    uint16_t y, uint16_t w, uint16_t h);
void setBorder(frame_t * out,color_t c);
void setBackground(frame_t * out, color_t c);
void attachFrame(window_t * window, frame_t * frame);
void resizeFrame(frame_t * frame, uint16_t width, uint16_t height);
void renderFrame(frame_t * frame);

#endif
