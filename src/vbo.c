#include "vbo.h"

VBO* createVBO(Vertex* vertices, size_t size) {
    VBO* vbo = malloc(sizeof(VBO));
    glGenBuffers(1, &vbo->ID);
    glBindBuffer(GL_ARRAY_BUFFER, vbo->ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    return vbo;
}

void BindVBO(VBO* vbo) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo->ID);
}

void UnbindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DeleteVBO(VBO* vbo) {
    glDeleteBuffers(1, &vbo->ID);
}