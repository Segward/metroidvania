#include <model/sprite.h> 
#include <shapes/quad.h>

void sprite_create(sprite_t *sprite, GLuint texture)
{
  if (!sprite)
    return;

  sprite->texture = texture;
  sprite->animated = false;

  sprite_update(sprite, (vec2){ 50.0f, 50.0f }, (vec2){ 50.0f, 50.0f });
}

void sprite_apply_animation(sprite_t *sprite, animation_t *animation)
{
  if (!(sprite && animation))
    return;

  sprite->animation = animation; 
  sprite->animation->index = 0;
  sprite->animated = true;
}

void sprite_update(sprite_t *sprite, vec2 position, vec2 size)
{
  if (!sprite)
    return;

  vec2_dup(sprite->position, position);
  vec2_dup(sprite->size, size);

  if (sprite->animated)
    animation_next(sprite->animation); 
}

void sprite_draw(sprite_t *sprite)
{
  if (!sprite)
    return;

  vec4 uv = { 0.0f, 0.0f, 1.0f, 1.0f };
  
  if (sprite->animated)
  {
    size_t index = sprite->animation->index;
    vec4s animated_frame = sprite->animation->uvs[index];
    memcpy(uv, &animated_frame, sizeof(uv));
  }

  quad_draw(sprite->position, sprite->size, 
        (vec4){ 1.0f, 1.0f, 1.0f, 1.0f },
        sprite->texture, uv);
}
