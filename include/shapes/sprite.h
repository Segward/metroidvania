#ifndef SPRITE_H
#define SPRITE_H

#include <pch.h>

bool sprite_init(void);
void sprite_delete(void);
void sprite_draw(vec2 position, vec2 size, vec4 color, GLuint texture, vec4 uv);

#endif
