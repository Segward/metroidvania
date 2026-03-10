#ifndef SPRITE_H
#define SPRITE_H

#include <engine/graphics/texture.h>

typedef struct sprite
{
  vec2 offset;
  vec2 size;
  vec4 color;
  vec2 atlas_start;
  vec2 atlas_size;
} sprite_t;

void sprite_init(void);
void sprite_draw(sprite_t *sprites, texture_t *tex, GLsizei count);
void sprite_cleanup(void);

#endif
