#include <model/static_sprite.h>
#include <graphics/texture.h>
#include <shapes/quad.h>

bool static_sprite_create(static_sprite_t *sprite, const char *path)
{
  if (!(sprite && path))
    return false;

  GLuint texture;
  if (!texture_create(&texture, path))
    return false;

  sprite->texture = texture;
  static_sprite_update(sprite, (vec2){ 50.0f, 50.0f }, (vec2){ 50.0f, 50.0f });

  return true;
}

void static_sprite_update(static_sprite_t *sprite, vec2 position, vec2 size)
{
  if (!sprite)
    return;

  vec2_dup(sprite->position, position);
  vec2_dup(sprite->size, size);
}

void static_sprite_draw(static_sprite_t sprite)
{
  quad_draw(sprite.position, sprite.size, 
            (vec4){ 1.0f, 1.0f, 1.0f, 1.0f },
            sprite.texture,
            (vec4){0.0f, 0.0f, 1.0f, 1.0f});
}

void static_sprite_delete(static_sprite_t *sprite)
{
  if (!(sprite))
    return;

  texture_delete(&sprite->texture);
}
