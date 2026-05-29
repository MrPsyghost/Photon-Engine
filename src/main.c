#include "mesh.h"

#define WIDTH  1000
#define HEIGHT 600

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    Vertex vertices[] = {
        {
            {-1.0f, 0.0f,  1.0f}, // position
            {0.0f, 1.0f, 0.0f},   // normal
            {1.0f, 1.0f, 1.0f},   // color
            {0.0f, 0.0f}          // texUV
        },

        {
            {-1.0f, 0.0f, -1.0f},
            {0.0f, 1.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 1.0f}
        },

        {
            { 1.0f, 0.0f, -1.0f},
            {0.0f, 1.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {1.0f, 1.0f}
        },

        {
            { 1.0f, 0.0f,  1.0f},
            {0.0f, 1.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {1.0f, 0.0f}
        }
    };

    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    Vertex lightVertices[] = {
        {
            {-0.1f, -0.1f,  0.1f},
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 0.0f}
        },

        {
            {-0.1f, -0.1f, -0.1f},
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 0.0f}
        },

        {
            {0.1f, -0.1f, -0.1f},
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 0.0f}
        },

        {
            {0.1f, -0.1f,  0.1f},
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 0.0f}
        },

        {
            {-0.1f,  0.1f,  0.1f},
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 0.0f}
        },

        {
            {-0.1f,  0.1f, -0.1f},
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 0.0f}
        },

        {
            {0.1f,  0.1f, -0.1f},
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 0.0f}
        },

        {
            {0.1f,  0.1f,  0.1f},
            {0.0f, 0.0f, 0.0f},
            {1.0f, 1.0f, 1.0f},
            {0.0f, 0.0f}
        }
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
        4, 6, 7
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

    Texture* textures[] = {
        createTexture("textures/planks.png", "diffuse", 0, GL_UNSIGNED_BYTE),
        createTexture("textures/planksSpec.png", "specular", 1, GL_UNSIGNED_BYTE),
    };
    
    Shaders* shaderProgram = createShaders("shaders/default.vert", "shaders/default.frag");
    
    size_t vertexCount = sizeof(vertices) / sizeof(Vertex);
    Vertex* verts = malloc(vertexCount * sizeof(Vertex));
    memcpy(verts, vertices, vertexCount * sizeof(Vertex));

    size_t indexCount = sizeof(indices) / sizeof(GLuint);
    GLuint* ind = malloc(indexCount * sizeof(GLuint));
    memcpy(ind, indices, indexCount * sizeof(GLuint));
    
    size_t texCount = sizeof(textures) / sizeof(Texture*);
    
    Mesh* floor = createMesh(vertices, vertexCount, indices, indexCount, textures, texCount);
    
    Shaders* lightShaders = createShaders("shaders/light.vert", "shaders/light.frag");
    
    size_t lightVertexCount = sizeof(lightVertices) / sizeof(Vertex);
    Vertex* lightVerts = malloc(lightVertexCount * sizeof(Vertex));
    memcpy(lightVerts, lightVertices, lightVertexCount * sizeof(Vertex));
    
    size_t lightIndexCount = sizeof(lightIndices) / sizeof(GLuint);
    GLuint* lightInd = malloc(lightIndexCount * sizeof(GLuint));
    memcpy(lightInd, lightIndices, lightIndexCount * sizeof(GLuint));
    
    Mesh* light = createMesh(lightVertices, lightVertexCount, lightIndices, lightIndexCount, textures, texCount);
    
    vec4 lightColor = {1.0f, 1.0f, 1.0f, 1.0f};
    
    vec3 lightPos = {0.5f, 0.5f, 0.5f};
    mat4 lightModel;
    glm_mat4_identity(lightModel);
    glm_translate(lightModel, lightPos);
    
    vec3 pyramidPos = {0.0f, 0.0f, 0.0f};
    mat4 pyramidModel;
    glm_mat4_identity(pyramidModel);
    glm_translate(pyramidModel, pyramidPos);
    
    ActivateShaders(lightShaders);
    glUniformMatrix4fv(glGetUniformLocation(lightShaders->ID, "model"), 1, GL_FALSE, (float*)lightModel);
    glUniform4f(glGetUniformLocation(lightShaders->ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
    ActivateShaders(shaderProgram);
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram->ID, "model"), 1, GL_FALSE, (float*)pyramidModel);
    glUniform4f(glGetUniformLocation(shaderProgram->ID, "lightColor"), lightColor[0], lightColor[1], lightColor[2], lightColor[3]);
    glUniform3f(glGetUniformLocation(shaderProgram->ID, "lightPos"), lightPos[0], lightPos[1], lightPos[2]);
    
    glEnable(GL_DEPTH_TEST);
    
    Camera* cam = createCamera(WIDTH, HEIGHT, (vec3){0.0f, 0.0f, 2.0f});
    
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        Inputs(cam, window);
        updateMatrix(cam, 45.0f, 0.1f, 100.0f);

        DrawMesh(floor, shaderProgram, cam);
        DrawMesh(light, lightShaders, cam);

        glfwSwapBuffers(window);

        glfwPollEvents();
    }

    DeleteShaders(shaderProgram);
    DeleteShaders(lightShaders);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}