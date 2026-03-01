#ifndef GLOBAL_H
#define GLOBAL_H

#include <graphics/window.h>

typedef struct {
  window_t window;
  mat4x4 projection;
} global_t;

extern global_t global;

#endif
