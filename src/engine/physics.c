#include <engine/physics.h>
#include <engine/global.h>
#include <engine/vector.h>
#include <engine/util.h>

static vector_t *objects;

void physics_init(void) {
  objects = vector_create(sizeof(object_t), 0);
}

u8 physics_object_create(vec2 position, vec2 size, usize *out_index) {
  object_t object = {
    .aabb = {
      .position = { position[0], position[1] },
      .size = { size[0] * 0.5, size[1] * 0.5 }
    },

    .velocity = { 0, 0 },
    .acceleration = { 0, 0 }
  };

  usize index;
  if (vector_append(objects, &object, &index) != 0)
    ERROR_RETURN(1, "failed to append to vector");

  *out_index = index;
  return 0;
}

void physics_update(void) {
  object_t *object;
  for (usize i = 0; i < objects->len; i++) {
    object = vector_get(objects, i);
    object->velocity[0] += object->acceleration[0] * global.time.delta;
    object->velocity[1] += object->acceleration[1] * global.time.delta;
    object->aabb.position[0] += object->velocity[0] * global.time.delta;
    object->aabb.position[1] += object->velocity[1] * global.time.delta;
  }
}

object_t *physics_object_get(usize index) {
  return vector_get(objects, index);
}
