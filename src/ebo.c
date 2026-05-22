#include "ebo.h"

EBO* createEBO(GLuint* indices, GLsizeiptr size) {
    EBO* ebo_ = malloc(sizeof(EBO));
    glGenBuffers(1, &ebo_->ID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_->ID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
    return ebo_;
}

void BindEBO(EBO* ebo_) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo_->ID);
}

void UnbindEBO() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void DeleteEBO(EBO* ebo_) {
    glDeleteBuffers(1, &ebo_->ID);
}