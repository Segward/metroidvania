#ifndef QUAD_BATCH_H
#define QUAD_BATCH_H

#include <graphics/quad.h>

typedef struct quad_batch
{
  quad_t *quads;
  GLuint tex;
} quad_batch_t;

void quad_batch_init(quad_batch_t *batch, GLuint tex);
void quad_batch_push(quad_batch_t *batch, quad_t quad);
void quad_batch_draw(quad_batch_t *batch);
void quad_batch_cleanup(quad_batch_t *batch);

#endif
