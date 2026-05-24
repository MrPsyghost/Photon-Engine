#include <stdio.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "shaders.h"
#include "textures.h"
#include "vao.h"
#include "vbo.h"
#include "ebo.h"
#include "stb/stb_image.h"
#include "cglm/cglm.h"
#include "cglm/mat4.h"
#include "cglm/types.h"
#include "camera.h"

#define WIDTH  1000
#define HEIGHT 600

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLfloat vertices[] = {
        //     COORDINATES     /        COLORS          /    TexCoord   /        NORMALS        //
        -1.0f, 0.0f,  1.0f,      0.0f, 0.0f, 0.0f,        0.0f, 0.0f,     0.0f, 1.0f, 0.0f,
        -1.0f, 0.0f, -1.0f,      0.0f, 0.0f, 0.0f,        0.0f, 1.0f,     0.0f, 1.0f, 0.0f,
         1.0f, 0.0f, -1.0f,      0.0f, 0.0f, 0.0f,        1.0f, 1.0f,     0.0f, 1.0f, 0.0f,
         1.0f, 0.0f,  1.0f,      0.0f, 0.0f, 0.0f,        1.0f, 0.0f,     0.0f, 1.0f, 0.0f,
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLfloat lightVertices[] = {
        -0.1f, -0.1f,  0.1f,
        -0.1f, -0.1f, -0.1f,
         0.1f, -0.1f, -0.1f,
         0.1f, -0.1f,  0.1f,
        -0.1f,  0.1f,  0.1f,
        -0.1f,  0.1f, -0.1f,
         0.1f,  0.1f, -0.1f,
         0.1f,  0.1f,  0.1f,
    };

    GLuint lightIndices[] = {
        0, 1, 2,
        0, 2, 3,
        0, 4, 7,
        0, 7, 3,
        3, 7, 6,
        3, 6, 2,
        2, 6, 5,
        2, 5, 1,
        1, 5, 4,
        1, 4, 0,
        4, 5, 6,
        4, 6, 7,
    };

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Photon Engine Test", NULL, NULL);
    if (window == NULL) {
        printf("glfw failed to create a window!");
        glfwTerminate();
        return -1;
    }
    
    glfwMakeContextCurrent(window);

    gladLoadGL();

    glViewport(0, 0, WIDTH, HEIGHT);

    Shaders* shaderProgram = createShaders("shaders/default.vert", "shaders/default.frag");
    
    VAO* vao_ = createVAO();
    BindVAO(vao_);
    
    VBO* vbo_ = createVBO(vertices, sizeof(vertices));
    EBO* ebo_ = createEBO(indices, sizeof(indices));

    LinkAttrib(vbo_, 0, 3, GL_FLOAT, 11 * sizeof(float), (void*)0);
    LinkAttrib(vbo_, 1, 3, GL_FLOAT, 11 * sizeof(float), (void*)(3 * sizeof(float)));
    LinkAttrib(vbo_, 2, 2, GL_FLOAT, 11 * sizeof(float), (void*)(6 * sizeof(float)));
    LinkAttrib(vbo_, 3, 3, GL_FLOAT, 11 * sizeof(float), (void*)(8 * sizeof(float)));
    UnbindVAO();
    UnbindVBO();
    UnbindEBO();

    Shaders* lightShaders = createShaders("shaders/light.vert", "shaders/light.frag");

    VAO* lightVAO = createVAO();
    BindVAO(lightVAO);

    VBO* lightVBO = createVBO(lightVertices, sizeof(lightVertices));
    EBO* lightEBO = createEBO(lightIndices, sizeof(lightIndices));

    LinkAttrib(lightVBO, 0, 3, GL_FLOAT, 3 * sizeof(float), (void*)0);
    UnbindVAO();
    UnbindVBO();
    UnbindEBO();

    vec4 lightColor = {1.0f, 1.0f, 1.0f, 1.0f};
    
    vec3 lightPos = {0.5f, 0.5f, 0.5f};
    mat4 lightModel;
    glm_mat4_identity(lightModel);
    glm_translate(lightModel, lightPos);
    
    vec3 pyramidPos = {0.0f, 0.0f, 0.0f};
    mat4 pyramidModel;
    glm_mat4_identity(pyramidModel);
    glm_translate(pyramidModel, pyramidPos);

    Texture* planksTex = createTexture("textures/planks.png", GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE);
    texUnit(shaderProgram, "tex0", 0);
    Texture* planksSpec = createTexture("textures/planks.png", GL_TEXTURE_2D, 1, GL_RED, GL_UNSIGNED_BYTE);
    texUnit(shaderProgram, "tex1", 1);

    glEnable(GL_DEPTH_TEST);

    Camera* cam = createCamera(WIDTH, HEIGHT, (vec3){0.0f, 0.0f, 2.0f});

    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Inputs(cam, window);
        updateMatrix(cam, 45.0f, 0.1f, 100.0f);
        ActivateShaders(shaderProgram);
        glUniform3f(glGetUniformLocation(shaderProgram->ID, "camPos"), cam->Position[0], cam->Position[1], cam->Position[2]);
        Matrix(cam, shaderProgram, "camMatrix");

        ActivateShaders(lightShaders);
        glUniformMatrix4fv(glGetUniformLocation(lightShaders->ID, "model"), 1, GL_FALSE, (float*)lightModel);
        glUniform4f(glGetUniformLocation(lightShaders->ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
        ActivateShaders(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, (float*)pyramidModel);
        glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
        glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), lightPos[0], lightPos[1], lightPos[2]);

        BindTexture(planksTex);
        BindTexture(planksSpec);
        BindVAO(vao_);

        glDrawElements(GL_TRIANGLES, sizeof(indices)/sizeof(int), GL_UNSIGNED_INT, 0);

        ActivateShaders(lightShaders);
        Matrix(cam, lightShaders, "camMatrix");
        BindVAO(lightVAO);
        glDrawElements(GL_TRIANGLES, sizeof(lightIndices)/sizeof(int), GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    DeleteVAO(vao_);
    DeleteVBO(vbo_);
    DeleteEBO(ebo_);
    DeleteTexture(planksTex);
    DeleteTexture(planksSpec);
    DeleteShaders(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}