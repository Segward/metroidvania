#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <linmath.h>

GLuint shader_create(const char *vs_path, const char *fs_path);
void shader_delete(GLuint program);
void shader_update_mat4x4(GLuint program, const char *name, mat4x4 matrix);
void shader_update_vec4(GLuint program, const char *name, vec4 vector);
void shader_update_texture(GLuint program, const char *name, GLuint texture);


#endif
