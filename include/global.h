#ifndef GLOBAL_H
#define GLOBAL_H

#include <pch.h>
#include <model/object.h>

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
  } texture;

  struct 
  {
    object_t *objects;
  } world;

  mat4x4 view;
  mat4x4 proj;
  vec4 tint;
};

extern struct global global;

#endif
