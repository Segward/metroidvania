#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_RETURN(retval, fmt, ...) \
  do { \
    fprintf(stderr, fmt __VA_OPT__(,) __VA_ARGS__); \
    return retval; \
  } while (0)

#define ERROR_EXIT(exit_code, fmt, ...) \
  do { \
    fprintf(stderr, fmt __VA_OPT__(,) __VA_ARGS__); \
    exit(exit_code); \
  } while (0)

#endif
