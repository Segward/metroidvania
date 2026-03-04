#include <graphics/quad.h>
#include <util/global.h>

#include <graphics/shader.h>
#include <graphics/vertex_array.h>
#include <graphics/vertex_buffer.h>
#include <graphics/index_buffer.h>

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
  shader_create(&program, "assets/shaders/quad.vert", "assets/shaders/quad.frag");

  vertex_array_generate(&vao);
  vertex_buffer_generate(&vbo);
  index_buffer_generate(&ebo);

  vertex_array_bind(vao);

  vertex_buffer(vbo, vertices, sizeof(vertices));
  index_buffer(ebo, indices, sizeof(indices));

  vertex_array_attribute(0, 2, 4, 0);
  vertex_array_attribute(1, 2, 4, 2);
}

void quad_delete(void)
{
  index_buffer_delete(&ebo);
  vertex_buffer_delete(&vbo);
  vertex_array_delete(&vao);
  shader_delete(program);
}

void quad_draw(vec2 position, vec2 size, vec4 color, GLuint texture, vec4 uv)
{
  shader_use(program);
  shader_update_vec2(program, "uPos", position);
  shader_update_vec2(program, "uSize", size);
  shader_update_mat4x4(program, "uProj", global.projection);
  shader_update_mat4x4(program, "uView", global.view);
  shader_update_vec4(program, "uUV", uv);
  shader_update_vec4(program, "uColor", color);
  shader_update_texture(program, "uTexture", texture);

  vertex_array_bind(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
}
