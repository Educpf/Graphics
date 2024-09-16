#pragma once


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

#include <GL/glew.h>


#include "DirectionalLight.h"
#include "PointLight.h"

#include "CommonValues.h"

class Shader 
{
 public:
   Shader() : shaderID(0),  uniformProjection(0), uniformModel(0), uniformView(0), pointLightCount(0) {};
   ~Shader();
 private:

   void CompileShader(const char* vertexCode, const char* fragmentCode);
   void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

   void ClearShader();

 public:

   void CreateFromString(const char* vertexCode, const char* fragmentCode);
   void CreateFromFile(const char* vertexPath, const char* fragmentPath);

   std::string ReadFile(const char* filePath);

 public:

   void UseShader();

   void SetDirectionalLight(DirectionalLight* directionalLight);
   void SetPointLights(PointLight* pointLights, unsigned int lightCount);

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

    GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformEyePosition;
    GLuint uniformPointLightCount, uniformSpecularIntensity, uniformShininess;

   int pointLightCount;

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

};