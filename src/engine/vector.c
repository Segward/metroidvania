#include <engine/vector.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

vector_t *vector_create(size_t item_size, size_t capacity) {
  vector_t *vector = malloc(sizeof(vector_t));
  if (vector == NULL) {
    fprintf(stderr, "failed to malloc\n");
    return NULL;
  }

  vector->item_size = item_size;
  vector->capacity = capacity;
  vector->len = 0;

  if (capacity == 0) {
    vector->items = NULL;
    return vector;
  }

  vector->items = malloc(item_size * capacity);
  if (vector->items == NULL) {
    fprintf(stderr, "failed to malloc\n");
    free(vector);
    return NULL;
  }

  return vector;
}

int vector_append(vector_t *vector, void *item, size_t *out_index) { 
  if (vector->len == vector->capacity) {
    vector->capacity = vector->capacity > 0 ? vector->capacity * 2 : 1;
    void *items = realloc(vector->items, vector->item_size * vector->capacity);
    if (items == NULL) {
      fprintf(stderr, "failed to realloc\n");
      return 0;
    }

    vector->items = items;
  }

  size_t index = vector->len++;
  memcpy((char *)vector->items + index * vector->item_size, item, vector->item_size);

  *out_index = index;
  return 1;
}

void *vector_get(vector_t *vector, size_t index) {
  if (index >= vector->len) {
    fprintf(stderr, "index out of bounds\n");
    return NULL;
  }

  return (char *)vector->items + index * vector->item_size;
}

int vector_remove(vector_t *vector, size_t index) {
  if (vector->len == 0) {
    fprintf(stderr, "vector is empty\n");
    return 0;
  }
  
  if (index >= vector->len) {
    fprintf(stderr, "index out of bounds\n");
    return 0;
  }

  if (vector->len == 1) {
    vector->len = 0;
    return 1;
  }

  vector->len--;

  char *item_ptr = (char *)vector->items + index * vector->item_size;
  char *end_ptr = (char *)vector->items + vector->len * vector->item_size;
  memcpy(item_ptr, end_ptr, vector->item_size);

  return 1;
}
