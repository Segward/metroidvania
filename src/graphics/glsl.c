#include <graphics/glsl.h>
#include <util/io.h>

static GLuint glsl_compile(GLenum type, const char *src)
{
  GLuint program = glCreateShader(type);
  glShaderSource(program, 1, &src, NULL);
  glCompileShader(program);

  GLint ok = 0;
  glGetShaderiv(program, GL_COMPILE_STATUS, &ok);
  assert(ok);

  return program;
}

static GLuint glsl_link(GLuint vert, GLuint frag)
{
  GLuint program = glCreateProgram();
  glAttachShader(program, vert);
  glAttachShader(program, frag);
  glLinkProgram(program);

  GLint ok = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &ok);
  assert(ok);

  return program;
}

void glsl_create(GLuint *program, const char *vert_path, const char *frag_path)
{
  file_t vert_file = io_file_read(vert_path);
  file_t frag_file = io_file_read(frag_path);
  assert(vert_file.valid && frag_file.valid);

  GLuint vert = glsl_compile(GL_VERTEX_SHADER, (const char *)vert_file.data);
  GLuint frag = glsl_compile(GL_FRAGMENT_SHADER, (const char *)frag_file.data);
  assert(vert && frag);

  GLuint _program = glsl_link(vert, frag);
  assert(_program);

  glDeleteShader(vert);
  glDeleteShader(frag);
  free(vert_file.data);
  free(frag_file.data);

  *program = _program;
}
