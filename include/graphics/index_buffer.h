#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <pch.h>

void index_buffer_generate(GLuint *ebo);
void index_buffer(GLuint ebo, GLuint *data, size_t size);
void index_buffer_delete(GLuint *ebo);

#endif
