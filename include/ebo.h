#ifndef EBO_H
#define EBO_H

#include <stdlib.h>
#include "glad/glad.h"

typedef struct {
    GLuint ID;
} EBO;

EBO* createEBO(GLuint* indices, GLsizeiptr size);

void BindEBO(EBO* ebo_);
void UnbindEBO();
void DeleteEBO(EBO* ebo_);

#endif