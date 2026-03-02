#ifndef SPRITE_H
#define SPRITE_H

#include <pch.h>

typedef struct sprite
{
  vec2 position;
  vec2 size;
  GLuint texture;
} sprite_t;

void sprite_create(sprite_t *sprite, GLuint texture);
void sprite_draw(sprite_t *sprite);

#endif
