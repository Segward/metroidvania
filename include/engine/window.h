#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>
#include <engine/types.h>

typedef struct {
  GLFWwindow *handle;
  u32 width;
  u32 height;
} window_t;

void window_init(u32 width, u32 height);

#endif
