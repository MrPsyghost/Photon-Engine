#ifndef VBO_H
#define VBO_H

#include <stdlib.h>
#include "glad/glad.h"

typedef struct {
    GLuint ID;
} VBO;

VBO* createVBO(GLfloat* vertices, GLsizeiptr size);

void BindVBO(VBO* vbo_);
void UnbindVBO();
void DeleteVBO(VBO* vbo_);

#endif