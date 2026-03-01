#include <model/animated_sprite.h>
#include <stb/stb_ds.h>
#include <graphics/texture.h>
#include <shapes/quad.h>

bool animated_sprite_create(animated_sprite_t *sprite, const char *path, unsigned columns, unsigned rows)
{
  if (!(sprite && path))
    return false;

  GLuint texture;
  if (!texture_create(&texture, path))
    return false;

  sprite->texture = texture;
  animated_sprite_update(sprite, (vec2){ 50.0f, 50.0f }, (vec2){ 50.0f, 50.0f });

  sprite->columns = columns;
  sprite->rows = rows;
  sprite->frames = NULL;
  sprite->index = 0;

  return true;
}

void animated_sprite_frame(animated_sprite_t *sprite, unsigned column, unsigned row)
{
  if (!sprite || sprite->columns == 0 || sprite->rows == 0)
    return;

  float u0 = (float)column / (float)sprite->columns;
  float v0 = (float)row / (float)sprite->rows;
  float u1 = (float)(column + 1) / (float)sprite->columns;
  float v1 = (float)(row + 1) / (float)sprite->rows;

  vec4s uv = {{ u0, v0, u1, v1 }};
  arrput(sprite->frames, uv);
}

void animated_sprite_update(animated_sprite_t *sprite, vec2 position, vec2 size)
{
  if (!sprite)
    return;

  vec2_dup(sprite->position, position);
  vec2_dup(sprite->size, size);
}

void animated_sprite_next_frame(animated_sprite_t *sprite)
{
  if (!sprite)
    return;

  size_t len = arrlen(sprite->frames);
  if (len == 0)
    return;

  sprite->index = (sprite->index + 1) % len;
}

void animated_sprite_draw(animated_sprite_t *sprite)
{
  if (!sprite)
    return;

  if (arrlen(sprite->frames) == 0)
    return;

  vec4s uvs = sprite->frames[sprite->index];
  vec4 uv;

  memcpy(uv, &uvs, sizeof(uv));

  quad_draw(sprite->position, sprite->size, 
          (vec4){ 1.0f, 1.0f, 1.0f, 1.0f },
          sprite->texture, uv);
}

void animated_sprite_delete(animated_sprite_t *sprite)
{
  if (!sprite)
    return;

  texture_delete(&sprite->texture);
}
