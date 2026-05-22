#ifndef CAMERA_H
#define CAMERA_H

#include <stdlib.h>
#include "glad/glad.h"
#include "shaders.h"
#include "cglm/cglm.h"
#include "cglm/mat4.h"

typedef struct {
    vec3 Position;
    vec3 Orientation;
    vec3 Up;
    mat4 camMatrix;

    int width;
    int height;

    double speed;
    float sensitivity;

    bool firstClick;
} Camera;

Camera* createCamera(int width, int height, vec3 Position);

void Matrix(Camera* cam, Shaders* shaderPrgm, const char* uniform);
void updateMatrix(Camera* cam, float FOVdeg, float nearPlane, float farPlane);
void Inputs(Camera* cam, GLFWwindow* window);

#endif