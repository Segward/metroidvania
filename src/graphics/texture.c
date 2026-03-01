#include <pch.h>
#include <graphics/texture.h>
#include <util/global.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb/stb_image.h>

static bool texture_create(GLuint *texture, const char *path)
{
  if (!(texture && path))
    return false;

  glGenTextures(1, texture);
  glBindTexture(GL_TEXTURE_2D, *texture);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  int width, height, channels;
  unsigned char *data = stbi_load(path, &width, &height, &channels, STBI_rgb_alpha);
  if (!data)
    return false;

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);

  stbi_image_free(data);

  return true;
}

bool texture_init(void)
{
  if (!texture_create(&global.texture.sprite, "assets/sprite.png"))
    return false;

  return true;
}

static void texture_delete(GLuint *texture)
{
  if (!texture || !*texture) return;

  glDeleteTextures(1, texture);
  *texture = 0;
}

void texture_cleanup(void)
{
  texture_delete(&global.texture.sprite);
}
