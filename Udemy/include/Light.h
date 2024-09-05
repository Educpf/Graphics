#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>


class Light 
{

 public:
    Light() : color(glm::vec3(1.0f, 1.0f, 1.0f)), ambientIntensity(1) {};
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity) : color(glm::vec3(red, green, blue)), ambientIntensity(ambientIntensity){};
 public:

    void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation);

 private:
    glm::vec3 color;
    GLfloat ambientIntensity;

};