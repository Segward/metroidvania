#ifndef GLOBAL_H
#define GLOBAL_H

#include <engine/graphics/window.h>
#include <engine/graphics/texture.h>
#include <engine/model/time.h>
#include <engine/model/input.h>

typedef struct global 
{
  window_t window;
  time_t time;
  input_t input;
  texture_t texture;
  mat4x4 view;
  mat4x4 proj;
} global_t;

extern global_t global;

#endif
