#include <glad/glad.h>
#include <engine/shader.h>
#include <engine/util.h>
#include <engine/io.h>

#define SHADER_SOURCE(file) \
  (const char *const *)&(file.data)

unsigned shader_new(const char *vert_path, const char *frag_path) {
  file_t vert_file = io_file_read(vert_path);
  file_t frag_file = io_file_read(frag_path);
  if (!(vert_file.valid && frag_file.valid))
    ERROR_EXIT(1, "failed reading shader files\n");

  unsigned vert_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vert_shader, 1, SHADER_SOURCE(vert_file), NULL);
  glCompileShader(vert_shader);

  unsigned frag_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(frag_shader, 1, SHADER_SOURCE(frag_file), NULL);
  glCompileShader(frag_shader);

  unsigned program = glCreateProgram();
  glAttachShader(program, vert_shader);
  glAttachShader(program, frag_shader);
  glLinkProgram(program);

  glDeleteShader(vert_shader);
  glDeleteShader(frag_shader);

  return program;
}
