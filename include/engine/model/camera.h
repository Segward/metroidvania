#ifndef CAMERA_H
#define CAMERA_H

#include <pch.h>

typedef struct camera
{
  vec2 pos;
} camera_t;

void camera_update(vec2 pos);

#endif
