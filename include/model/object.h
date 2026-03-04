#ifndef OBJECT_H
#define OBJECT_H

#include <pch.h>

typedef struct object
{
  vec2 position;
  vec2 size;
  GLuint texture;
} object_t;

void object_create(object_t *object, GLuint texture);
void object_draw(object_t *object);

#endif
