
/*
This is a program that aims to draw a rectangle on the screen
It makes use of Index Buffers in order to eliminate repeating vertices
It also implements a way of getting OpenGl errors using the GlGetError function
The use of Macros significally improves the structure of the code

Update:
Now shaders are rendered from outside file located in the res/shaders directory
Both shaders (vertex and fragment are write in the same file)

Update:
Make use of Uniforms to be able to change the fragment shader to use CPU information
*/

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "Renderer.h"
#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include "Texture.h"


int main(void) {
    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit()) {
        std::cout << "Error initializing glfw! " << std::endl;
        return -1;
    }

    // Create a windowed mode window and its OpenGL Context
    window = glfwCreateWindow(640, 480, "RedCherno", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    // Syncronize with monitors refresh rate
    glfwSwapInterval(1);


    if (glewInit() != GLEW_OK) {
        std::cout << "ERROR while initializing GLEW" << std::endl;
        return -1;
    }

    // Define Vertex Buffer (VBO?) to be allocated in VRAM

    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
        0.5f,  -0.5f, 1.0f, 0.0f, // 1
        0.5f,  0.5f,  1.0f, 1.0f,  // 2
        -0.5f, 0.5f,  0.0f, 1.0f // 3
    };

    uint indices[]{0, 1, 2, 2, 3, 0};

    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    // Create VAO
    VertexArray vao;
    // The ID - identifier for the buffer
    VertexBuffer vb(positions, sizeof(float) * 4 * 4);
    // Stores indices in the GPU
    IndexBuffer ib(indices, 6);
    // Create Vertex Buffer layout
    VertexBufferLayout layout;
    layout.Push<float>(2);
    layout.Push<float>(2);
    // Bind the layout to the VAO
    vao.AddBuffer(vb, ib, layout);

    // Pase the shaders from the location specified

    Shader shader("res/shaders/Texture.glsl");
    shader.Bind();
    shader.SetUniform4f("u_Color", 0.8f, 0.3f, 0.8f, 1.0f);

    Texture texture("res/Him.png");

    texture.Bind(/*default 0*/);
    shader.SetUniform1i("u_Texture", 0/*matches the slot texture was bind to*/);

    vao.Unbind();
    vb.Unbind();
    ib.Unbind();
    shader.Unbind();

    Renderer renderer;

    float r = 0.0f;
    float increment = 0.005f;
    uint count = 0;

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)) {
        // Render Here
        /* clears the specified buffers with the defined colors in
         * glClearColor/glClearDepth/glClearStencil*/
        renderer.Clear();

        shader.Bind();
        shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f);

        /*Using Modern OpenGl*/
        renderer.Draw(vao, ib, shader);

        if (count % 4 == 0){
            if (r > 1.0f)
                increment = -0.05f;
            else if (r < 0.0f)
                increment = 0.05f;
            r += increment;
        }

        count++;
        // Swap front and back buffers
        glfwSwapBuffers(window);

        // Pool for and process events
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
