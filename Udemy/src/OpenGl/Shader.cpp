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

GLuint Shader::GetAmbientIntensityLocation() { return uniformDirectionalLight.uniformAmbientIntensity; }

GLuint Shader::GetAmbientColorLocation() { return uniformDirectionalLight.uniformColor; }

GLuint Shader::GetDiffuseIntensityLocation() { return uniformDirectionalLight.uniformDiffuseIntensity; }

GLuint Shader::GetDirectionLocation() { return uniformDirectionalLight.uniformDirection; }

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

void Shader::SetDirectionalLight(DirectionalLight* directionalLight)
{

    directionalLight->UseLight(uniformDirectionalLight.uniformAmbientIntensity, uniformDirectionalLight.uniformColor,
                                uniformDirectionalLight.uniformDiffuseIntensity, uniformDirectionalLight.uniformDirection);
}


void Shader::SetPointLights(PointLight* pointLights, unsigned int lightCount)
{
    if (lightCount > MAX_POINT_LIGHTS) lightCount = MAX_POINT_LIGHTS;

    glUniform1i(uniformPointLightCount, lightCount);

    for (uint8_t i = 0; i<lightCount; i++)
    {
        pointLights[i].UseLight(uniformPointLight[i].uniformAmbientIntensity,uniformPointLight[i].uniformColor,
                                uniformPointLight[i].uniformDiffuseIntensity, uniformPointLight[i].uniformPosition,
                                uniformPointLight[i].uniformConstant, uniformPointLight[i].uniformLinear, uniformPointLight[i].uniformExponent);
    }

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
    uniformDirectionalLight.uniformColor = glGetUniformLocation(shaderID, "directionLight.base.color");
    uniformDirectionalLight.uniformAmbientIntensity = glGetUniformLocation(shaderID, "directionLight.base.ambientIntensity");
    uniformDirectionalLight.uniformDiffuseIntensity = glGetUniformLocation(shaderID, "directionLight.base.diffuseIntensity");
    uniformDirectionalLight.uniformDirection = glGetUniformLocation(shaderID, "directionLight.direction");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
    uniformShininess = glGetUniformLocation(shaderID, "material.shininess");
    uniformEyePosition = glGetUniformLocation(shaderID, "eyePosition");

    uniformPointLightCount = glGetUniformLocation(shaderID, "pointLightCount");


    for (uint8_t i = 0 ; i < MAX_POINT_LIGHTS; i++)
    {
        char locBuff[100] = {'\0'};

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.color", i);
        uniformPointLight[i].uniformColor = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.ambientIntensity", i);
        uniformPointLight[i].uniformAmbientIntensity = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].base.diffuseIntensity", i);
        uniformPointLight[i].uniformDiffuseIntensity = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].position", i);
        uniformPointLight[i].uniformPosition = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].constant", i);
        uniformPointLight[i].uniformConstant = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].linear", i);
        uniformPointLight[i].uniformLinear = glGetUniformLocation(shaderID, locBuff);

        snprintf(locBuff, sizeof(locBuff), "pointLights[%d].exponent", i);
        uniformPointLight[i].uniformExponent = glGetUniformLocation(shaderID, locBuff);
    }
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