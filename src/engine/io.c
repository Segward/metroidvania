#include <engine/io.h>
#include <engine/util.h>
#include <stdio.h>
#include <stdlib.h>

file_t io_file_read(const char *path) {
  file_t file = { .valid = 0 };

  FILE *fp = fopen(path, "rb");
  if (!fp) {
    ERROR_RETURN(file, "fopen failed for %s\n", path);
  }

  fseek(fp, 0, SEEK_END);
  long size = ftell(fp);
  if (size < 0) {
    fclose(fp);
    ERROR_RETURN(file, "ftell failed for %s\n", path);
  }

  rewind(fp);

  char *data = malloc((size_t)size);
  if (!data && size > 0) {
    fclose(fp);
    ERROR_RETURN(file, "malloc failed for %s\n", path);
  }

  size_t read = fread(data, 1, (size_t)size, fp);
  if (read < (size_t)size && ferror(fp)) {
    free(data);
    fclose(fp);
    ERROR_RETURN(file, "fread failed for %s\n", path);
  }

  fclose(fp);

  file.data = data;
  file.size = (long)read;
  file.valid = 1;

  return file;
}
