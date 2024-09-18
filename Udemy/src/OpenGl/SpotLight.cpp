#include "SpotLight.h"

SpotLight::SpotLight()
    : PointLight()
{
    direction = glm::vec3(0.0f, -1.0f, 0.0f);
    edge = 0;
    processedEdge = cosf(glm::radians(edge));
}

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue,
                     GLfloat ambientIntensity, GLfloat diffuseIntensity,
                     GLfloat xPos, GLfloat yPos, GLfloat zPos,
                     GLfloat xDirection, GLfloat yDirection, GLfloat zDirection,
                     GLfloat constant, GLfloat linear, GLfloat exponent,
                     GLfloat edge)
    : PointLight(red, green, blue, ambientIntensity, diffuseIntensity, xPos, yPos, zPos, constant, linear, exponent)
{

    direction = glm::normalize(glm::vec3(xDirection, yDirection, zDirection));
    this->edge = edge;
    processedEdge = cosf(glm::radians(edge));
}

void SpotLight::SetFlash(glm::vec3 position, glm::vec3 direction)
{
    this->position = position;
    this->direction = direction;
}

void SpotLight::UseLight(GLuint ambientIntensityLocation,
                         GLuint ambientColorLocation,
                         GLuint diffuseIntensityLocation,
                         GLuint positionLocation, GLuint directionLocation,
                         GLuint edgeLocation, GLuint constantLocation,
                         GLuint linearLocation, GLuint exponentLocation)
{

    glUniform3f(ambientColorLocation, color.x, color.y, color.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);

    glUniform3f(positionLocation, position.x, position.y, position.z);
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(edgeLocation, processedEdge);

    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, exponent);

}
