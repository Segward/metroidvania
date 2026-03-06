#include <model/quad_batch.h>
#include <stb/stb_ds.h>

void quad_batch_init(quad_batch_t *batch, GLuint tex)
{
  assert(batch && tex);
  batch->quads = NULL;
  batch->tex = tex;
}

void quad_batch_push(quad_batch_t *batch, quad_t quad)
{
  assert(batch);
  arrput(batch->quads, quad);
}

void quad_batch_draw(quad_batch_t *batch)
{
  assert(batch);
  size_t len = arrlen(batch->quads);
  quad_draw(batch->quads, batch->tex, (GLsizei)len);
}

void quad_batch_cleanup(quad_batch_t *batch)
{
  assert(batch);
  arrfree(batch->quads);
}

