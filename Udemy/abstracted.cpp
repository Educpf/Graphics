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

// Window dimensions
const float toRadians = M_PI / 180.0f;

Windoh mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;

// Vertex shader
static const char* vShader = "shaders/vertex.glsl";

// fragment shader
static const char* fShader = "shaders/fragment.glsl";


void CreateObject() {

    unsigned int indices[] = 
    {
        0, 3, 1, // left side
        1, 3, 2, // right side
        2, 3, 0, // front 
        0, 1, 2 // bottom
    };


    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f, // Bottom left - 0
        0.0f, -1.0f, 1.0f,  // Back - 1
        1.0f, -1.0f, 0.0f, // Bottom right - 2 
        0.0f,  1.0f, 0.0f // TOP - 3
        };


    Mesh* pyramid = new Mesh();   
    pyramid->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(pyramid);
    Mesh* pyramid2 = new Mesh();   
    pyramid2->CreateMesh(vertices, indices, 12, 12);
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
    if (mainWindow.Initialise(true)){ return 1; };

    CreateObject();
    CreateShaders();

    // Uniforms and stuff
    GLuint uniformModel, uniformProjection;


    // Projection model 
    glm::mat4 projection = glm::perspective(toRadians * 90.0f, (GLfloat)mainWindow.getBufferWidth() / (GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

    // Loop until window closes

    while (!mainWindow.getShouldClose()) {
        // Get and handle user input events
        glfwPollEvents();

        // Clear Window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shaderList[0]->UseShader();
        uniformModel = shaderList[0]->GetModelLocation();
        uniformProjection = shaderList[0]->GetProjectionLocation();

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));


        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

        meshList[0]->RenderMesh();

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 1.0f, -2.5f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        meshList[1]->RenderMesh();


        // Create static function that clears shaders
        glUseProgram(0);
        mainWindow.swapBuffers();
    }
    return 0;
}
