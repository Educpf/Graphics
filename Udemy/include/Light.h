#pragma once

#include <GL/glew.h>
#include <glm/glm.hpp>


class Light 
{

 public:
   Light() : color(glm::vec3(1.0f, 1.0f, 1.0f)), ambientIntensity(1), direction(glm::vec3(0.0f, -1.0f, 0.0f)), diffuseIntensity(0.0f){};
   
   Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity,
         GLfloat xDirection, GLfloat yDirection, GLfloat zDirection, GLfloat diffuseIntensity) 
         : color(glm::vec3(red, green, blue)), ambientIntensity(ambientIntensity), direction(glm::vec3(xDirection, yDirection, zDirection)), diffuseIntensity(diffuseIntensity){};

 public:


   void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);

 private:
   glm::vec3 color;
   GLfloat ambientIntensity;

   glm::vec3 direction;
   GLfloat diffuseIntensity;
    
};