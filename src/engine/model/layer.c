#include <engine/model/layer.h>
#include <stb/stb_ds.h>

void layer_make(layer_t *layer, int index)
{
  assert(layer);
  layer->map = NULL;
  layer->index = index;
}

void layer_push_sprite(layer_t *layer, sprite_t sprite, GLuint tex)
{
  layer_entry_t *map = layer->map;
  ptrdiff_t index = hmgeti(map, tex);
  if (index >= 0) 
  {
    arrput(layer->map[index].value, sprite);
  } else {
    sprite_t *sprites = NULL;
    arrput(sprites, sprite);
    hmput(layer->map, tex, sprites);
  }
}

void layer_draw(layer_t *layer)
{
  layer_entry_t *map = layer->map;
  for (ptrdiff_t i = 0; i < hmlen(map); i++) 
  {
    sprite_t *value = map[i].value;
    GLsizei count = (GLsizei)arrlen(value);
    if (count > 0)
      sprite_draw(value, map[i].key, count);
  }
}

void layer_cleanup(layer_t *layer)
{
  layer_entry_t *map = layer->map;
  for (ptrdiff_t i = 0; i < hmlen(map); i++)
    arrfree(map[i].value);

  hmfree(map);
  layer->map = NULL;
}
