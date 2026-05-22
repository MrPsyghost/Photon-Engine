#include "shaders.h"

char* getFileContents(const char* fileName) {
    FILE* file = fopen(fileName, "rb");

    if (file == NULL) {
        printf("ERROR: Could not open file: %s\n", fileName);
        return NULL;
    }
    
    fseek(file, 0, SEEK_END);
    long size = ftell(file);
    rewind(file);

    char* buffer = (char*)malloc(size + 1);
    if (buffer == NULL) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, size, file);
    fclose(file);

    buffer[size] = '\0';

    if (size >= 3 && 
        (unsigned char)buffer[0] == 0xEF && 
        (unsigned char)buffer[1] == 0xBB && 
        (unsigned char)buffer[2] == 0xBF) {
        memmove(buffer, buffer + 3, size - 2);
        printf("Removed BOM from: %s\n", fileName);
    }

    return buffer;
}

Shaders* createShaders(const char* vertexFile, const char* fragmentFile) {
    Shaders* shader = malloc(sizeof(Shaders));

    const char* vertexShaderSource = getFileContents(vertexFile);
    const char* fragmentShaderSource = getFileContents(fragmentFile);

    if (!vertexShaderSource || !fragmentShaderSource) {
        printf("ERROR: Failed to load shader files: %s or %s\n", vertexFile, fragmentFile);
        exit(1);
    }

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    CheckShaderCompileError(vertexShader, "VERTEX");

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    CheckShaderCompileError(fragmentShader, "FRAGMENT");

    shader->ID = glCreateProgram();

    glAttachShader(shader->ID, vertexShader);
    glAttachShader(shader->ID, fragmentShader);
    glLinkProgram(shader->ID);
    CheckProgramLinkError(shader->ID);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    
    free((void*)vertexShaderSource);
    free((void*)fragmentShaderSource);

    return shader;
}

void ActivateShaders(Shaders* shader) {
    glUseProgram(shader->ID);
}

void DeleteShaders(Shaders* shader) {
    glDeleteProgram(shader->ID);
}

void CheckShaderCompileError(GLuint shader, const char* type) {
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        printf("ERROR: %s Shader Compilation Failed:\n%s\n", type, infoLog);
    }
}

void CheckProgramLinkError(GLuint program) {
    GLint success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024];
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        printf("ERROR: Shader Program Linking Failed:\n%s\n", infoLog);
    }
}