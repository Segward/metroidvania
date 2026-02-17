#ifndef VECTOR_H
#define VECTOR_H

#include <stddef.h>

typedef struct {
  void *items;
  size_t item_size;
  size_t len;
  size_t capacity;
} vector_t;

vector_t *vector_create(size_t item_size, size_t capacity);
int vector_append(vector_t *vector, void *item, size_t *out_index);
void *vector_get(vector_t *vector, size_t index);
int vector_remove(vector_t *vector, size_t index);

#endif
