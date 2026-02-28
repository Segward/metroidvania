#include <graphics/vertex_buffer.h>

void vertex_buffer_generate(GLuint *vbo)
{
  if (!vbo) return;

  glGenBuffers(1, vbo);
}

void vertex_buffer(GLuint vbo, GLfloat *data, size_t size)
{
  if (!(vbo && data)) return;

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)size, data, GL_STATIC_DRAW);
}

void vertex_buffer_dynamic(GLuint vbo, size_t size)
{
  if (!vbo) return;

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, (GLsizeiptr)size, NULL, GL_DYNAMIC_DRAW);
}

void vertex_buffer_subtitue(GLuint vbo, GLfloat *data, size_t size, size_t offset)
{
  if (!(vbo && data)) return;

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferSubData(GL_ARRAY_BUFFER, (GLintptr)offset, (GLsizeiptr)size, data);
}

void vertex_buffer_delete(GLuint *vbo)
{
  if (!(vbo && *vbo)) return;

  glDeleteBuffers(1, vbo);
  *vbo = 0;
}

