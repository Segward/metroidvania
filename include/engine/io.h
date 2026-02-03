#ifndef IO_H
#define IO_H

typedef struct {
  char *data;
  long size;
  int valid;
} file_t;

file_t io_file_read(const char *path);

#endif
