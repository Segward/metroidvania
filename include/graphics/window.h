#ifndef WINDOW_H
#define WINDOW_H

#include <pch.h>

typedef struct window
{
  GLFWwindow *handle;
  int width;
  int height;
} window_t;

bool window_init(int width, int height, const char *title);
void window_close(void);

#endif
