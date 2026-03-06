#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include <engine/graphics/sprite.h>

typedef struct sprite_batch
{
  sprite_t *arr;
  GLuint tex;
} sprite_batch_t;

void sprite_batch_make(sprite_batch_t *batch, GLuint tex);
sprite_t *sprite_batch_push(sprite_batch_t *batch, sprite_t sprite);
void sprite_batch_draw(sprite_batch_t *batch);
void sprite_batch_cleanup(sprite_batch_t *batch);

#endif

