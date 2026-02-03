#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <stdint.h>

#define MESH_BUFFER(buffer, target, data, usage) \
  do { \
    glBindBuffer((target), (buffer)); \
    glBufferData((target), sizeof(data), (data), (usage)); \
  } while (0)

#define MESH_ATTRIB(index, count, type, normalized, stride, offset) \
  do { \
    glEnableVertexAttribArray((index)); \
    glVertexAttribPointer((index), (count), (type), (normalized), \
                          (const GLsizei)(stride), (const void *)(uintptr_t)(offset)); \
  } while (0)

#endif
