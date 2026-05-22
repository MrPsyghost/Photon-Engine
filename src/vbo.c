#include "vbo.h"

VBO* createVBO(GLfloat* vertices, GLsizeiptr size) {
    VBO* vbo_ = malloc(sizeof(VBO));
    glGenBuffers(1, &vbo_->ID);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_->ID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
    return vbo_;
}

void BindVBO(VBO* vbo_) {
    glBindBuffer(GL_ARRAY_BUFFER, vbo_->ID);
}

void UnbindVBO() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void DeleteVBO(VBO* vbo_) {
    glDeleteBuffers(1, &vbo_->ID);
}