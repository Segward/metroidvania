#include <graphics/index_buffer.h>

void index_buffer_generate(GLuint *ebo)
{
  if (!ebo) return;

  glGenBuffers(1, ebo);
}

void index_buffer(GLuint ebo, GLuint *data, size_t size)
{
  if (!(ebo && data)) return;

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)size, data, GL_STATIC_DRAW);

}

void index_buffer_delete(GLuint *ebo)
{
  if (!(ebo && *ebo)) return;

  glDeleteBuffers(1, ebo);
  *ebo = 0;
}
