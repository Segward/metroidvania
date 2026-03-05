#ifndef IQUAD_H
#define IQUAD_H

#include <pch.h>

void iquad_init(void);
void iquad_cleanup(void);
void iquad_draw(vec2 *offsets, int count, vec2 size, vec4 color, GLuint tex);

#endif
