#include <engine/io.h>

#include <stdio.h>
#include <stdlib.h>

size_t io_file_read(const char *path, char **out_buffer) {
  *out_buffer = NULL;

  FILE *file = fopen(path, "rb");
  if (file == NULL) {
    fprintf(stderr, "failed to open file: %s\n", path);
    return 0;
  }

  if (fseek(file, 0, SEEK_END) != 0) {
    fprintf(stderr, "failed to seek end of file: %s\n", path);
    fclose(file);
    return 0;
  }

  long size = ftell(file);
  if (size < 0) {
    fprintf(stderr, "failed to tell size of file %s\n", path);
    fclose(file);
    return 0;
  }

  if (fseek(file, 0, SEEK_SET) != 0) {
    fprintf(stderr, "failed to seek start of file: %s\n", path);
    fclose(file);
    return 0;
  }

  char *buffer = malloc((size_t)size + 1);
  if (buffer == NULL) {
    fprintf(stderr, "failed to malloc\n");
    fclose(file);
    return 0;
  }

  size_t read = fread(buffer, 1, (size_t)size, file);
  if (read < (size_t)size && ferror(file)) {
    fprintf(stderr, "failed to read file %s\n", path);
    free(buffer);
    fclose(file);
    return 0;
  }

  fclose(file);
  buffer[read] = '\0';

  *out_buffer = buffer;
  return read;
}
