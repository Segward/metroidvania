#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>

GLuint shader_new(const char *vertex_path, 
                  const char *fragment_path);

#endif
