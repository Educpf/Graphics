#include "Light.h"

void Light::UseLight(GLfloat ambientIntensityLocation, GLfloat ambientColorLocation)
{
    glUniform3f(ambientColorLocation, color.x, color.y, color.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
}
