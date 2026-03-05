#include <graphics/quad.h>
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

void quad_init(void)
{
  glsl_create(&program, "assets/shaders/quad.vert", "assets/shaders/quad.frag");

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
  glBufferData(GL_ARRAY_BUFFER, 0, NULL, GL_STREAM_DRAW);

  glEnableVertexAttribArray(2);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(quad_t), (void*)offsetof(quad_t, offset));
  glVertexAttribDivisor(2, 1);

  glEnableVertexAttribArray(3);
  glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(quad_t), (void*)offsetof(quad_t, size));
  glVertexAttribDivisor(3, 1);

  glEnableVertexAttribArray(4);
  glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(quad_t), (void*)offsetof(quad_t, color));
  glVertexAttribDivisor(4, 1);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void quad_cleanup(void)
{
  glDeleteBuffers(1, &instance);
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
  glDeleteProgram(program);
}

void quad_draw(quad_t *quads, GLuint tex, GLsizei count)
{
  glUseProgram(program);

  glUniformMatrix4fv(glGetUniformLocation(program, "uProj"), 1, GL_FALSE, &global.proj[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "uView"), 1, GL_FALSE, &global.view[0][0]);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(glGetUniformLocation(program, "uTex"), 0);

  glBindBuffer(GL_ARRAY_BUFFER, instance);

  GLsizeiptr bytes = (GLsizeiptr)count * (GLsizeiptr)sizeof(quad_t);
  glBufferData(GL_ARRAY_BUFFER, bytes, NULL, GL_STREAM_DRAW);
  glBufferSubData(GL_ARRAY_BUFFER, 0, bytes, quads);

  glBindVertexArray(vao);
  glDrawElementsInstanced(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0, count);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
