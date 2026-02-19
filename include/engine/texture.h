#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include <stdbool.h>

typedef struct texture
{
  GLuint id;
  int width;
  int height;
  bool valid;
} texture_t;

texture_t texture_create(const char *path);

#endif
