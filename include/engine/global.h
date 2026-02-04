#ifndef GLOBAL_H
#define GLOBAL_H

#include <engine/window.h>
#include <engine/time.h>

typedef struct {
  window_t window;
  time_t time;
} global_t;

extern global_t global;

#endif
