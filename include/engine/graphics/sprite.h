#ifndef SPRITE_H
#define SPRITE_H

#include <pch.h>

typedef struct sprite
{
  vec2 offset;
  vec2 size;
  vec4 color;
} sprite_t;

void sprite_init(void);
void sprite_draw(sprite_t *sprites, GLuint tex, GLsizei count);
void sprite_cleanup(void);

#endif
