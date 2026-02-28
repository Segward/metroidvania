#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <pch.h>

void vertex_buffer_generate(GLuint *vbo);
void vertex_buffer(GLuint vbo, GLfloat *data, size_t size);
void vertex_buffer_dynamic(GLuint vbo, size_t size);
void vertex_buffer_subtitue(GLuint vbo, GLfloat *data, size_t size, size_t offset);
void vertex_buffer_delete(GLuint *vbo);

#endif
