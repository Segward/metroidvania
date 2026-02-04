#include <glad/glad.h>
#include <engine/render_internal.h>
#include <engine/io.h>
#include <engine/util.h>

static u32 render_shader_create(const char *vert_path, const char *frag_path) {
  char *vert_source;
  io_file_read(vert_path, &vert_source);
  if (vert_source == NULL)
    ERROR_EXIT("failed to read vertex source");

  char *frag_source;
  io_file_read(frag_path, &frag_source);
  if (frag_source == NULL)
    ERROR_EXIT("failed to read vertex source");

  u32 vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, (const char *const *)&vert_source, NULL);
  glCompileShader(vert_shader);

  u32 frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, (const char *const *)&frag_source, NULL);
  glCompileShader(frag_shader);

  u32 program = glCreateProgram();
  glAttachShader(program, vert_shader);
  glAttachShader(program, frag_shader);
  glLinkProgram(program);

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

  return program;
}

#define MESH_BUFFER(buffer, target, data, usage) \
  do { \
    glBindBuffer((target), (buffer)); \
    glBufferData((target), sizeof(data), (data), (usage)); \
  } while (0)

#define MESH_ATTRIB(index, count, type, normalized, stride, offset) \
  do { \
    glEnableVertexAttribArray((index)); \
    glVertexAttribPointer((index), (count), (type), (normalized), \
                          (const GLsizei)(stride), (const void *)(offset)); \
  } while (0)

u32 quad_vao;
u32 quad_vbo;
u32 quad_ebo;
u32 quad_shader;

static f32 quad_vertices[] = {
   0.5f,  0.5f, 0.0f, 0.0f, 0.0f,
   0.5f, -0.5f, 0.0f, 0.0f, 1.0f,
  -0.5f, -0.5f, 0.0f, 1.0f, 1.0f,
  -0.5f,  0.5f, 0.0f, 1.0f, 0.0f
};

static u32 quad_indices[] = {
  0, 1, 3,
  1, 2, 3
};

void render_quad_init(void) {
  quad_shader = render_shader_create("assets/quad.vert", "assets/quad.frag");

  glGenVertexArrays(1, &quad_vao);
  glGenBuffers(1, &quad_vbo); 
  glGenBuffers(1, &quad_ebo);

  glBindVertexArray(quad_vao);

  MESH_BUFFER(quad_vbo, GL_ARRAY_BUFFER, quad_vertices, GL_STATIC_DRAW);
  MESH_BUFFER(quad_ebo, GL_ELEMENT_ARRAY_BUFFER, quad_indices, GL_STATIC_DRAW);

  MESH_ATTRIB(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0 * sizeof(float));
  MESH_ATTRIB(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 3 * sizeof(float));

  glBindVertexArray(0);
}
