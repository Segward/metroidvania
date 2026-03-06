#include <engine/util/io.h>

void file_read(const char *path, char **out, size_t *read)
{
  assert(path && out);

  FILE *file = fopen(path, "rb");
  assert(file);

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char *buffer = malloc((size_t)size);
  assert(buffer);

  size_t bytes = fread(buffer, 1, (size_t)size, file);
  fclose(file);

  *out = buffer;
  if (read)
    *read = bytes;
}
