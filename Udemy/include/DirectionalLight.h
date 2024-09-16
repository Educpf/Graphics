#pragma once
#include "Light.h"


class DirectionalLight : 
    public Light
{
 public:
    DirectionalLight();
    ~DirectionalLight();
   DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity,
         GLfloat xDirection, GLfloat yDirection, GLfloat zDirection);


   void UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation, GLfloat diffuseIntensityLocation, 
                GLfloat directionLocation);

 private:
    glm::vec3 direction;
};