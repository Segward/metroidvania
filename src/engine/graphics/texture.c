#include <engine/graphics/texture.h>
#include <engine/util/io.h>
#include <stb/stb_image.h>

void texture_load_file(texture_t *tex, const char *path)
{
  size_t file_size = 0;
  char *file_data = NULL;

  file_read(path, &file_data, &file_size);
  if (file_data == NULL) {
    fprintf(stderr, "Failed to read texture file: %s\n", path);
    exit(EXIT_FAILURE);
  }

  int width = 0;
  int height = 0;
  int channels = 0;

  unsigned char *pixels = stbi_load_from_memory((const stbi_uc *)file_data, (int)file_size, &width, &height, &channels, 4);

  free(file_data);

  if (pixels == NULL) {
    fprintf(stderr, "Failed to load image: %s\n", path);
    exit(EXIT_FAILURE);
  }

  tex->width = width;
  tex->height = height;

  glGenTextures(1, &tex->id);
  glBindTexture(GL_TEXTURE_2D, tex->id);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

  glBindTexture(GL_TEXTURE_2D, 0);
  stbi_image_free(pixels);
}
