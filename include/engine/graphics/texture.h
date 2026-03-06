#ifndef TEXTURE_H
#define TEXTURE_H

#include <pch.h>

typedef struct texture_data
{
  unsigned char *ptr;
  int width;
  int height;
} texture_data_t;

void texture_load_file(GLuint *tex, const char *path);
void texture_make(GLuint *tex, texture_data_t *data);

#endif
