#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <iostream>


// Window dimensions
const int WIDTH = 800, HEIGHT = 600;

GLuint VAO, VBO, shader;

// Vertex shader
static const char* vShader = 
"#version 330 core\n"
"\n"
"layout(location = 0) in vec3 pos;\n"
"void main(){\n"
    "float num = 1;\n"
"   gl_Position = vec4(pos.x * num, pos.y * num, pos.z * num, 1.0);\n"
"}\n";

// fragment shader
static const char* fShader = 
"#version 330 core\n"
"\n"
"out vec4 color;\n"
"void main(){\n"
"   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
"}\n";

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void CreateTriangle() {
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f
        };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            glEnableVertexAttribArray(0);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
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
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
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
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error linking program: %s\n", eLog);
        return;
    }

    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if (!result){
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error validating program: %s\n", eLog);
        return;
    }

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
        glfwCreateWindow(WIDTH, HEIGHT, "Test window", NULL, NULL);

    if (!mainWindow) {
        printf("GLFW Window creation failed!");
        glfwTerminate();
        return 1;
    }

    // Get buffer size information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

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

    glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);
    // Setup the viewPort Size - sets up the size we are drawing in the window - Looks up to the actuall size of the window
    glViewport(0, 0, bufferWidth, bufferHeight);

    CreateTriangle();
    CompileShaders();

    // Loop until window closes

    while (!glfwWindowShouldClose(mainWindow)) {
        // Get and handle user input events
        glfwPollEvents();

        // Clear Window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shader);

        glBindVertexArray(VAO);

        glDrawArrays(GL_TRIANGLES, 0, 3);

        glBindVertexArray(0);
        glUseProgram(0);


        glfwSwapBuffers(mainWindow);
    }
    glfwTerminate();
    return 0;
}
