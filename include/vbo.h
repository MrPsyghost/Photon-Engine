#ifndef VBO_H
#define VBO_H

#include <stdlib.h>
#include "glad/glad.h"
#include "cglm/cglm.h"

typedef struct {
    vec3 position;
    vec3 normal;
    vec3 color;
    vec2 texUV;
} Vertex;

typedef struct {
    GLuint ID;
} VBO;

VBO* createVBO(Vertex* vertices, size_t size);

void BindVBO(VBO* vbo);
void UnbindVBO();
void DeleteVBO(VBO* vbo);

#endif