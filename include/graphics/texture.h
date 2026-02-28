#ifndef TEXTURE_H
#define TEXTURE_H

#include <pch.h>

bool texture_create(GLuint *texture, const char *path);
void texture_delete(GLuint *texture);

#endif
