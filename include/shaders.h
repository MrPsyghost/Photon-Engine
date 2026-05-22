#ifndef SHADERS_H
#define SHADERS_H

#define SHADERS_LIMIT 10000

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

char* getFileContents(const char* fileName);

typedef struct {
    GLuint ID;
} Shaders;

Shaders* createShaders(const char* vertexFile, const char* fragmentFile);

void ActivateShaders(Shaders* shader);
void DeleteShaders(Shaders* shader);

void CheckShaderCompileError(GLuint shader, const char* type);
void CheckProgramLinkError(GLuint program);

#endif