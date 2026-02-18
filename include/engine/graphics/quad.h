#ifndef QUAD_H
#define QUAD_H

#include <glad/glad.h>
#include <linmath.h>
#include <stdbool.h>

bool quad_init(void);
void quad_draw(vec2 position, vec2 size, vec4 color);

#endif
