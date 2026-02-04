#include <glad/glad.h>
#include <engine/render.h>
#include <engine/render_internal.h>
#include <engine/window.h>
#include <engine/global.h>

static mat4x4 proj;

void render_init(void) {
  window_init(640, 480);
  render_quad_init();

  mat4x4_ortho(proj, 0, global.window.width, 0, global.window.height, -2, 2);

  glUseProgram(quad_shader);
  glUniformMatrix4fv(glGetUniformLocation(quad_shader, "uProj"), 1, GL_FALSE, &proj[0][0]);
}

void render_begin(void) {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void render_end(void) {
  glfwSwapBuffers(global.window.handle);
  glfwPollEvents();
}

void render_quad(vec2 position, vec2 size, vec4 color) {
  glUseProgram(quad_shader);

  mat4x4 model;
  mat4x4_identity(model);

  mat4x4_translate(model, position[0], position[1], 0);
  mat4x4_scale_aniso(model, model, size[0], size[1], 1);

  glUniformMatrix4fv(glGetUniformLocation(quad_shader, "uModel"), 1, GL_FALSE, &model[0][0]);
  glUniform4fv(glGetUniformLocation(quad_shader, "uColor"), 1, color);

  glBindVertexArray(quad_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
  glBindVertexArray(0);
}
