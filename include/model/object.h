#ifndef OBJECT_H
#define OBJECT_H

#include <pch.h>

typedef struct object
{
  vec2 pos;
  vec2 size;
  GLuint tex;
} object_t;

void object_create(object_t *object, GLuint tex);
void object_draw(object_t *object);

#endif
