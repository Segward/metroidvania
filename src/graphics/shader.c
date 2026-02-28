#include <graphics/shader.h>
#include <io.h>

static GLuint shader_compile(GLenum type, const char *src)
{
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  GLint ok = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
  if (!ok) 
  {
    glDeleteShader(shader);
    return 0;
  }

  return shader;
}

static GLuint shader_link(GLuint vs, GLuint fs)
{
  GLuint program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  GLint ok = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &ok);
  if(!ok) 
  {
    glDeleteProgram(program);
    return 0;
  }

  return program;
}

GLuint shader_create(const char *vs_path, const char *fs_path)
{
  file_t vs_file = io_file_read(vs_path);
  if (!vs_file.valid)
    return 0;

  file_t fs_file = io_file_read(fs_path);
  if (!fs_file.valid)
  {
    free(vs_file.data);
    return 0;
  }

  const char *vs_src = (const char *)vs_file.data;
  const char *fs_src = (const char *)fs_file.data;
  GLuint vs = shader_compile(GL_VERTEX_SHADER, vs_src);
  GLuint fs = shader_compile(GL_FRAGMENT_SHADER, fs_src);
  if (!(vs && fs))
  {
    free(vs_file.data);
    free(fs_file.data);
    return 0;
  }

  GLuint program = shader_link(vs, fs);

  glDeleteShader(vs);
  glDeleteShader(fs);
  free(vs_file.data);
  free(fs_file.data);

  if (!program)
    return 0;

  return program;
}

void shader_use(GLuint program)
{
  if (!program)
    return;

  glUseProgram(program);
}

void shader_delete(GLuint program)
{
  if (!program)
    return;

  glDeleteProgram(program);
}

void shader_update_mat4x4(GLuint program, const char *name, mat4x4 matrix)
{
  GLint location = glGetUniformLocation(program, name);
  const GLfloat *value = (const GLfloat *)&matrix[0][0];
  glUniformMatrix4fv(location, 1, GL_FALSE, value);
}

void shader_update_vec4(GLuint program, const char *name, vec4 vector)
{
  GLint location = glGetUniformLocation(program, name);
  const GLfloat *value = (const GLfloat *)&vector[0];
  glUniform4fv(location, 1, value);
}

void shader_update_texture(GLuint program, const char *name, GLuint texture)
{
  GLint location = glGetUniformLocation(program, name);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glUniform1i(location, 0);
}
