#include "camera.h"

Camera* createCamera(int width, int height, vec3 Position) {
    Camera* cam = malloc(sizeof(Camera));
    
    cam->width = width;
    cam->height = height;
    glm_vec3_copy(Position, cam->Position);
    glm_mat4_identity(cam->camMatrix);
    glm_vec3_copy((vec3){0.0f, 0.0f, -1.0f}, cam->Orientation);
    glm_vec3_copy((vec3){0.0f, 1.0f, 0.0f}, cam->Up);
    cam->speed = 0.01f;
    cam->sensitivity = 100.0f;
    cam->firstClick = true;
    
    return cam;
}

void updateMatrix(Camera* cam, float FOVdeg, float nearPlane, float farPlane) {
    mat4 view;
    mat4 projection;
    glm_mat4_identity(view);
    glm_mat4_identity(projection);
    
    vec3 centre;
    glm_vec3_add(cam->Position, cam->Orientation, centre);
    glm_lookat(cam->Position, centre, cam->Up, view);

    glm_perspective(glm_rad(FOVdeg), (float)cam->width/cam->height, nearPlane, farPlane, projection);

    glm_mat4_mul(projection, view, cam->camMatrix);
}

void Matrix(Camera* cam, Shaders* shaderPrgm, const char* uniform) {
    glUniformMatrix4fv(glGetUniformLocation(shaderPrgm->ID, uniform), 1, GL_FALSE, (float*)cam->camMatrix);
}

void Inputs(Camera* cam, GLFWwindow* window) {
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
        if (cam->firstClick) {
            glfwSetCursorPos(window, (float)cam->width/2, (float)cam->height/2);
            cam->firstClick = false;
        }
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        
        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
            vec3 newOrientation;
            glm_vec3_scale(cam->Orientation, cam->speed, newOrientation);
            glm_vec3_add(cam->Position, newOrientation, cam->Position);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
            vec3 right;
            glm_cross(cam->Orientation, cam->Up, right);
            glm_normalize(right);

            vec3 movement;
            glm_vec3_scale(right, -cam->speed, movement);
            glm_vec3_add(cam->Position, movement, cam->Position);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
            vec3 newOrientation;
            glm_vec3_scale(cam->Orientation, -cam->speed, newOrientation);
            glm_vec3_add(cam->Position, newOrientation, cam->Position);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
            vec3 right;
            glm_cross(cam->Orientation, cam->Up, right);
            glm_normalize(right);

            vec3 movement;
            glm_vec3_scale(right, cam->speed, movement);
            glm_vec3_add(cam->Position, movement, cam->Position);
        }

        if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
            vec3 newUp;
            glm_vec3_scale(cam->Up, cam->speed, newUp);
            glm_vec3_add(cam->Position, newUp, cam->Position);
        }
        if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
            vec3 newUp;
            glm_vec3_scale(cam->Up, -cam->speed, newUp);
            glm_vec3_add(cam->Position, newUp, cam->Position);
        }
        
        cam->speed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ? 0.04f : 0.01f;

        double mouseX, mouseY;
        glfwGetCursorPos(window, &mouseX, &mouseY);
        
        float rotX = cam->sensitivity * (float)(mouseY - (cam->height/2))/cam->height;
        float rotY = cam->sensitivity * (float)(mouseX - (cam->width/2))/cam->width;

        vec3 right;
        glm_cross(cam->Orientation, cam->Up, right);
        glm_normalize(right);
        
        vec3 newOrientation;
        glm_vec3_copy(cam->Orientation, newOrientation);
        glm_vec3_rotate(newOrientation, glm_rad(-rotX), right);
        
        vec3 Down;
        glm_vec3_scale(cam->Up, -1.0f, Down);
        
        float angleUp = glm_vec3_angle(newOrientation, cam->Up);
        float angleDown = glm_vec3_angle(newOrientation, Down);

        if (angleUp > glm_rad(5.0f) && angleDown > glm_rad(5.0f)) {
            glm_vec3_copy(newOrientation, cam->Orientation);
        }
        
        glm_vec3_rotate(cam->Orientation, glm_rad(-rotY), cam->Up);
        glfwSetCursorPos(window, (float)cam->width/2, (float)cam->height/2);
    } else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_RELEASE) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        cam->firstClick = true;
    }
}