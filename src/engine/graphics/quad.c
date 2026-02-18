#include <engine/graphics/quad.h>
#include <engine/graphics/vertex.h>
#include <engine/graphics/shader.h>
#include <engine/graphics/texture.h>
#include <engine/global.h>
#include <stdbool.h>
#include <stdio.h>

static GLfloat vertices[] = {
   0.5f,  0.5f, 0.0f, 1.0f, 0.0f,
   0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
  -0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
  -0.5f,  0.5f, 0.0f, 0.0f, 0.0f
};

static GLuint indices[] = {
  0, 1, 3,
  1, 2, 3
};

static GLuint vao;
static GLuint vbo;
static GLuint ebo;
static GLuint program;
static GLuint texture;

bool quad_init(void)
{
  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo);
  glGenBuffers(1, &ebo);

  glBindVertexArray(vao);

  vertex_add_vertices(vbo, vertices, sizeof(vertices));
  vertex_add_indices(ebo, indices, sizeof(indices));

  GLsizei stride = (GLsizei)(5 * sizeof(GLfloat));
  vertex_add_attribute(0, 3, stride, 0);
  vertex_add_attribute(1, 2, stride, 3 * sizeof(GLfloat));

  glBindVertexArray(0);

  program = shader_create("assets/quad.vert", "assets/quad.frag");
  if (!program) return false;

  texture = texture_create("assets/texture.png");
  if (!texture) return false;

  return true;
}

mat4x4 model;
mat4x4 projection;

void quad_draw(vec2 position, vec2 size, vec4 color)
{
  mat4x4_identity(model);
  mat4x4_translate(model, position[0], position[1], 0);
  mat4x4_scale_aniso(model, model, size[0], size[1], 1);
  mat4x4_ortho(projection, 0, global.window.width, 0, global.window.height, -1, 1);
  
  glUseProgram(program);
  shader_update_mat4x4(program, "uModel", model);
  shader_update_mat4x4(program, "uProj", projection);
  shader_update_vec4(program, "uColor", color);
  shader_update_texture(program, "uTexture", texture);

  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
  glBindVertexArray(0);
}
