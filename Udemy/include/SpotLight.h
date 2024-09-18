#pragma once

#include "PointLight.h"

class SpotLight :
    public PointLight
{

 public:

    SpotLight();

    SpotLight(GLfloat red, GLfloat green, GLfloat blue,
                GLfloat ambientIntensity, GLfloat diffuseIntensity,
                GLfloat xPos, GLfloat yPos, GLfloat zPos,
                GLfloat xDirection, GLfloat yDirection, GLfloat zDirection,
                GLfloat constant, GLfloat linear, GLfloat exponent, 
                GLfloat edge);


    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColorLocation, GLuint diffuseIntensityLocation, 
                GLuint positionLocation, GLuint directionLocation, GLuint edgeLocation, 
                GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation);

    void SetFlash(glm::vec3 position, glm::vec3 front);



 private:

    glm::vec3 direction;

    GLfloat edge, processedEdge /*To reduce calculations inside shader*/;
};