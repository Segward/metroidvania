#ifndef QUAD_H
#define QUAD_H

#include <pch.h>

typedef struct quad
{
  vec2 offset;
  vec2 size;
  vec4 color;
} quad_t;

void quad_init(void);
void quad_cleanup(void);
void quad_draw(quad_t *quads,  GLuint tex, GLsizei count);

#endif
