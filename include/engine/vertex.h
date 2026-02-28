#ifndef VERTEX_H
#define VERTEX_H

#include <glad/glad.h>
#include <stddef.h>

void vertex_add_vertices(GLuint vbo, GLfloat *vertices, size_t size);
void vertex_add_indices(GLuint ebo, GLuint *indices, size_t size);
void vertex_add_attribute(GLuint index, GLint size, GLsizei stride, size_t offset);
void vertex_add_dynamic_buffer(GLuint vbo, size_t size);
void vertex_update_buffer(GLuint vbo, const void *data, size_t size, size_t offset);

#endif
