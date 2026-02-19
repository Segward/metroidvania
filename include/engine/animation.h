#ifndef ANIMATION_H
#define ANIMATION_H

#include <linmath.h>
#include <engine/texture.h>
#include <stdbool.h>

typedef struct animation
{
  texture_t texture;
  int columns;
  int rows;
  int index;
  vec4 uv;
  bool valid;
} animation_t;

animation_t animation_create(const char *path, int columns, int rows);
void animation_next(animation_t *animation);

#endif
