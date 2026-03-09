#ifndef GLOBAL_H
#define GLOBAL_H

#include <pch.h>

struct global 
{
  struct 
  {
    GLFWwindow *handle;
    int width;
    int height;
  } window;

  struct 
  {
    double last_time;
    double delta_time;
  } time;

  struct 
  {
    GLuint player;
    GLuint grass;
    GLuint white;
  } tex;

  mat4x4 view;
  mat4x4 proj;
};

extern struct global global;

#endif
