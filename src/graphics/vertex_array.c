#include <graphics/vertex_array.h>

void vertex_array_generate(GLuint *vao)
{
  if (!vao) return;

  glGenVertexArrays(1, vao);
}

void vertex_array_bind(GLuint vao)
{
  if (!vao) return;

  glBindVertexArray(vao);
}

void vertex_array_attribute(GLuint index, GLint size, GLsizei stride, size_t offset)
{
  const void *pointer = (const void *)(offset * sizeof(GLfloat));
  stride = stride * sizeof(GLfloat);
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
}

void vertex_array_delete(GLuint *vao)
{
  if (!(vao && *vao)) return;

  glDeleteVertexArrays(1, vao);
  *vao = 0;
}
