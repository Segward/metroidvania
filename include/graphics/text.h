#ifndef TEXT_H
#define TEXT_H

#include <pch.h>

void text_init(void);
void text_delete(void);
void text_draw(const char *text, vec2 position, float scale, vec4 color);

#endif
