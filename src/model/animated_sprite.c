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

  uv_t uv;
  uv.u0 = (float)column / (float)sprite->columns;
  uv.v0 = (float)row / (float)sprite->rows;
  uv.u1 = (float)(column + 1) / (float)sprite->columns;
  uv.v1 = (float)(row + 1) / (float)sprite->rows;

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

  uv_t uv = sprite->frames[sprite->index];

  quad_draw(sprite->position, sprite->size, 
          (vec4){ 1.0f, 1.0f, 1.0f, 1.0f },
          sprite->texture,
          (vec4){ uv.u0, uv.v0, uv.u1, uv.v1 });
}

void animated_sprite_delete(animated_sprite_t *sprite)
{
  if (!sprite)
    return;

  texture_delete(&sprite->texture);
}
