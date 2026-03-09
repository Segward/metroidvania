#ifndef SPRITE_MAP_H
#define SPRITE_MAP_H

#include <pch.h>
#include <engine/graphics/sprite.h>

typedef struct sprite_map_entry
{
  GLuint key;
  sprite_t *value;
} sprite_map_entry_t;

void sprite_map_add(sprite_map_entry_t **map, sprite_t sprite, GLuint key);
void sprite_map_draw(sprite_map_entry_t *map);
void sprite_map_cleanup(sprite_map_entry_t **map);

#endif
