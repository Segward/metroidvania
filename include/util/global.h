#ifndef GLOBAL_H
#define GLOBAL_H

#include <pch.h>

struct global {
  struct {
    GLFWwindow *handle;
    int width;
    int height;
    mat4x4 projection;
  } window;

  struct {
    double last_time;
    double delta_time;
  } time;

  struct {
    GLuint sprite;
  } texture;
};

extern struct global global;

#endif
