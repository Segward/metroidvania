#ifndef IO_H
#define IO_H

#include <pch.h>

typedef struct file
{
  char *data;
  size_t size;
  bool valid;
} file_t;

file_t io_file_read(const char *path);

#endif
