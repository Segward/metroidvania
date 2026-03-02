#include <graphics/texture.h>
#include <util/global.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

void texture_create(GLuint *texture, const char *path)
{
  assert(texture && path);

  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int width, height, channels;
  unsigned char *data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
  assert(data);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);
}

void texture_white(GLuint *texture)
{
  assert(texture);

  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  unsigned char white_pixel[] = {255, 255, 255, 255};

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_RGBA, GL_UNSIGNED_BYTE, white_pixel);
  glGenerateMipmap(GL_TEXTURE_2D);
}

void texture_delete(GLuint *texture)
{
  assert(texture);
  glDeleteTextures(1, texture);
  *texture = 0;
}
