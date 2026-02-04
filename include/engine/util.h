#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>

#define ERROR_LOG(fmt, ...) \
  do { \
    fprintf(stderr, "%s:%d:%s: " fmt "\n", __FILE__, __LINE__, __func__ __VA_OPT__(,) __VA_ARGS__); \
    fflush(stderr); \
  } while (0)

#define ERROR_RETURN(retval, fmt, ...) \
  do { \
    ERROR_LOG(fmt __VA_OPT__(,) __VA_ARGS__); \
    return (retval); \
  } while (0)

#define ERROR_EXIT(fmt, ...) \
  do { \
    ERROR_LOG(fmt __VA_OPT__(,) __VA_ARGS__); \
    exit(EXIT_FAILURE); \
  } while (0)

#endif
