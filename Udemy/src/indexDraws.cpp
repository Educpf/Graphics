#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


// Window dimensions
const int WIDTH = 800, HEIGHT = 600;
const float toRadians = M_PI / 180.0f;



GLuint VAO, VBO, IBO, shader, uniformModel;


bool direction = true;
float triOffset = 0;
float triMaxOffset = 0.7f;
float triIncrement = 0.005f;

bool sizeDirection = true;
float curSize = 0.4f;
float maxSize = 0.8f;
float minSize = 0.1f;

float curAngle = 0.0f;

// Vertex shader
static const char* vShader = 
"#version 330 core\n"
"\n"
"layout(location = 0) in vec3 pos;\n"
"uniform mat4 model;\n"
"out vec4 vCol;\n"
"void main(){\n"
"   gl_Position =  model * vec4(pos, 1.0);\n"
"   vCol =  vec4(clamp(pos, 0.0f, 1.0f),1.0f);\n"
"}\n";

// fragment shader
static const char* fShader = 
"#version 330 core\n"
"\n"
"out vec4 color;\n"
"in vec4 vCol;\n"
"void main(){\n"
"   color = vCol;\n"
"}\n";


void CreateTriangle() {

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


    

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    

    glBindVertexArray(0);

    // Unbind the IBO only after unbinding VAO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType){

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

    return;
}

void CompileShaders(){
    // Stores shader program as ID
    shader = glCreateProgram();
    if (!shader){
        printf("Error creating shader program!");
        return;
    }

    AddShader(shader, vShader, GL_VERTEX_SHADER);
    AddShader(shader, fShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(shader);

    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        printf("Error linking program: %s\n", eLog);
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shader, sizeof(eLog), nullptr, eLog);
        printf("Error validating program: %s\n", eLog);
        return;
    }
    

    uniformModel = glGetUniformLocation(shader, "model");

}



int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        printf("GLFW initialization failed!");
        glfwTerminate();
        return 1;
    }

    // ------ Setup GLFW Window properties
    // OpenGl Version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Is not backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create window
    GLFWwindow *mainWindow =
        glfwCreateWindow(WIDTH, HEIGHT, "Test window", nullptr, nullptr);

    if (!mainWindow) {
        printf("GLFW Window creation failed!");
        glfwTerminate();
        return 1;
    }


    // Set new context for Glew to use
    glfwMakeContextCurrent(mainWindow);

    // Allow modern extensions features - enable to access extensions (Not used
    // in this course tho
    // - they are "too advance")
    glewExperimental = GL_TRUE;

    if (glewInit() != GLEW_OK) {
        printf("Glew initialization failed!");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST);

    CreateTriangle();
    CompileShaders();

    // Loop until window closes

    while (!glfwWindowShouldClose(mainWindow)) {
        // Get and handle user input events
        glfwPollEvents();

        if (direction)
        {
            triOffset += triIncrement;
        }else 
        {
            triOffset -= triIncrement;
        }

        if(abs(triOffset) > triMaxOffset)
        {
            direction = !direction;
        }

        curAngle += 0.1f;
        if (curAngle >= 360){
            curAngle -= 360;
        }


        if (sizeDirection)
        {
            curSize += 0.001f;
        }else{
            curSize -= 0.001f;
        }

        if (curSize >= maxSize || curSize <= minSize) 
        {
            sizeDirection = !sizeDirection;
        }

        // Clear Window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(shader);

        glm::mat4 model(1.0f);
        // model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
        model = glm::rotate(model, curAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 1.0f));


        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));


        glBindVertexArray(VAO);

        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);

        glBindVertexArray(0);
        glUseProgram(0);


        glfwSwapBuffers(mainWindow);
    }
    glfwTerminate();
    return 0;
}
