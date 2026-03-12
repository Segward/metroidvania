#ifndef TILEMAP_H
#define TILEMAP_H

#include <pch.h>

typedef struct object
{
  vec2 pos;
  vec2 size;
} object_t;

void tilemap_init(void);
void tilemap_draw(void);
void tilemap_cleanup(void);

extern object_t *tilemap_objects;

#endif
