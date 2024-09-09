#include "Material.h"

Material::~Material() {}

void Material::UseMaterial(GLuint specularIntensityLocation,
                           GLuint shininessLocation) {
    glUniform1f(specularIntensityLocation, specularIntensity);
    glUniform1f(shininessLocation, shininess);
}
