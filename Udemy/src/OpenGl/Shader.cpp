#include "Shader.h"


GLuint Shader::GetProjectionLocation() 
{
    return uniformProjection; 
}


GLuint Shader::GetModelLocation() 
{
    return uniformModel; 
}

GLuint Shader::GetViewLocation(){
    return uniformView;
}

GLuint Shader::GetAmbientIntensityLocation() { return uniformAmbientIntensity; }

GLuint Shader::GetAmbientColorLocation() { return uniformAmbientColor; }

GLuint Shader::GetDiffuseIntensityLocation() { return uniformDiffuseIntensity; }

GLuint Shader::GetDirectionLocation() { return uniformDirection; }

GLuint Shader::GetSpecularIntensityLocation() { return uniformSpecularIntensity; }

GLuint Shader::GetShininessLocation() { return uniformShininess; }

GLuint Shader::GetEyePositionLocation() { return uniformEyePosition; }

void Shader::CreateFromString(const char* vertexCode,
                              const char* fragmentCode) {
    CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* filePath)
{

    std::string content;
    std::ifstream fileStream(filePath, std::ios::in);

    if (!fileStream.is_open()){
        std::cout << "Failed to read: " << filePath << "!\n";
        return "";
    }

    std::string line = "";
    while (std::getline(fileStream, line))
    {
        content.append(line + "\n");
    }

    fileStream.close();
    return content;

}

void Shader::CreateFromFile(const char* vertexPath, const char* fragmentPath)
{
    CompileShader(ReadFile(vertexPath).c_str(), ReadFile(fragmentPath).c_str());
}

void Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
    // Stores shader program as ID
    shaderID = glCreateProgram();
    if (!shaderID){
        printf("Error creating shader program!");
        return;
    }

    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shaderID);

    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        printf("Error linking program: %s\n", eLog);
        return;
    }

    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shaderID, sizeof(eLog), nullptr, eLog);
        printf("Error validating program: %s\n", eLog);
        return;
    }
    

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformAmbientColor = glGetUniformLocation(shaderID, "directionLight.color");
    uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionLight.ambientIntensity");
    uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionLight.diffuseIntensity");
    uniformDirection = glGetUniformLocation(shaderID, "directionLight.direction");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
    uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
    uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");
}

void Shader::AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType)
{
    GLuint theShader = glCreateShader(shaderType);

    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLenght[1];
    codeLenght[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLenght);
    glCompileShader(theShader);

    // Error handling
    GLint result = 0;
    GLchar eLog[1024] = {0};


    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if (!result){
        glGetShaderInfoLog(theShader, sizeof(eLog), nullptr, eLog);
        printf("Error compiling the %d shader: %s\n", shaderType, eLog);
        return;
    }

    glAttachShader(theProgram, theShader);
}


void Shader::UseShader()
{
    glUseProgram(shaderID);
}

void Shader::ClearShader()
{
    if (shaderID != 0){
        glDeleteProgram(shaderID);
        shaderID = 0;
    }

    uniformModel = 0;
    uniformProjection = 0;
    uniformView = 0;
}

Shader::~Shader()
{
    ClearShader();
}