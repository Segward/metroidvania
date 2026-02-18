#include <engine/graphics/vertex.h>

void vertex_add_vertices(GLuint vbo, GLfloat *vertices, size_t size)
{
  const void *data = (const void *)vertices;
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)size, data, GL_STATIC_DRAW);
}

void vertex_add_indices(GLuint ebo, GLuint *indices, size_t size)
{
  const void *data = (const void *)indices;
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)size, data, GL_STATIC_DRAW);
}

void vertex_add_attribute(GLuint index, GLint size, 
                          GLsizei stride, size_t offset)
{
  const void *pointer = (const void *)(offset * sizeof(GLfloat));
  stride = stride * sizeof(GLfloat);
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
}

