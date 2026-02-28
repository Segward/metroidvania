#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <glad/glad.h>
#include <stddef.h>

void index_buffer(GLuint ebo, GLuint *data, size_t size);
void index_buffer_delete(GLuint *ebo);

#endif
