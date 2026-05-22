#include "shaders.h"

char* getFileContents(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    
    if (file != NULL) {
        fseek(file, 0, SEEK_END);
        long size = ftell(file);
        rewind(file);

        char* buffer = (char*)malloc(size + 1);

        fread(buffer, 1, size, file);
        buffer[size] = '\0';

        fclose(file);
        return buffer;
    }

    return NULL;
}

Shaders* createShaders(const char* vertexFile, const char* fragmentFile) {
    Shaders* shader = malloc(sizeof(Shaders));

    const char* vertexShaderSource = getFileContents(vertexFile);
    const char* fragmentShaderSource = getFileContents(fragmentFile);

    if (!vertexShaderSource || !fragmentShaderSource) {
        printf("ERROR: Failed to load shader files.\n");
        exit(1);
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    shader->ID = glCreateProgram();

    glAttachShader(shader->ID, vertexShader);
    glAttachShader(shader->ID, fragmentShader);
    glLinkProgram(shader->ID);
    
    // free(vertexShaderSource);
    // free(fragmentShaderSource);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shader;
}

void ActivateShaders(Shaders* shader) {
    glUseProgram(shader->ID);
}

void DeleteShaders(Shaders* shader) {
    glDeleteProgram(shader->ID);
}