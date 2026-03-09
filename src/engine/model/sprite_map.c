#include <engine/model/sprite_map.h>
#include <stb/stb_ds.h>

void sprite_map_add(sprite_map_entry_t **map, sprite_t sprite, GLuint texture)
{
  ptrdiff_t i = hmgeti(*map, texture);
  if (i >= 0) {
    arrput((*map)[i].value, sprite);
  } else {
    sprite_t *arr = NULL;
    arrput(arr, sprite);
    hmput(*map, texture, arr);
  }
}

void sprite_map_draw(sprite_map_entry_t *map)
{
  for (ptrdiff_t i = 0; i < hmlen(map); i++) {
    sprite_t *value = map[i].value;
    GLsizei count = (GLsizei)arrlen(value);
    if (count > 0)
      sprite_draw(value, map[i].key, count);
  }
}

void sprite_map_cleanup(sprite_map_entry_t **map)
{
  for (ptrdiff_t i = 0; i < hmlen(*map); i++)
    arrfree((*map)[i].value);

  hmfree(*map);
  *map = NULL;
}
