#include <engine/util/io.h>

void file_read(const char *path, char **out, size_t *read)
{
  FILE *file = fopen(path, "rb");
  if (!file) {
    fprintf(stderr, "Failed to open file %s\n", path);
    exit(EXIT_FAILURE);
  }

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  rewind(file);

  char *buffer = malloc((size_t)size);
  if (!buffer) {
    fprintf(stderr, "Failed to malloc\n");
    fclose(file);
    exit(EXIT_FAILURE);
  }

  size_t bytes = fread(buffer, 1, (size_t)size, file);
  fclose(file);

  *out = buffer;
  if (read)
    *read = bytes;
}
