#ifndef QUAD_H
#define QUAD_H

#include <pch.h>

void quad_init(void);
void quad_cleanup(void);
void quad_draw(vec2 pos, vec2 size, vec4 color, GLuint tex, vec4 uv);

#endif
