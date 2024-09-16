#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>


class Light 
{

 public:
   Light() : color(glm::vec3(1.0f, 1.0f, 1.0f)), ambientIntensity(1), diffuseIntensity(0.0f){};
   
   Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity) 
         : color(glm::vec3(red, green, blue)), ambientIntensity(ambientIntensity), diffuseIntensity(diffuseIntensity){};

 public:


 protected:
   glm::vec3 color;
   GLfloat ambientIntensity;

   GLfloat diffuseIntensity;
    
};