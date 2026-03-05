#include <util/io.h>

file_t io_file_read(const char *path)
{
  file_t retval = { .valid = false };

  FILE *file = fopen(path, "rb");
  if (!file) return retval;

  fseek(file, 0, SEEK_END);
  long size = ftell(file);
  fseek(file, 0, SEEK_SET);

  if (size < 0) 
  { 
    fclose(file); 
    return retval; 
  }

  char *buffer = (char*)malloc((size_t)size + 1);
  if (!buffer) 
  { 
    fclose(file); 
    return retval; 
  }

  size_t read = fread(buffer, 1, (size_t)size, file);
  fclose(file);

  buffer[read] = '\0';

  retval.size  = read;
  retval.data  = buffer;
  retval.valid = true;

  return retval;
}
