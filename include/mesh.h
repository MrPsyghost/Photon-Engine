#ifndef MESH_H
#define MESH_H

#include <stdio.h>
#include <string.h>
#include "vao.h"
#include "ebo.h"
#include "camera.h"
#include "textures.h"

typedef struct {
    Vertex* vertices;
    size_t vertexCount;

    GLuint* indices;
    size_t indexCount;
    
    Texture** textures;
    size_t textureCount;

    VAO* vao;
} Mesh;

Mesh* createMesh(Vertex* vertices, size_t vertexCount, GLuint* indices, size_t indexCount, Texture** textures, size_t textureCount);

void DrawMesh(Mesh* mesh, Shaders* shader, Camera* cam);


#endif