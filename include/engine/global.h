#ifndef GLOBAL_H
#define GLOBAL_H

#include <engine/window.h>
#include <engine/render.h>

typedef struct {
  window_t window;
  render_t render;
} global_t;

extern global_t global;

#endif
