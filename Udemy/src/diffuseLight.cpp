
#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Windoh.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"

// Window dimensions
const float toRadians = M_PI / 180.0f;

Windoh mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;

Light mainLight;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex shader
static const char* vShader = "res/shaders/diffuseVertex.glsl";

// fragment shader
static const char* fShader = "res/shaders/diffuseFrag.glsl";


void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
                        unsigned int vLength, unsigned int normalOffset)
{
    for (unsigned int i=0; i<indiceCount; i+=3)
    {
        unsigned int in0 = indices[i] * vLength;
        unsigned int in1 = indices[i+1] * vLength;
        unsigned int in2 = indices[i+2] * vLength;

        glm::vec3 v1 (vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0+2]);
        glm::vec3 v2 (vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0+2]);
        glm::vec3 v3 (vertices[in2] - vertices[in1], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0+2]);

        glm::vec3 normal = glm::normalize(glm::cross(v1, v2));

        in0 += normalOffset;
        in1 += normalOffset;
        in2 += normalOffset;

        vertices[in0] += normal.x;
        vertices[in0 + 1] += normal.y;
        vertices[in0 + 2] += normal.z;
        vertices[in1] += normal.x;
        vertices[in1 + 1] += normal.y;
        vertices[in1 + 2] += normal.z;
        vertices[in2] += normal.x;
        vertices[in2 + 1] += normal.y;
        vertices[in2 + 2] += normal.z;
    }

    for (unsigned int i = 0; i < verticeCount/vLength; i++)
    {
        unsigned int nOffset = i * vLength + normalOffset;
        glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
        vec = glm::normalize(vec);
        vertices[nOffset] = vec.x;
        vertices[nOffset + 1] = vec.y;
        vertices[nOffset + 2] = vec.z;
    }

}


void CreateObject() {

    unsigned int indices[] = 
    {
        0, 3, 1, // left side
        1, 3, 2, // right side
        2, 3, 0, // front 
        0, 1, 2 // bottom
    };


    GLfloat vertices[] = {
    //   x      y      z      u     v       normals
        -1.0f, -1.0f, 0.0f,   0.0f, 0.0f,   0.0f, 0.0f, 0.0f,     // Bottom left - 0
        0.0f, -1.0f, 1.0f,    0.5f, 0.0f,   0.0f, 0.0f, 0.0f,     // Back - 1
        1.0f, -1.0f, 0.0f,    1.0f, 0.0f,   0.0f, 0.0f, 0.0f,     // Bottom right - 2 
        0.0f,  1.0f, 0.0f,    0.5f, 1.0f,   0.0f, 0.0f, 0.0f,     // TOP - 3
        };

    calcAverageNormals(indices, 12, vertices, 32, 8, 5);

    Mesh* pyramid = new Mesh();   
    pyramid->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(pyramid);
    Mesh* pyramid2 = new Mesh();   
    pyramid2->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(pyramid2);
}


void CreateShaders()
{
    Shader* shader1 = new Shader();
    shader1->CreateFromFile(vShader, fShader);
    shaderList.push_back(shader1);
}


int main() {

    mainWindow = Windoh();
    if (mainWindow.Initialise(true, true)){ return 1; };

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0, 5.0f, 0.1f);


    brickTexture = Texture("res/Textures/brick.png");
    brickTexture.LoadTexture();
    dirtTexture = Texture("res/Textures/dirt.png");
    dirtTexture.LoadTexture();

    mainLight = Light(1.0f, 1.0f, 1.0f, 0.4f, 2.0f, 0.0f, -2.0f, 1.0f);

    CreateObject();
    CreateShaders();


    // Uniforms and stuff
    GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0,
     uniformAmbientColor = 0, uniformAmbientIntensity = 0,
     uniformDirection = 0, uniformDiffuseIntensity = 0;

    // Projection model 
    glm::mat4 projection = glm::perspective(toRadians * 45.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

    // Loop until window closes

    while (!mainWindow.getShouldClose()) {

        GLfloat current = glfwGetTime();
        deltaTime = current - lastTime;
        lastTime = current;

        // Get and handle user input events
        glfwPollEvents();

        camera.keyControl(mainWindow.getKeys(), deltaTime);
        camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

        // Clear Window
        glClearColor(0.05f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0]->UseShader();
        uniformModel = shaderList[0]->GetModelLocation();
        uniformProjection = shaderList[0]->GetProjectionLocation();
        uniformView = shaderList[0]->GetViewLocation();
        uniformAmbientColor = shaderList[0]->GetAmbientColorLocation();
        uniformAmbientIntensity = shaderList[0]->GetAmbientIntensityLocation();
        uniformDirection = shaderList[0]->GetDirectionLocation();
        uniformDiffuseIntensity = shaderList[0]->GetDiffuseIntensityLocation();

        mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColor, uniformDiffuseIntensity, uniformDirection);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));


        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
        glUniform1i(glGetUniformLocation(shaderList[0]->getID(), "theTexture"), 0);
       
        brickTexture.UseTexture();
        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        dirtTexture.UseTexture();
        meshList[1]->RenderMesh();


        // Create static function that clears shaders
        glUseProgram(0);
        mainWindow.swapBuffers();
    }
    return 0;
}
