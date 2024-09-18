#pragma once


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Camera{

 public:
    Camera() {};
    Camera(glm::vec3 pos, glm::vec3 up, GLfloat yaw, GLfloat pitch, GLfloat mSpeed, GLfloat tSpeed) 
    : position(pos),  front(glm::vec3(0.0f, 0.0f, -1.0f)), worldUp(up), yaw(yaw), pitch(pitch),
     movementSpeed(mSpeed), turnSpeed(tSpeed) {update(); };
    ~Camera(){};

 public:

   void keyControl(bool* keys, GLfloat time);
   void mouseControl(GLfloat xChange, GLfloat yChange);
   glm::mat4 CalculateViewMatrix();

   glm::vec3 getCameraPosition();
   glm::vec3 getCameraDirection();

 private:
    glm::vec3 position;
    glm::vec3 front;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat movementSpeed;
    GLfloat turnSpeed;

    void update();
};