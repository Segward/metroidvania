#include <graphics/glsl.h>
#include <util/io.h>

static GLuint glsl_compile(GLenum type, const char *src)
{
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  GLint ok = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
  assert(ok);
 
  return shader;
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
  char *vert_src = io_file_read(vert_path);
  char *frag_src = io_file_read(frag_path);
  assert(vert_src && frag_src);

  GLuint vert = glsl_compile(GL_VERTEX_SHADER, (const char *)vert_src);
  GLuint frag = glsl_compile(GL_FRAGMENT_SHADER, (const char *)frag_src);
  assert(vert && frag);

  *program = glsl_link(vert, frag);
  assert(*program);

  glDeleteShader(vert);
  glDeleteShader(frag);
  free(vert_src);
  free(frag_src);
}
