#include "textures.h"

Texture* createTexture(const char* image, const char* texType, GLuint slot, GLenum pixelType) {
    Texture* tex = malloc(sizeof(Texture));

    tex->Type = texType;

    int widthImg, heightImg, numColh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColh, 0);

    GLenum format;

    if (numColh == 4)
        format = GL_RGBA;
    else if (numColh == 3)
        format = GL_RGB;
    else if (numColh == 1)
        format = GL_RED;
    else {
        printf("Unsupported channel count: %d\n", numColh);
        return NULL;
    }

    if (!bytes) {
        printf("Failed to load texture: %s\n", image);
    } else {
        printf("Loaded %s (%dx%d, channels=%d)\n", image, widthImg, heightImg, numColh);
    }

    glGenTextures(1, &tex->ID);
    glActiveTexture(GL_TEXTURE0 + slot);
    tex->unit = slot;
    glBindTexture(GL_TEXTURE_2D, tex->ID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    float flatColor[] = {1.0f, 1.0f, 1.0f, 1.0f};
    glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, flatColor);

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    glTexImage2D(GL_TEXTURE_2D, 0, format, widthImg, heightImg, 0, format, pixelType, bytes);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D, 0);

    return tex;
}

void texUnit(Shaders* shaderPrgm, const char* uniform, GLuint unit) {
    GLuint texUni = glGetUniformLocation(shaderPrgm->ID, uniform);
    ActivateShaders(shaderPrgm);
    glUniform1i(texUni, unit);
}

void BindTexture(Texture* tex) {
    glActiveTexture(GL_TEXTURE0 + tex->unit);
    glBindTexture(GL_TEXTURE_2D, tex->ID);
}

void UnbindTexture(Texture* tex) {
    glBindTexture(GL_TEXTURE_2D, 0);
}

void DeleteTexture(Texture* tex) {
    glDeleteTextures(1, &tex->ID);
}