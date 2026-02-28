#ifndef TEXTURE_H
#define TEXTURE_H

#include <pch.h>

GLuint texture_create(const char *path);
void texture_delete(GLuint *texture);

#endif
