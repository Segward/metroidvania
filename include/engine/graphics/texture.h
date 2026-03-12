#ifndef TEXTURE_H
#define TEXTURE_H

#include <pch.h>

typedef struct texture
{
  GLuint id;
  int width;
  int height;
} texture_t;

void texture_load_file(texture_t *tex, const char *path);

#endif
