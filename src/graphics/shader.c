#include <graphics/shader.h>
#include <util/io.h>

static GLuint shader_compile(GLenum type, const char *src)
{
  assert(src);

  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  GLint ok = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
  assert(ok);

  return shader;
}

static GLuint shader_link(GLuint vs, GLuint fs)
{
  assert(vs && fs);

  GLuint program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  GLint ok = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &ok);
  assert(ok);

  return program;
}

void shader_create(GLuint *program, const char *vs_path, const char *fs_path)
{
  assert(program && vs_path && fs_path);

  file_t vs_file = io_file_read(vs_path);
  file_t fs_file = io_file_read(fs_path);
  assert(vs_file.valid && fs_file.valid);

  const char *vs_src = (const char *)vs_file.data;
  const char *fs_src = (const char *)fs_file.data;
  GLuint vs = shader_compile(GL_VERTEX_SHADER, vs_src);
  GLuint fs = shader_compile(GL_FRAGMENT_SHADER, fs_src);
  assert(vs && fs);

  *program = shader_link(vs, fs);
  assert(program);

  glDeleteShader(vs);
  glDeleteShader(fs);
  free(vs_file.data);
  free(fs_file.data);
}

void shader_use(GLuint program)
{
  assert(program);
  glUseProgram(program);
}

void shader_delete(GLuint program)
{
  assert(program);
  glDeleteProgram(program);
}

void shader_update_mat4x4(GLuint program, const char *name, mat4x4 matrix)
{
  assert(program && name);
  GLint location = glGetUniformLocation(program, name);
  glUniformMatrix4fv(location, 1, GL_FALSE, &matrix[0][0]);
}

void shader_update_vec4(GLuint program, const char *name, vec4 vector)
{
  assert(program && name);
  GLint location = glGetUniformLocation(program, name);
  glUniform4fv(location, 1, &vector[0]);
}

void shader_update_vec2(GLuint program, const char *name, vec2 vector)
{
  assert(program && name);
  GLint location = glGetUniformLocation(program, name);
  glUniform2fv(location, 1, &vector[0]);
}

void shader_update_texture(GLuint program, const char *name, GLuint texture)
{
  assert(program && name);
  GLint location = glGetUniformLocation(program, name);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(location, 0);
}
