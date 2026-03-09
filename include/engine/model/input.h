#ifndef INPUT_H
#define INPUT_H

#include <pch.h>

typedef struct input
{
  bool left;
  bool right;
  bool up;
  bool down;

  bool mouse_left;
  bool mouse_right;

  vec2 mouse_pos;
  vec2 mouse_world;
} input_t;

void input_update(void);

#endif
