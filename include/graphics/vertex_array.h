#ifndef VERTEX_ARRAY_H
#define VERTEX_ARRAY_H

#include <pch.h>

void vertex_array_generate(GLuint *vao);
void vertex_array_bind(GLuint vao);
void vertex_array_attribute(GLuint index, GLint size, GLsizei stride, size_t offset);
void vertex_array_delete(GLuint *vao);

#endif
