#include <engine/graphics/quad.h>
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
static GLuint i_vbo;
static GLuint program;

static GLint u_proj;
static GLint u_view;
static GLint u_tex;

static void attrib_float(GLuint index, GLint count, GLsizei stride, size_t offset)
{
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
}

static void attrib_float_instanced(GLuint index, GLint count, GLsizei stride, size_t offset)
{
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, count, GL_FLOAT, GL_FALSE, stride, (const void*)offset);
  glVertexAttribDivisor(index, 1);
}

void quad_init(void)
{
  const GLsizei vertex_stride = 4 * sizeof(GLfloat);
  const GLsizei instance_stride = sizeof(quad_t);

  shader_make(&program, "assets/shaders/quad.vert", "assets/shaders/quad.frag");

  u_proj = glGetUniformLocation(program, "uProj");
  u_view = glGetUniformLocation(program, "uView");
  u_tex  = glGetUniformLocation(program, "uTex");

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenBuffers(1, &i_vbo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  attrib_float(0, 2, vertex_stride, 0);
  attrib_float(1, 2, vertex_stride, 2 * sizeof(GLfloat));

  glBindBuffer(GL_ARRAY_BUFFER, i_vbo);
  glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STREAM_DRAW);

  attrib_float_instanced(2, 2, instance_stride, offsetof(quad_t, offset));
  attrib_float_instanced(3, 2, instance_stride, offsetof(quad_t, size));
  attrib_float_instanced(4, 4, instance_stride, offsetof(quad_t, color));
  attrib_float_instanced(5, 2, instance_stride, offsetof(quad_t, uv_offset));
  attrib_float_instanced(6, 2, instance_stride, offsetof(quad_t, uv_size));

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void quad_draw(quad_t *quads, GLuint tex, GLsizei count)
{
  if (!quads || count <= 0 || tex == 0)
    return;

  glUseProgram(program);
  glBindVertexArray(vao);

  glUniformMatrix4fv(u_proj, 1, GL_FALSE, &global.proj[0][0]);
  glUniformMatrix4fv(u_view, 1, GL_FALSE, &global.view[0][0]);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(u_tex, 0);

  glBindBuffer(GL_ARRAY_BUFFER, i_vbo);

  GLsizeiptr bytes = (GLsizeiptr)count * (GLsizeiptr)sizeof(quad_t);

  glBufferData(GL_ARRAY_BUFFER, bytes, NULL, GL_STREAM_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, bytes, quads);

  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0, count);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void quad_cleanup(void)
{
  glDeleteBuffers(1, &i_vbo);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(program);
}
