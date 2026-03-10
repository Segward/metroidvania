#ifndef TEXTURE_H
#define TEXTURE_H

#include <pch.h>

typedef struct texture_data
{
  unsigned char *ptr;
  int width;
  int height;
} texture_data_t;

typedef struct texture
{
  GLuint id;
  int width;
  int height;
} texture_t;

void texture_load_file(texture_t *tex, const char *path);
void texture_make(texture_t *tex, texture_data_t *data);

#endif
