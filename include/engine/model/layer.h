#ifndef LAYER_H
#define LAYER_H

#include <pch.h>
#include <engine/graphics/sprite.h>

typedef struct layer_entry
{
  GLuint key;
  sprite_t *value;
} layer_entry_t;

typedef struct layer
{
  layer_entry_t *map;
  int index;
} layer_t;

void layer_make(layer_t *layer, int index);
void layer_push(layer_t *layer, sprite_t sprite, GLuint tex);
void layer_draw(layer_t *layer);
void layer_clear(layer_t *layer);
void layer_cleanup(layer_t *layer);

#endif
