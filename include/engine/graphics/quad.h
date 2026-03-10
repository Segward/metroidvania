#ifndef QUAD_H
#define QUAD_H

#include <pch.h>

typedef struct quad
{
  vec2 offset;
  vec2 size;
  vec4 color;
  vec2 uv_offset;
  vec2 uv_size;
} quad_t;

void quad_init(void);
void quad_draw(quad_t *quads, GLuint tex, GLsizei count);
void quad_cleanup(void);

#endif
