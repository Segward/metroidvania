#include <engine/graphics/texture.h>
#include <engine/util/io.h>
#include <stb/stb_image.h>

static void texture_load_data(texture_data_t *out, const char *path)
{
  assert(out && path);

  out->ptr = NULL;
  out->width = 0;
  out->height = 0;

  size_t size = 0;
  char *file_data = NULL;
  file_read(path, &file_data, &size);
  assert(file_data);

  out->ptr = stbi_load_from_memory((const stbi_uc *)file_data, (int)size, &out->width, &out->height, NULL, 4);
  assert(out->ptr);

  free(file_data);
}

void texture_load_file(texture_t *tex, const char *path)
{
  assert(tex && path);

  texture_data_t data;
  texture_load_data(&data, path);

  tex->width = data.width;
  tex->height = data.height;

  texture_make(tex, &data);
  stbi_image_free(data.ptr);
}

void texture_make(texture_t *tex, texture_data_t *data)
{
  assert(tex && data);
  assert(data->ptr);

  glGenTextures(1, &tex->id);
  glBindTexture(GL_TEXTURE_2D, tex->id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, data->width, data->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data->ptr);
  glBindTexture(GL_TEXTURE_2D, 0);
}
