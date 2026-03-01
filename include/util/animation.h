#ifndef ANIMATION_H
#define ANIMATION_H

#include <pch.h>

typedef struct animation
{
  int columns;
  int rows;
  vec4s *uvs;
  size_t index;
} animation_t;

void animation_create(animation_t *animation, int columns, int rows);
void animation_frame(animation_t *animation, int column, int row);
void animation_next(animation_t *animation);
void animation_delete(animation_t *animation);

#endif
