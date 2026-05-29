#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdlib.h>
#include "glad/glad.h"
#include "stb/stb_image.h"
#include "shaders.h"


typedef struct {
    GLuint ID;
    const char* Type;
    GLuint unit;
} Texture;

Texture* createTexture(const char* image, const char* texType, GLuint sl, GLenum pixelType);

void texUnit(Shaders* shaderPrgm, const char* uniform, GLuint unit);
void BindTexture(Texture* tex);
void UnbindTexture(Texture* tex);
void DeleteTexture(Texture* tex);

#endif