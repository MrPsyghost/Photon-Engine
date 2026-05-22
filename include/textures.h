#ifndef TEXTURES_H
#define TEXTURES_H

#include <stdlib.h>
#include "glad/glad.h"
#include "stb/stb_image.h"
#include "shaders.h"


typedef struct {
    GLuint ID;
    GLenum Type;
} Texture;

Texture* createTexture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType);

void texUnit(Shaders* shaderPrgm, const char* uniform, GLuint unit);
void BindTexture(Texture* tex);
void UnbindTexture(Texture* tex);
void DeleteTexture(Texture* tex);

#endif