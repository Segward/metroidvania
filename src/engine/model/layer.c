#include <engine/model/layer.h>
#include <stb/stb_ds.h>

void layer_make(layer_t *layer, texture_t *atlas)
{
  if (!layer || !atlas)
    return;

  layer->sprites = NULL;
  layer->atlas = atlas;
}

sprite_t *layer_make_sprite(layer_t *layer)
{
  if (!layer)
      return NULL;

  size_t index = arrlen(layer->sprites);

  sprite_t sprite = {0};
  arrput(layer->sprites, sprite);

  return &layer->sprites[index];
}

void layer_draw(layer_t *layer)
{
  if (!layer || !layer->atlas || !layer->sprites)
    return;

  GLsizei count = (GLsizei)arrlen(layer->sprites);
  sprite_draw(layer->sprites, layer->atlas, count);
}

void layer_cleanup(layer_t *layer)
{
  if (!layer)
    return;

  arrfree(layer->sprites);
  layer->sprites = NULL;
  layer->atlas = NULL;
}
