#include <model/sprite.h> 
#include <graphics/quad.h>

void sprite_create(sprite_t *sprite, GLuint texture)
{
  if (!sprite)
    return;

  sprite->texture = texture;

  vec2_dup(sprite->position, (vec2){ 400.0f, 400.0f });
  vec2_dup(sprite->size, (vec2){ 100.0f, 100.0f });
}

void sprite_draw(sprite_t *sprite)
{
  if (!sprite)
    return;

  quad_draw(sprite->position, sprite->size, 
        (vec4){ 1.0f, 1.0f, 1.0f, 1.0f },
        sprite->texture,
        (vec4){ 0.0f, 0.0f, 1.0f, 1.0f });
}
