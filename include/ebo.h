#ifndef EBO_H
#define EBO_H

#include <stdlib.h>
#include "glad/glad.h"
#include "vbo.h"

typedef struct {
    GLuint ID;
} EBO;

EBO* createEBO(GLuint* indices, size_t size);

void BindEBO(EBO* ebo);
void UnbindEBO();
void DeleteEBO(EBO* ebo);

#endif