#ifndef VECTOR_H
#define VECTOR_H

#include <engine/types.h>

typedef struct {
  void *items;
  usize item_size;
  usize len;
  usize capacity;
} vector_t;

vector_t *vector_create(usize item_size, usize capacity);
u8 vector_append(vector_t *vector, void *item, usize *out_index);
void *vector_get(vector_t *vector, usize index);
u8 vector_remove(vector_t *vector, usize index);

#endif
