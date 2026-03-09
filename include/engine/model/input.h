#ifndef INPUT_H
#define INPUT_H

#include <pch.h>

typedef struct input
{
  bool left;
  bool right;
  bool up;
  bool down;
} input_t;

void input_update(void);

#endif
