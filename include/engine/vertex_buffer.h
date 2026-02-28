#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <glad/glad.h>
#include <stddef.h>

void vertex_buffer(GLuint vbo, GLfloat *data, size_t size);
void vertex_buffer_dynamic(GLuint vbo, size_t size);
void vertex_buffer_subtitue(GLuint vbo, GLfloat *data, size_t size, size_t offset);
void vertex_buffer_delete(GLuint *vbo);

#endif
