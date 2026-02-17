#ifndef PHYSICS_H
#define PHYSICS_H

#include <linmath.h>
#include <stddef.h>

typedef struct {
  vec2 position;
  vec2 size;
} aabb_t;

typedef struct {
  aabb_t aabb;
  vec2 velocity;
  vec2 acceleration;
} object_t;

void physics_init(void);
int physics_object_create(vec2 position, vec2 size, size_t *out_index);
void physics_update(void);
object_t *physics_object_get(size_t index);

#endif
