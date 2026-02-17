#ifndef IO_H
#define IO_H

#include <stddef.h>

size_t io_file_read(const char *path, char **out_buffer);

#endif
