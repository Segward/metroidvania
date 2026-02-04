#include <engine/io.h>
#include <engine/util.h>
#include <stdio.h>
#include <stdlib.h>

u32 io_file_read(const char *path, char **out_buffer) {
  *out_buffer = NULL;

  FILE *file = fopen(path, "rb");
  if (file == NULL)
    ERROR_EXIT("failed to open %s", path);

  if (fseek(file, 0, SEEK_END) != 0) {
    fclose(file);
    ERROR_EXIT("failed to seek end %s", path);
  }

  long size = ftell(file);
  if (size < 0) {
    fclose(file);
    ERROR_EXIT("failed to tell size of %s", path);
  }

  if (fseek(file, 0, SEEK_SET) != 0) {
    fclose(file);
    ERROR_EXIT("failed to seek set %s", path);
  }

  char *buffer = malloc((size_t)size + 1);
  if (buffer == NULL) {
    fclose(file);
    ERROR_EXIT("malloc failed for %s", path);
  }

  size_t read = fread(buffer, 1, (size_t)size, file);
  if (read < (size_t)size && ferror(file)) {
    free(buffer);
    fclose(file);
    ERROR_EXIT("failed to read %s", path);
  }

  fclose(file);
  buffer[read] = '\0';

  *out_buffer = buffer;
  return (u32)read;
}
