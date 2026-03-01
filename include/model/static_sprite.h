#ifndef STATIC_SPRITE_H
#define STATIC_SPRITE_H

#include <pch.h>

typedef struct static_sprite
{
  vec2 position;
  vec2 size;
  GLuint texture;
} static_sprite_t;

bool static_sprite_create(static_sprite_t *sprite, const char *path);
void static_sprite_update(static_sprite_t *sprite, vec2 position, vec2 size);
void static_sprite_draw(static_sprite_t sprite);
void static_sprite_delete(static_sprite_t *sprite);

#endif
