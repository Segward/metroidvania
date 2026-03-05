#include <model/object.h>
#include <graphics/quad.h>
#include <global.h>

void object_create(object_t *object, GLuint tex)
{
  assert(object && tex);
  vec2_dup(object->pos, (vec2){ 0.0f, 0.0f });
  vec2_dup(object->size, (vec2){ 100.0f, 100.0f });
  object->tex = tex;
}

void object_draw(object_t *object)
{
  assert(object);
  quad_draw(object->pos, object->size, global.tint, 
            object->tex, (vec4){ 0.0f, 0.0f, 1.0f, 1.0f });
}
