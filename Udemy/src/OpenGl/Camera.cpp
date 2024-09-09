#include "Camera.h"

void Camera::keyControl(bool* keys, GLfloat time)
{
    GLfloat distance = movementSpeed * time;

    if (keys[GLFW_KEY_W]) position += front * distance;
    if (keys[GLFW_KEY_S]) position -= front * distance;
    if (keys[GLFW_KEY_D]) position += right * distance;
    if (keys[GLFW_KEY_A]) position -= right * distance;
    if (keys[GLFW_KEY_SPACE]) position += worldUp * distance;
    if (keys[GLFW_KEY_LEFT_SHIFT]) position -= worldUp * distance;

}

void Camera::mouseControl(GLfloat xChange, GLfloat yChange)
{
    xChange *= turnSpeed;
    yChange *= turnSpeed;

    yaw += xChange;
    pitch += yChange;

    if (pitch > 89.0f) { pitch = 89.0f; }
    if (pitch < -89.0f) { pitch = -89.0f; }

    update();

}

glm::mat4 Camera::CalculateViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getCameraPosition() {return position;}

void Camera::update() {
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

    front = glm::normalize(front);

    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
