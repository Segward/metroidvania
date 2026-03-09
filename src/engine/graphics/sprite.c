#include <engine/graphics/sprite.h>
#include <engine/graphics/shader.h>
#include <engine/model/global.h>

static GLfloat vertices[] = {
  1.0f, 1.0f, 1.0f, 0.0f,
  1.0f, 0.0f, 1.0f, 1.0f,
  0.0f, 0.0f, 0.0f, 1.0f,
  0.0f, 1.0f, 0.0f, 0.0f
};

static GLuint indices[] = { 
  0, 1, 3, 
  1, 2, 3 
};

static GLuint vao;
static GLuint vbo;
static GLuint ebo;
static GLuint program;
static GLuint instance;

static void attrib_float(GLuint index, GLint count, GLsizei stride, size_t offset)
{
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, stride, (void*)offset);
}

static void attrib_float_instanced(GLuint index, GLint count, GLsizei stride, size_t offset)
{
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, stride, (void*)offset);
  glVertexAttribDivisor(index, 1);
}

void sprite_init(void)
{
  const GLsizei vertex_stride = 4 * sizeof(GLfloat);
  const GLsizei instance_stride = sizeof(sprite_t);

  shader_make(&program, "assets/shaders/quad.vert", "assets/shaders/quad.frag");

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenBuffers(1, &instance);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  attrib_float(0, 2, vertex_stride, 0);
  attrib_float(1, 2, vertex_stride, 2 * sizeof(GLfloat));

  glBindBuffer(GL_ARRAY_BUFFER, instance);
  glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STREAM_DRAW);

  attrib_float_instanced(2, 2, instance_stride, offsetof(sprite_t, offset));
  attrib_float_instanced(3, 2, instance_stride, offsetof(sprite_t, size));
  attrib_float_instanced(4, 4, instance_stride, offsetof(sprite_t, color));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void sprite_draw(sprite_t *sprites, GLuint tex, GLsizei count)
{
  glUseProgram(program);

  glUniformMatrix4fv(glGetUniformLocation(program, "uProj"), 1, GL_FALSE, &global.proj[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "uView"), 1, GL_FALSE, &global.view[0][0]);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(glGetUniformLocation(program, "uTex"), 0);

  glBindBuffer(GL_ARRAY_BUFFER, instance);

  GLsizeiptr bytes = (GLsizeiptr)count * (GLsizeiptr)sizeof(sprite_t);
  glBufferData(GL_ARRAY_BUFFER, bytes, NULL, GL_STREAM_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, bytes, sprites);

  glBindVertexArray(vao);
  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0, count);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void sprite_cleanup(void)
{
  glDeleteBuffers(1, &instance);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(program);
}

