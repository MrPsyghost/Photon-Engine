#include "vao.h"

VAO* createVAO() {
    VAO* vao_ = malloc(sizeof(VAO));
    glGenVertexArrays(1, &vao_->ID);
    return vao_;
}

void LinkAttrib(VBO* vbo_, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
    BindVBO(vbo_);

    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);

    UnbindVBO();
}

void BindVAO(VAO* vao_) {
    glBindVertexArray(vao_->ID);
}

void UnbindVAO() {
    glBindVertexArray(0);
}

void DeleteVAO(VAO* vao_) {
    glDeleteVertexArrays(1, &vao_->ID);
}