#include <engine/gfx/shader.h>
#include <engine/io.h>

#include <stdio.h>
#include <stdlib.h>

static GLuint shader_compile(GLenum type, const char *src) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &src, NULL);
  glCompileShader(shader);

  GLint ok = 0;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
  if (!ok) {
    glDeleteShader(shader);
    return 0;
  }

  return shader;
}

static GLuint shader_link(GLuint vs, GLuint fs) {
  GLuint program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  GLint ok = 0;
  glGetProgramiv(program, GL_LINK_STATUS, &ok);
  if(!ok) {
    glDeleteProgram(program);
    return 0;
  }

  return program;
}

GLuint shader_create(const char *vs_path, const char *fs_path) {
  char *vs_src;
  io_file_read(vs_path, &vs_src);
  if (vs_src == NULL) {
    fprintf(stderr, "failed to read file: %s\n", vs_path);
    return 0;
  }

  char *fs_src;
  io_file_read(fs_path, &fs_src);
  if (fs_src == NULL) {
    fprintf(stderr, "failed to read file: %s\n", fs_path);
    free(vs_src);
    return 0;
  }

  GLuint vs = shader_compile(GL_VERTEX_SHADER, (const char *)vs_src);
  GLuint fs = shader_compile(GL_FRAGMENT_SHADER, (const char *)fs_src);
  if (!(vs && fs)) {
    fprintf(stderr, "failed to compile shader\n");
    free(vs_src);
    free(fs_src);
    return 0;
  }

  GLuint program = shader_link(vs, fs);
  if (!program)
    fprintf(stderr, "failed to link shader\n");

  glDeleteShader(vs);
  glDeleteShader(fs);
  free(vs_src);
  free(fs_src);

  return program;
}
