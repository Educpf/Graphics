#pragma once

#include <GL/glew.h>


class Material {

 public:
    Material() : specularIntensity(0), shininess(0) {};
    Material(GLfloat specularIntensity, GLfloat shininess) : specularIntensity(specularIntensity), shininess(shininess) {};
    ~Material();
 private:

    GLfloat specularIntensity;
    GLfloat shininess;

 public:

    void UseMaterial(GLuint specularIntensityLocation, GLuint shininessLocation);
};