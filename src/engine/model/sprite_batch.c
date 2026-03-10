#include <engine/model/sprite_batch.h>
#include <stb/stb_ds.h>

void sprite_batch_make(sprite_batch_t *batch, texture_t *tex)
{
  batch->tex = tex;
  batch->batch = NULL;
}

void sprite_batch_push(sprite_batch_t *batch, sprite_t sprite)
{
  arrput(batch->batch, sprite);
}

void sprite_batch_clear(sprite_batch_t *batch)
{
  arrsetlen(batch->batch, 0);
}

void sprite_batch_draw(sprite_batch_t *batch)
{
  GLsizei count = (GLsizei)arrlen(batch->batch);
  if (count == 0)
      return;

  sprite_draw(batch->batch, batch->tex, count);
}

void sprite_batch_cleanup(sprite_batch_t *batch)
{
  arrfree(batch->batch);
  batch->batch = NULL;
  batch->tex = NULL;
}
