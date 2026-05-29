#include "ebo.h"

EBO* createEBO(GLuint* indices, size_t size) {
    EBO* ebo = malloc(sizeof(EBO));
    glGenBuffers(1, &ebo->ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    return ebo;
}

void BindEBO(EBO* ebo) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo->ID);
}

void UnbindEBO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DeleteEBO(EBO* ebo) {
    glDeleteBuffers(1, &ebo->ID);
}