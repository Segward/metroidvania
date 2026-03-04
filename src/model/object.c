#include <model/object.h>
#include <graphics/quad.h>
#include <util/global.h>

void object_create(object_t *object, GLuint texture)
{
  assert(object && texture);
  object->texture = texture;

  vec2_dup(object->position, (vec2){ 100.0f, 100.0f });
  vec2_dup(object->size, (vec2){ 100.0f, 100.0f });
}

void object_draw(object_t *object)
{
  assert(object);

  quad_draw(object->position,
            object->size,
            global.tint,
            object->texture,
            (vec4){ 0.0f, 0.0f, 1.0f, 1.0f });
}
