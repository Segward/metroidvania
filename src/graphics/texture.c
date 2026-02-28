#include <graphics/texture.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

bool texture_create(GLuint *texture, const char *path)
{
  if (!(texture && path)) 
    return false;

  int width, height;
  unsigned char *data = stbi_load(path, &width, &height, NULL, STBI_rgb_alpha);
  if (!data) 
    return false;

  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);
  glBindTexture(GL_TEXTURE_2D, 0);

  return true;
}

void texture_delete(GLuint *texture)
{
  if (!texture || !*texture) return;

  glDeleteTextures(1, texture);
  *texture = 0;
}
