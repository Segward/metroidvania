#include <pch.h>
#include <util/io.h>

char *io_file_read(const char *path)
{
  FILE *file = fopen(path, "rb");
  assert(file);

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = (char*)malloc((size_t)size + 1);
  assert(buffer);

  size_t read = fread(buffer, 1, (size_t)size, file);
  fclose(file);

  buffer[read] = '\0';
  return buffer;
}
