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

void quad_init(void)
{
  glsl_create(&program, "assets/shaders/quad.vert", "assets/shaders/quad.frag");

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void *)(2 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);
}

void quad_cleanup(void)
{
  glDeleteBuffers(1, &ebo);
  glDeleteBuffers(1, &vbo);
  glDeleteVertexArrays(1, &vao);
}

void quad_draw(vec2 pos, vec2 size, vec4 color, GLuint tex, vec4 uv)
{
  glUseProgram(program);
  glUniform2fv(glGetUniformLocation(program, "uPos"), 1, &pos[0]);
  glUniform2fv(glGetUniformLocation(program, "uSize"), 1, &size[0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "uProj"), 1, GL_FALSE, &global.proj[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(program, "uView"), 1, GL_FALSE, &global.view[0][0]);
  glUniform4fv(glGetUniformLocation(program, "uUV"), 1, &uv[0]);
  glUniform4fv(glGetUniformLocation(program, "uColor"), 1, &color[0]);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, tex);
  glUniform1i(glGetUniformLocation(program, "uTex"), 0);

  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void *)0);
}
