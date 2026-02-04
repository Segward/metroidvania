#ifndef RENDER_H
#define RENDER_H

#include <linmath.h>

void render_init(void);
void render_begin(void);
void render_end(void);
void render_quad(vec2 position, vec2 size, vec4 color);

#endif
