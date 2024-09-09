#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Windoh
{

 public:
    Windoh() : width(800), height(600), xChange(0), yChange(0)
    {
      for (unsigned int i = 0; i < 1024; i++)
      {
         keys[i] = 0;
      }

    };
    Windoh(GLint width, GLint height) : width(width), height(height), xChange(0), yChange(0)
    {
      for (unsigned int i = 0; i < 1024; i++)
      {
         keys[i] = 0;
      }

    };

    int Initialise(bool resize, bool disableMouse);

    inline GLint getBufferWidth() { return bufferWidth; };
    inline GLint getBufferHeight() { return bufferHeight; };

    inline bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }

    inline bool* getKeys(){ return keys; }
    inline GLfloat getXChange() { GLfloat change = xChange; xChange = 0; return change; }
    inline GLfloat getYChange() { GLfloat change = yChange; yChange = 0; return change; }

    inline void swapBuffers() { glfwSwapBuffers(mainWindow);}
   glm::mat4 getProjectionMatrix() { return projection;}

    ~Windoh();

 private:

    GLFWwindow* mainWindow;
    GLint width, height;
    GLint bufferWidth, bufferHeight;

    bool keys[1024];
    GLfloat lastX;
    GLfloat lastY;
    GLfloat xChange;
    GLfloat yChange;
    bool mouseFirstMoved;

   glm::mat4 projection;

   void calculateProjectionMatrix();
   static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
   static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
   static void handleMouse(GLFWwindow* window, double xNew, double yNew);
};