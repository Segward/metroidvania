#include <glad/glad.h>
#include <engine/quad.h>
#include <engine/shader.h>
#include <engine/mesh.h>

static unsigned vao;
static unsigned vbo;
static unsigned ebo;
static unsigned program;

static float quad_vertices[] = {
   0.5,  0.5, 0, 0, 0,
   0.5, -0.5, 0, 0, 1,
  -0.5, -0.5, 0, 1, 1,
  -0.5,  0.5, 0, 1, 0
};

static unsigned quad_indices[] = {
  0, 1, 3,
  1, 2, 3
};

void quad_init(void) {
  program = shader_new("assets/quad.vert", "assets/quad.frag");

  glGenVertexArrays(1, &vao);
  glGenBuffers(1, &vbo); 
  glGenBuffers(1, &(ebo));

  glBindVertexArray(vao);

  MESH_BUFFER(vbo, GL_ARRAY_BUFFER, quad_vertices, GL_STATIC_DRAW);
  MESH_BUFFER(ebo, GL_ELEMENT_ARRAY_BUFFER, quad_indices, GL_STATIC_DRAW);

  MESH_ATTRIB(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0 * sizeof(float));
  MESH_ATTRIB(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 3 * sizeof(float));

  glBindVertexArray(0);
}

void quad_draw(vec3 pos, vec2 scale, vec4 color) {;
  glUseProgram(program);

  glUniform3fv(glGetUniformLocation(program, "uPos"), 1, pos);
  glUniform2fv(glGetUniformLocation(program, "uScale"), 1, scale);
  glUniform4fv(glGetUniformLocation(program, "uColor"), 1, color);

  glBindVertexArray(vao);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (const void*)0);
  glBindVertexArray(0);
}
