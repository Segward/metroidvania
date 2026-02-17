#ifndef VERTEX_H
#define VERTEX_H

#include <glad/glad.h>

void vertex_buffers_init(GLuint *vao, GLuint *vbo, GLuint *ebo);

void vertex_add_attribute(GLuint index, GLint size, GLenum type, 
                          GLboolean normalized, GLsizei stride, 
                          const void *offset);

void vertex_add_buffer_data(GLuint buffer, GLenum target, GLsizeiptr size, 
                            const void *data, GLenum usage);

#endif
