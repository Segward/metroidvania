#include <graphics/iquad.h>
#include <graphics/glsl.h>
#include <global.h>

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

#define IQUAD_MAX_INSTANCES 10000

void iquad_init(void)
{
  glsl_create(&program, "assets/shaders/iquad.vert", "assets/shaders/quad.frag");

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);
  glGenBuffers(1, &instance);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glBindBuffer(GL_ARRAY_BUFFER, instance);
  glBufferData(GL_ARRAY_BUFFER, IQUAD_MAX_INSTANCES * sizeof(vec2), NULL, GL_STREAM_DRAW);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vec2), (void*)0);
  glEnableVertexAttribArray(2);
  glVertexAttribDivisor(2, 1);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void iquad_cleanup(void)
{
  glDeleteBuffers(1, &instance);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

void iquad_draw(vec2 *offsets, int count, vec2 size, vec4 color, GLuint tex)
{
  if (count <= 0) return;
  if (count > IQUAD_MAX_INSTANCES) count = IQUAD_MAX_INSTANCES;

  glUseProgram(program);

  glUniform2fv(glGetUniformLocation(program, "uSize"), 1, &size[0]);
  glUniform4fv(glGetUniformLocation(program, "uColor"), 1, &color[0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "uProj"), 1, GL_FALSE, &global.proj[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "uView"), 1, GL_FALSE, &global.view[0][0]);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(glGetUniformLocation(program, "uTex"), 0);

  glBindBuffer(GL_ARRAY_BUFFER, instance);
  glBufferData(GL_ARRAY_BUFFER, IQUAD_MAX_INSTANCES * sizeof(vec2), NULL, GL_STREAM_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, count * sizeof(vec2), offsets);

  glBindVertexArray(vao);
  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0, count);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
