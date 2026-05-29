#include "mesh.h"

Mesh* createMesh(Vertex* vertices, size_t vertexCount, GLuint* indices, size_t indexCount, Texture** textures, size_t textureCount) {
    Mesh* mesh = malloc(sizeof(Mesh));
    mesh->vao = createVAO();
    mesh->vertices = vertices;
    mesh->vertexCount = vertexCount;
    mesh->indices = indices;
    mesh->indexCount = indexCount;
    mesh->textures = textures;
    mesh->textureCount = textureCount;

    BindVAO(mesh->vao);
    VBO* vbo = createVBO(vertices, vertexCount * sizeof(Vertex));
    EBO* ebo = createEBO(indices, indexCount * sizeof(GLuint));

    LinkAttrib(vbo, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
    LinkAttrib(vbo, 1, 3, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));
    LinkAttrib(vbo, 2, 3, GL_FLOAT, sizeof(Vertex), (void*)(6 * sizeof(float)));
    LinkAttrib(vbo, 3, 2, GL_FLOAT, sizeof(Vertex), (void*)(9 * sizeof(float)));
    
    UnbindVAO();
    UnbindVBO();
    UnbindEBO();

    return mesh;
}

void DrawMesh(Mesh* mesh, Shaders* shaders, Camera* cam) {
    ActivateShaders(shaders);

    BindVAO(mesh->vao);

    uint16_t numDiffuse = 0;
    uint16_t numSpecular = 0;

    char dest[101];

    for (uint32_t i = 0; i < mesh->textureCount; i++) {
        const char* type = mesh->textures[i]->Type;
        uint32_t number;

        if (strcmp(type, "diffuse") == 0) {
            number = numDiffuse++;
        } else if (strcmp(type, "specular") == 0) {
            number = numSpecular++;
        }

        sprintf(dest, "%s%d", type, number);
        texUnit(shaders, dest, i);
        BindTexture(mesh->textures[i]);
    }

    glUniform3f(glGetUniformLocation(shaders->ID, "camPos"), cam->Position[0], cam->Position[1], cam->Position[2]);
    Matrix(cam, shaders, "camMatrix");

    glDrawElements(GL_TRIANGLES, mesh->indexCount, GL_UNSIGNED_INT, 0);
}