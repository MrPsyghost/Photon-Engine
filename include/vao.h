#ifndef VAO_H
#define VAO_H

#include <stdlib.h>
#include "glad/glad.h"
#include "vbo.h"

typedef struct {
    GLuint ID;
} VAO;

VAO* createVAO();

void LinkAttrib(VBO* vbo_, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset);
void BindVAO(VAO* vao_);
void UnbindVAO();
void DeleteVAO(VAO* vao_);

#endif