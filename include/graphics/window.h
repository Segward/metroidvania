#ifndef WINDOW_H
#define WINDOW_H

#include <stdbool.h>

bool window_init(int width, int height, const char *title);
void window_close(void);

#endif
