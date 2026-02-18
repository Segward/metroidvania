#include <engine/io.h>
#include <stdio.h>
#include <stdlib.h>

file_t io_file_read(const char *path)
{
  file_t retval = {
    .valid = false
  };

  FILE *file = fopen(path, "rb");
  if (file == NULL)
    return retval;

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);

  char *buffer = malloc((size_t)size);
  if (buffer == NULL)
  {
    fclose(file);
    return retval;
  }

  size_t read = fread(buffer, 1, (size_t)size, file);
  fclose(file);

  retval.size = read;
  retval.data = buffer;
  retval.valid = true;

  return retval;
}
