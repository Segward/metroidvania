#ifndef ANIMATED_SPRITE_H
#define ANIMATED_SPRITE_H

#include <pch.h>

typedef struct animated_sprite
{
  vec2 position;
  vec2 size;
  GLuint texture;
  unsigned columns;
  unsigned rows;
  vec4s *frames;
  size_t index;
} animated_sprite_t;

bool animated_sprite_create(animated_sprite_t *sprite, const char *path, unsigned columns, unsigned rows);
void animated_sprite_frame(animated_sprite_t *sprite, unsigned column, unsigned row);
void animated_sprite_update(animated_sprite_t *sprite, vec2 position, vec2 size);
void animated_sprite_next_frame(animated_sprite_t *sprite);
void animated_sprite_draw(animated_sprite_t *sprite);
void animated_sprite_delete(animated_sprite_t *sprite);

#endif
