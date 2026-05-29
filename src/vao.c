#include "vao.h"

VAO* createVAO() {
    VAO* vao = malloc(sizeof(VAO));
    glGenVertexArrays(1, &vao->ID);
    return vao;
}

void LinkAttrib(VBO* vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, void* offset) {
    BindVBO(vbo);

    glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
    glEnableVertexAttribArray(layout);

    UnbindVBO();
}

void BindVAO(VAO* vao) {
    glBindVertexArray(vao->ID);
}

void UnbindVAO() {
    glBindVertexArray(0);
}

void DeleteVAO(VAO* vao) {
    glDeleteVertexArrays(1, &vao->ID);
}