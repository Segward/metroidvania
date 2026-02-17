#include <engine/gfx/mesh.h>
#include <stdint.h>

static void mesh_bind_buffer(GLuint buffer, GLenum target, GLsizeiptr size, 
                             const void *data, GLenum usage) {
  glBindBuffer(target, buffer);
  glBufferData(target, size, data, usage);
}

static void mesh_enable_attrib(GLuint index, GLint size, GLenum type, GLboolean normalized, 
                              GLsizei stride, const void *offset) {
  glEnableVertexAttribArray(index);
  glVertexAttribPointer(index, size, type, normalized, stride, offset);
}

static GLfloat quad_vertices[] = {
   0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
   0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
  -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
  -0.5f,  0.5f, 0.0f, 1.0f, 0.0f
};

static GLuint quad_indices[] = {
  0, 1, 3,
  1, 2, 3
};

void mesh_init_quad(GLuint *vao, GLuint *vbo, GLuint *ebo) {
  glGenVertexArrays(1, vao);
  glGenBuffers(1, vbo);
  glGenBuffers(1, ebo);

  glBindVertexArray(*vao);

  mesh_bind_buffer(*vbo, GL_ARRAY_BUFFER, (GLsizeiptr)sizeof(quad_vertices), 
                   quad_vertices, GL_STATIC_DRAW);
  mesh_bind_buffer(*ebo, GL_ELEMENT_ARRAY_BUFFER, (GLsizeiptr)sizeof(quad_indices), 
                   quad_indices, GL_STATIC_DRAW);

  GLsizei stride = (GLsizei)(5 * sizeof(GLfloat));
  const void *offset_1 = (const void *)0;
  const void *offset_2 = (const void *)(uintptr_t)(3 * sizeof(GLfloat));

  mesh_enable_attrib(0, 3, GL_FLOAT, GL_FALSE, stride, offset_1);
  mesh_enable_attrib(1, 2, GL_FLOAT, GL_FALSE, stride, offset_2);

  glBindVertexArray(0);
}
