#ifndef RENDER_H
#define RENDER_H

#include <cglm/cglm.h>

typedef struct {
  mat4 proj;
} render_t;

void render_init(void);
void render_begin(void);
void render_end(void);

#endif
