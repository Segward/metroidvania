#include <util/animation.h>
#include <stb/stb_ds.h>

void animation_create(animation_t *animation, int columns, int rows)
{
  if (!animation)
    return;

  animation->columns = columns;
  animation->rows = rows;
  animation->uvs = NULL;
  animation->index = 0;
}

void animation_frame(animation_t *animation, int column, int row)
{
  if (!animation)
    return;

  float u0 = (float)column / (float)animation->columns;
  float v0 = (float)row / (float)animation->rows;
  float u1 = (float)(column + 1) / (float)animation->columns;
  float v1 = (float)(row + 1) / (float)animation->rows;

  vec4s uv = {{ u0, v0, u1, v1 }};
  arrput(animation->uvs, uv);
}

void animation_next(animation_t *animation)
{
  if (!animation)
    return;

  size_t length = arrlen(animation->uvs);
  if (length == 0)
    return;

  animation->index = (animation->index + 1) % length;
}

void animation_delete(animation_t *animation)
{
  if (!animation)
    return;

  arrfree(animation->uvs);
}
