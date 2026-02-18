#include <engine/gfx/render.h>
#include <engine/gfx/mesh.h>
#include <engine/gfx/shader.h>
#include <engine/window.h>
#include <engine/global.h>
#include <engine/gfx/texture.h>

#include <stdio.h>

static GLuint quad_vao;
static GLuint quad_vbo;
static GLuint quad_ebo;
static GLuint quad_shader;
static GLuint texture;

int render_init(void) {
  if (!window_init(640, 480)) {
    fprintf(stderr, "failed to initialize window\n");
    return 0;
  };

  mesh_init_quad(&quad_vao, &quad_vbo, &quad_ebo);
  quad_shader = shader_create("assets/quad.vert", "assets/quad.frag");
  if (!quad_shader) {
    fprintf(stderr, "failed to initialize quad shader\n");
    return 0;
  }

  texture = texture_create("assets/texture.png");

  return 1;
}

void render_begin(void) {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void render_quad(vec2 position, vec2 size, vec4 color) {
  glUseProgram(quad_shader);

  mat4x4 model;
  mat4x4_identity(model);

  mat4x4_translate(model, position[0], position[1], 0);
  mat4x4_scale_aniso(model, model, size[0], size[1], 1);

  mat4x4 proj;
  mat4x4_ortho(proj, 0, global.window.width, 0, global.window.height, -1, 1);

  glUniformMatrix4fv(glGetUniformLocation(quad_shader, "uProj"), 1, GL_FALSE, &proj[0][0]);
  glUniformMatrix4fv(glGetUniformLocation(quad_shader, "uModel"), 1, GL_FALSE, &model[0][0]);
  glUniform4fv(glGetUniformLocation(quad_shader, "uColor"), 1, color);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glUniform1i(glGetUniformLocation(quad_shader, "uTexture"), 0);
  
  glBindVertexArray(quad_vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
  glBindVertexArray(0);
}

void render_end(void) {
  glfwSwapBuffers(global.window.handle);
  glfwPollEvents();
}
