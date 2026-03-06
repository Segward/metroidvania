#include <engine/graphics/shader.h>
#include <engine/util/io.h>

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

static GLuint shader_link(GLuint vert, GLuint frag)
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

void shader_make(GLuint *program, const char *vert_path, const char *frag_path)
{
  assert(program && vert_path && frag_path);

  char *vert_src;
  file_read(vert_path, &vert_src, NULL);

  char *frag_src;
  file_read(frag_path, &frag_src, NULL);

  assert(vert_src && frag_src);

  GLuint vert = shader_compile(GL_VERTEX_SHADER, (const char *)vert_src);
  GLuint frag = shader_compile(GL_FRAGMENT_SHADER, (const char *)frag_src);
  assert(vert && frag);

  GLuint linked = shader_link(vert, frag);
  glDeleteShader(vert);
  glDeleteShader(frag);
  free(vert_src);
  free(frag_src);

  *program = linked;
}

