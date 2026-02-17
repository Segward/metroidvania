#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

typedef struct {
  GLFWwindow *handle;
  unsigned width;
  unsigned height;
} window_t;

int window_init(unsigned width, unsigned height);

#endif
