#ifndef GLOBAL_H
#define GLOBAL_H

#include <engine/graphics/window.h>
#include <engine/model/time.h>
#include <engine/model/camera.h>
#include <engine/model/input.h>

typedef struct global 
{
  window_t window;
  time_t time;
  input_t input;
  camera_t camera;

  mat4x4 view;
  mat4x4 proj;
} global_t;

extern global_t global;

#endif
