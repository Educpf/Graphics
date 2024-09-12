#include "Windoh.h"

#include <iostream>

void Windoh::calculateProjectionMatrix()
{
    projection = glm::perspective((GLfloat)(M_PI / 180.0f * 45.0f), (GLfloat)bufferWidth / (GLfloat)bufferHeight, 0.1f, 100.0f);
}

void Windoh::framebuffer_size_callback(GLFWwindow* window, int width,
                                       int height) {
    Windoh* windoh = static_cast<Windoh*>(glfwGetWindowUserPointer(window));
    glViewport(0, 0, width, height);
    windoh->bufferHeight = height;
    windoh->bufferWidth = width;
    windoh->calculateProjectionMatrix();
    
}

void Windoh::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    Windoh* windoh = static_cast<Windoh*>(glfwGetWindowUserPointer(window));

    if (key == GLFW_KEY_Q && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    if (key == GLFW_KEY_P && action == GLFW_PRESS) windoh->lockedInput = !windoh->lockedInput;

    if (key >= 0 && key < 1024 && !windoh->lockedInput)
    {
        if (action == GLFW_PRESS) windoh->keys[key] = true;
        else if (action == GLFW_RELEASE) windoh->keys[key] = false;
    }


    

}

void Windoh::handleMouse(GLFWwindow* window, double xNew, double yNew)
{
    Windoh* windoh = static_cast<Windoh*>(glfwGetWindowUserPointer(window));

    if (windoh->mouseFirstMoved)
    {
        windoh->lastX = xNew;
        windoh->lastY = yNew;
        windoh->mouseFirstMoved = false;
    }

    windoh->xChange += xNew - windoh->lastX;
    windoh->yChange += windoh->lastY - yNew;
    windoh->lastX = xNew;
    windoh->lastY = yNew;

}

int Windoh::Initialise(bool resize, bool disableMouse)
{

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
    mainWindow = glfwCreateWindow(width, height, "Test window", nullptr, nullptr);

    if (!mainWindow) {
        printf("GLFW Window creation failed!");
        glfwTerminate();
        return 1;
    }



    // Create CALLBACKS

    if (resize)
    {
        glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);
        glfwSetFramebufferSizeCallback(mainWindow, framebuffer_size_callback);
    }else
    {
        bufferHeight = height;
        bufferWidth = width;
    }   
        // Keys
    glfwSetKeyCallback(mainWindow, handleKeys);
        // Mouse
    glfwSetCursorPosCallback(mainWindow, handleMouse);
    if (disableMouse) glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    calculateProjectionMatrix();

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

    // Define who "owns" the window
    glfwSetWindowUserPointer(mainWindow, this);


    return 0;
}

Windoh::~Windoh()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}