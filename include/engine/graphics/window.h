#ifndef WINDOW_H
#define WINDOW_H

#include <pch.h>

void window_init(int width, int height, const char *title);
void window_cleanup(void);

extern GLFWwindow *window_handle;
extern int window_width;
extern int window_height;
extern vec2 mouse_world_pos;
extern vec2 mouse_screen_pos;
extern mat4x4 window_projection;

#endif
