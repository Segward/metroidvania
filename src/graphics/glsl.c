#include <graphics/glsl.h>
#include <util/io.h>

static GLuint glsl_compile(GLenum type, const char *src)
{
  GLuint sh = glCreateShader(type);
  glShaderSource(sh, 1, &src, NULL);
  glCompileShader(sh);

  GLint ok = 0;
  glGetShaderiv(sh, GL_COMPILE_STATUS, &ok);
  if (!ok) {
    GLint len = 0;
    glGetShaderiv(sh, GL_INFO_LOG_LENGTH, &len);

    char *log = (char*)malloc((size_t)len + 1);
    glGetShaderInfoLog(sh, len, NULL, log);
    log[len] = 0;

    fprintf(stderr, "\n[GLSL COMPILE ERROR] %s\n%s\n",
            (type == GL_VERTEX_SHADER ? "VERTEX" :
             type == GL_FRAGMENT_SHADER ? "FRAGMENT" : "OTHER"),
            log);

    free(log);
    glDeleteShader(sh);
    assert(0);
  }

  return sh;
}

static GLuint glsl_link(GLuint vert, GLuint frag)
{
  GLuint prog = glCreateProgram();
  glAttachShader(prog, vert);
  glAttachShader(prog, frag);
  glLinkProgram(prog);

  GLint ok = 0;
  glGetProgramiv(prog, GL_LINK_STATUS, &ok);
  if (!ok) {
    GLint len = 0;
    glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);

    char *log = (char*)malloc((size_t)len + 1);
    glGetProgramInfoLog(prog, len, NULL, log);
    log[len] = 0;

    fprintf(stderr, "\n[GLSL LINK ERROR]\n%s\n", log);

    free(log);
    glDeleteProgram(prog);
    assert(0);
  }

  return prog;
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
