#include "textures.h"

Texture* createTexture(const char* image, GLenum texType, GLenum slot, GLenum format, GLenum pixelType) {
    Texture* tex = malloc(sizeof(Texture));

    tex->Type = texType;

    int widthImg, heightImg, numColh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColh, 0);

    glGenTextures(1, &tex->ID);
    glActiveTexture(slot);
    glBindTexture(texType, tex->ID);

    glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

    float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(texType, GL_TEXTURE_BORDER_COLOR, flatColor);

    glTexImage2D(texType, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(texType);

    stbi_image_free(bytes);
    glBindTexture(texType, 0);
    
    return tex;
}

void texUnit(Shaders* shaderPrgm, const char* uniform, GLuint unit) {
    GLuint texUni = glGetUniformLocation(shaderPrgm->ID, uniform);
    ActivateShaders(shaderPrgm);
    glUniform1i(texUni, unit);
}

void BindTexture(Texture* tex) {
    glBindTexture(tex->Type, tex->ID);
}

void UnbindTexture(Texture* tex) {
    glBindTexture(tex->Type, 0);
}

void DeleteTexture(Texture* tex) {
    glDeleteTextures(1, &tex->ID);
}