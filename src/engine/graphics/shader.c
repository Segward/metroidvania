#include <engine/graphics/shader.h>
#include <engine/util/io.h>

static GLuint shader_compile(GLenum type, const char *src)
{
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  GLint ok = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
  if (!ok) {
    GLint log_len = 0;
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0) {
      char *log = malloc(log_len);
      glGetShaderInfoLog(shader, log_len, NULL, log);
      fprintf(stderr, "Shader compile error:\n%s\n", log);
      free(log);
    }
  }
 
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
  if (!ok) {
    GLint log_len = 0;
    glGetProgramiv(program, GL_INFO_LOG_LENGTH, &log_len);
    if (log_len > 0) {
      char *log = malloc(log_len);
      glGetProgramInfoLog(program, log_len, NULL, log);
      fprintf(stderr, "Program link error:\n%s\n", log);
      free(log);
    }
  }

  return program;
}

void shader_make(GLuint *program, const char *vert_path, const char *frag_path)
{
  char *vert_src;
  file_read(vert_path, &vert_src, NULL);
  if (!vert_src) {
    fprintf(stderr, "Failed to read vertex shader file\n");
    exit(EXIT_FAILURE);
  }

  char *frag_src;
  file_read(frag_path, &frag_src, NULL);
  if (!frag_src) {
    fprintf(stderr, "Failed to read fragment shader file\n");
    free(vert_src);
    exit(EXIT_FAILURE);
  }

  GLuint vert = shader_compile(GL_VERTEX_SHADER, (const char *)vert_src);
  if (!vert) {
    fprintf(stderr, "Failed to compile vertex shader\n");
    free(vert_src);
    free(frag_src);
    exit(EXIT_FAILURE);
  }

  GLuint frag = shader_compile(GL_FRAGMENT_SHADER, (const char *)frag_src);
  if (!vert) {
    fprintf(stderr, "Failed to compile fragment shader\n");
    free(vert_src);
    free(frag_src);
    glDeleteShader(vert);
    exit(EXIT_FAILURE);
  }

  free(vert_src);
  free(frag_src);

  *program = shader_link(vert, frag);
  if (!(*program)) {
    fprintf(stderr, "Shader program linking failed\n");
  }

  glDeleteShader(vert);
  glDeleteShader(frag);
}

