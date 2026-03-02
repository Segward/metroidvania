#ifndef TEXTURE_H
#define TEXTURE_H

#include <pch.h>

void texture_create(GLuint *texture, const char *path);
void texture_white(GLuint *texture);
void texture_delete(GLuint *texture);

#endif
