#pragma once

#include <GL/glew.h>
#include <stdio.h>
#include <string.h>

#include <fstream>
#include <iostream>

#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class Shader {
   public:
    Shader()
        : shaderID(0),
          uniformProjection(0),
          uniformModel(0),
          uniformView(0),
          pointLightCount(0),
          spotLightCount(0) {};

    ~Shader();

   private:
    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode,
                   GLenum shaderType);

    void ClearShader();

   public:
    void CreateFromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFile(const char* vertexPath, const char* fragmentPath);

    std::string ReadFile(const char* filePath);

   public:
    void UseShader();

    void SetDirectionalLight(DirectionalLight* directionalLight);
    void SetPointLights(PointLight* pointLights, unsigned int lightCount);
    void SetSpotLights(SpotLight* spotLights, unsigned int lightCount);

   public:
    uint getID() { return shaderID; };
    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();
    GLuint GetAmbientIntensityLocation();
    GLuint GetAmbientColorLocation();
    GLuint GetDiffuseIntensityLocation();
    GLuint GetDirectionLocation();
    GLuint GetSpecularIntensityLocation();
    GLuint GetShininessLocation();
    GLuint GetEyePositionLocation();

   private:
    GLuint shaderID, uniformProjection, uniformModel, uniformView,
        uniformEyePosition;
    GLuint uniformSpecularIntensity, uniformShininess;

    int pointLightCount;
    int spotLightCount;
    GLuint uniformPointLightCount, uniformSpotLightCount;

    struct {
        GLuint uniformColor;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformDirection;

    } uniformDirectionalLight;

    struct {
        GLuint uniformColor;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformPosition;
        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;

    } uniformPointLight[MAX_POINT_LIGHTS];

    struct {

        GLuint uniformColor;
        GLuint uniformAmbientIntensity;
        GLuint uniformDiffuseIntensity;

        GLuint uniformPosition;
        GLuint uniformDirection;
        GLuint uniformEdge;

        GLuint uniformConstant;
        GLuint uniformLinear;
        GLuint uniformExponent;

    } uniformSpotLight[MAX_SPOT_LIGHTS];

};