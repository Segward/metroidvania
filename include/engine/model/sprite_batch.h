#ifndef SPRITE_BATCH_H
#define SPRITE_BATCH_H

#include <engine/graphics/sprite.h>
#include <engine/graphics/texture.h>

typedef struct sprite_batch
{
  texture_t *tex;
  sprite_t *batch;
} sprite_batch_t;

void sprite_batch_make(sprite_batch_t *batch, texture_t *tex);
void sprite_batch_push(sprite_batch_t *batch, sprite_t sprite); 
void sprite_batch_clear(sprite_batch_t *batch);
void sprite_batch_draw(sprite_batch_t *batch);
void sprite_batch_cleanup(sprite_batch_t *batch);

#endif
