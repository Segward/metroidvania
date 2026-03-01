#ifndef quad_H
#define quad_H

#include <pch.h>

bool quad_init(void);
void quad_delete(void);
void quad_draw(vec2 position, vec2 size, vec4 color, GLuint texture, vec4 uv);

#endif
