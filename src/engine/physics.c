#include <engine/physics.h>
#include <engine/global.h>
#include <engine/vector.h>

#include <stdio.h>

static vector_t *objects;

void physics_init(void) {
  objects = vector_create(sizeof(object_t), 0);
}

int physics_object_create(vec2 position, vec2 size, size_t *out_index) {
  object_t object = {
    .aabb = {
      .position = { position[0], position[1] },
      .size = { size[0], size[1] }
    },

    .velocity = { 0, 0 },
    .acceleration = { 0, 0 }
  };

  size_t index;
  if (!vector_append(objects, &object, &index)) {
    fprintf(stderr, "failed to append to vector\n");
    return 0;
  }

  *out_index = index;
  return 1;
}

void physics_update(void) {
  object_t *object;
  for (size_t i = 0; i < objects->len; i++) {
    object = vector_get(objects, i);
    object->velocity[0] += object->acceleration[0] * global.time.delta;
    object->velocity[1] += object->acceleration[1] * global.time.delta;
    object->aabb.position[0] += object->velocity[0] * global.time.delta;
    object->aabb.position[1] += object->velocity[1] * global.time.delta;
  }
}

object_t *physics_object_get(size_t index) {
  return vector_get(objects, index);
}
