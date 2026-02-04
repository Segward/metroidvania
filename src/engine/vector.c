#include <engine/vector.h>
#include <engine/util.h>
#include <stdlib.h>
#include <string.h>

vector_t *vector_create(usize item_size, usize capacity) {
  vector_t *vector = malloc(sizeof(vector_t));
  if (vector == NULL)
    ERROR_RETURN(NULL, "malloc failed");

  vector->item_size = item_size;
  vector->capacity = capacity;
  vector->len = 0;

  if (capacity == 0) {
    vector->items = NULL;
    return vector;
  }

  vector->items = malloc(item_size * capacity);
  if (vector->items == NULL) {
    free(vector);
    ERROR_RETURN(NULL, "malloc failed");
  }

  return vector;
}

u8 vector_append(vector_t *vector, void *item, usize *out_index) { 
  if (vector->len == vector->capacity) {
    vector->capacity = vector->capacity > 0 ? vector->capacity * 2 : 1;
    void *items = realloc(vector->items, vector->item_size * vector->capacity);
    if (items == NULL)
      ERROR_RETURN(1, "malloc failed");

    vector->items = items;
  }

  usize index = vector->len++;
  memcpy((u8 *)vector->items + index * vector->item_size, item, vector->item_size);

  *out_index = index;
  return 0;
}

void *vector_get(vector_t *vector, usize index) {
  if (index >= vector->len)
    ERROR_RETURN(NULL, "index out of bounds");

  return (u8 *)vector->items + index * vector->item_size;
}

u8 vector_remove(vector_t *vector, usize index) {
  if (vector->len == 0)
    ERROR_RETURN(1, "vector is empty");
  
  if (index >= vector->len)
    ERROR_RETURN(1, "index out of bounds");

  if (vector->len == 1) {
    vector->len = 0;
    return 0;
  }

  vector->len--;

  u8 *item_ptr = (u8 *)vector->items + index * vector->item_size;
  u8 *end_ptr = (u8 *)vector->items + vector->len * vector->item_size;
  memcpy(item_ptr, end_ptr, vector->item_size);

  return 0;
}
