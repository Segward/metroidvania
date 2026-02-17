#ifndef render_H
#define render_H

#include <linmath.h>

int render_init(void);
void render_begin(void);
void render_quad(vec2 position, vec2 size, vec4 color);
void render_end(void);

#endif
