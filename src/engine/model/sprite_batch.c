#include <engine/model/sprite_batch.h>
#include <stb/stb_ds.h>

void sprite_batch_make(sprite_batch_t *batch, GLuint tex)
{
  assert(batch && tex);
  batch->tex = tex;
  batch->arr = NULL;
}

sprite_t *sprite_batch_push(sprite_batch_t *batch, sprite_t sprite)
{
  assert(batch);
  arrput(batch->arr, sprite);

  size_t len = arrlen(batch->arr);
  return &batch->arr[len - 1];
}

void sprite_batch_draw(sprite_batch_t *batch)
{
  GLsizei count = (GLsizei)arrlen(batch->arr);
  if (count > 0)
    sprite_draw(batch->arr, batch->tex, count);
}

void sprite_batch_cleanup(sprite_batch_t *batch)
{
  arrfree(batch->arr);
}
