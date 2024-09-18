
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

#include "CommonValues.h"

#include "Mesh.h"
#include "Shader.h"
#include "Windoh.h"
#include "Camera.h"
#include "Texture.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"

// Window dimensions
const float toRadians = M_PI / 180.0f;

Windoh mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader*> shaderList;
Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;

Material shinyMaterial;
Material dullMaterial;

DirectionalLight mainLight;
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

// Vertex shader
static const char* vShader = "res/shaders/spotLight/vertex.glsl";

// fragment shader
static const char* fShader = "res/shaders/spotLight/fragment.glsl";


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
        -1.0f, -1.0f, -0.6f,   0.0f, 0.0f,   0.0f, 0.0f, 0.0f,     // Bottom left - 0
        0.0f, -1.0f, 1.0f,    0.5f, 0.0f,   0.0f, 0.0f, 0.0f,     // Back - 1
        1.0f, -1.0f, -0.6f,    1.0f, 0.0f,   0.0f, 0.0f, 0.0f,     // Bottom right - 2 
        0.0f,  1.0f, 0.0f,    0.5f, 1.0f,   0.0f, 0.0f, 0.0f,     // TOP - 3
        };

    calcAverageNormals(indices, 12, vertices, 32, 8, 5);

    Mesh* pyramid = new Mesh();   
    pyramid->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(pyramid);
    Mesh* pyramid2 = new Mesh();   
    pyramid2->CreateMesh(vertices, indices, 32, 12);
    meshList.push_back(pyramid2);


    unsigned int floorIndices[] = 
    {
        0, 2, 1, // left up triangle
        1, 2, 3, // right bottom triangle
    };


    GLfloat floorVertices[] = {
    //   x      y      z      u     v       normals
        -10.0f, -0.0f, -10.0f,   0.0f, 0.0f,   0.0f, -1.0f, 0.0f,     // Top left - 0
        10.0f, 0.0f, -10.0f,    10.0f, 0.0f,   0.0f, -1.0f, 0.0f,     // Top right - 1
        -10.0f, 0.0f, 10.0f,    0.0f, 10.0f,   0.0f, -1.0f, 0.0f,     // Bottom left - 2 
        10.0f,  0.0f, 10.0f,    10.0f, 10.0f,  0.0f, -1.0f, 0.0f,     // Bottom right - 3
    };

    Mesh *obj3 = new Mesh();
    obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
    meshList.push_back(obj3);

}


void CreateShaders()
{
    Shader* shader1 = new Shader();
    shader1->CreateFromFile(vShader, fShader);
    shaderList.push_back(shader1);
}


int main() {
    
    mainWindow = Windoh();
    if (mainWindow.Initialise(true, true, true)){ return 1; };

    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0, 3.0f, 0.1f);


    brickTexture = Texture("res/Textures/brick.png");
    brickTexture.LoadTexture();
    dirtTexture = Texture("res/Textures/dirt.png");
    dirtTexture.LoadTexture();
    plainTexture = Texture("res/Textures/plain.png");
    plainTexture.LoadTexture();

    shinyMaterial = Material(1.0f, 256);
    dullMaterial = Material(0.3f, 4);

    mainLight = DirectionalLight(1.0f, 1.0f, 1.0f, // color
                                0.1f, 0.1f,  // ambient and diffuse intensity
                                0.0f, 0.0f, -1.0f); // Direction

    unsigned int pointLightCount = 0;
    // pointLightCount++;
    pointLights[0] = PointLight(0.0f, 0.0f, 1.0f,   // color
                                0.0f, 0.1f,        // ambient and diffuse intensity
                                0.0f, 0.0f, 0.0f, // position
                                0.3f, 0.2f, 0.1f); // distance attenuation

    // pointLightCount++;
    pointLights[1] = PointLight(0.0f, 1.0f, 0.0f,   // color
                                0.0f, 0.1f,        // ambient and diffuse intensity
                                -4.0f, 2.0f, 0.0f, // position
                                0.3f, 0.1f, 0.1f); // distance attenuation

    unsigned int spotLightCount = 0;
    spotLightCount++;
    spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,   // color
                                0.0f, 2.0f,        // ambient and diffuse intensity
                                0.0f, 0.0f, 0.0f, // position
                                0.0f, -1.0f, 0.0f, // direction
                                0.3f, 0.2f, 0.1f,  // distance attenuation
                                20.0f);             // edge

    CreateObject();
    CreateShaders();


    // Uniforms and stuff
    GLuint uniformModel = 0, uniformProjection = 0, uniformView = 0, uniformEyePosition = 0,
     uniformSpecularIntensity = 0, uniformShininess = 0;


    // Loop until window closes

    while (!mainWindow.getShouldClose()) {

        // Projection model 
        glm::mat4 projection = mainWindow.getProjectionMatrix();

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
        uniformEyePosition = shaderList[0]->GetEyePositionLocation();
        uniformSpecularIntensity = shaderList[0]->GetSpecularIntensityLocation();
        uniformShininess = shaderList[0]->GetShininessLocation();


        spotLights[0].SetFlash(camera.getCameraPosition() - glm::vec3(0, 0.3, 0), camera.getCameraDirection());
        shaderList[0]->SetDirectionalLight(&mainLight);
        shaderList[0]->SetPointLights(pointLights, pointLightCount);
        shaderList[0]->SetSpotLights(spotLights, spotLightCount);


        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.CalculateViewMatrix()));
        glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.5f));
        // model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniform1i(glGetUniformLocation(shaderList[0]->getID(), "theTexture"), 0);
       
        brickTexture.UseTexture();
        shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
        meshList[0]->RenderMesh();




        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 3.0f, -2.5f));
        // model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        dirtTexture.UseTexture();
        dullMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
        meshList[1]->RenderMesh();





        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
        // model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));

        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        dirtTexture.UseTexture();
        shinyMaterial.UseMaterial(uniformSpecularIntensity, uniformShininess);
        meshList[2]->RenderMesh();



        // Create static function that clears shaders
        glUseProgram(0);
        mainWindow.swapBuffers();
    }
    return 0;
}
