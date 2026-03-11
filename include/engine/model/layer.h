#ifndef LAYER_H
#define LAYER_H

#include <engine/graphics/sprite.h>
#include <engine/graphics/texture.h>

typedef struct layer
{
  texture_t *atlas;
  sprite_t *sprites;
} layer_t;

void layer_make(layer_t *layer, texture_t *atlas);
sprite_t *layer_make_sprite(layer_t *layer);
void layer_draw(layer_t *layer);
void layer_cleanup(layer_t *layer);

#endif
