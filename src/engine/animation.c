#include <engine/animation.h>

static void animation_update(animation_t *animation)
{
    int column = animation->index % animation->columns;
    int row    = animation->index / animation->columns;

    float u0 = column / (float)animation->columns;
    float u1 = (column + 1) / (float)animation->columns;

    float v1 = 1.0f - (row / (float)animation->rows);
    float v0 = 1.0f - ((row + 1) / (float)animation->rows);

    vec4 uv = { u0, v0, u1, v1 };
    vec4_dup(animation->uv, uv);
}

animation_t animation_create(const char *path, int columns, int rows)
{
  animation_t animation = {
    .columns = columns,
    .rows = rows,
    .valid = false
  };

  texture_t texture = texture_create(path);
  if (!texture.valid)
      return animation;

  animation.index = 0;
  animation.valid = true;
  animation.texture = texture;
  animation_update(&animation);

  return animation;
}

void animation_next(animation_t *animation)
{
  animation->index++;
  if (animation->index > animation->rows * animation->columns - 1)
    animation->index = 0;

  animation_update(animation);
}
