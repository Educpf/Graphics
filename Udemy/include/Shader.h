#pragma once


#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>

#include <GL/glew.h>


class Shader 
{
 public:
    Shader() : shaderID(0),  uniformProjection(0), uniformModel(0), uniformView(0) {};
    ~Shader();
 private:
    GLuint shaderID, uniformProjection, uniformModel, uniformView, uniformAmbientIntensity, uniformAmbientColor;

    void CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);

    std::string ReadFile(const char* filePath);

 public:

    void CreateFromString(const char* vertexCode, const char* fragmentCode);
    void CreateFromFile(const char* vertexPath, const char* fragmentPath);

    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();
    GLuint GetAmbientIntensityLocation();
    GLuint GetAmbientColorLocation();

    void UseShader();
    void ClearShader();

 public:
   uint getID() { return shaderID; };


};