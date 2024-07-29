
/*
This is a program that aims to draw a rectangle on the screen
It makes use of Index Buffers in order to eliminate repeting vertices
It also implements a way of getting OpenGl errors using the GlGetError function
The use of Macros significally improves the structure of the code
*/


#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <signal.h>
#include <iostream>

#define ASSERT(x) if(!(x)) raise(SIGTRAP) 
#define GLCall(x) GLCLearError();\
    x;\
    ASSERT(GLLOGCall(#x, __FILE__, __LINE__))

static void GLCLearError(){
    // get errors just to clean them
    while (glGetError() != GL_NO_ERROR); // or !glGetError()
}

const char* GetGLErrorString(GLenum error) {

    switch (error) {
        case GL_NO_ERROR:
            return "No error";
        case GL_INVALID_ENUM:
            return "Invalid enum";
        case GL_INVALID_VALUE:
            return "Invalid value";
        case GL_INVALID_OPERATION:
            return "Invalid operation";
        case GL_STACK_OVERFLOW:
            return "Stack overflow";
        case GL_STACK_UNDERFLOW:
            return "Stack underflow";
        case GL_OUT_OF_MEMORY:
            return "Out of memory";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "Invalid framebuffer operation";
        case GL_CONTEXT_LOST:
            return "Context lost";
        default:
            return "Unknown error";
    }
}

static bool GLLOGCall(const char* function, const char* file, int line){
    // While error is different than 0
    if (GLenum error = glGetError()){
        std::cout << "[OpenGl Error]: (" << error << " - "<<GetGLErrorString(error) <<"): "<< function << " " << file
        << ":" << line << std::endl;
        return false;
    }
    return true;
}


static uint CompileShader(const std::string& source, uint type){

    GLCall(uint id = glCreateShader(type));
    const char* src = source.c_str();
    GLCall(glShaderSource(id, 1, &src, nullptr));
    GLCall(glCompileShader(id));

    // Error Handling
    int result;
    GLCall(glGetShaderiv(id, GL_COMPILE_STATUS, &result));
    if (result == GL_FALSE){
        int length;
        GLCall(glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length));
        char* message = (char*)alloca(length * sizeof(char));
        GLCall(glGetShaderInfoLog(id, length, &length, message));

        std::cout << "Failed to compile shader" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        
        GLCall(glDeleteShader(id));
        return 0;
    }


    return id;
}

static uint CreateShader(const std::string& vertexShader, const std::string& fragmentShader){

    GLCall(uint program = glCreateProgram());
    uint vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    uint fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    GLCall(glAttachShader(program, vs));
    GLCall(glAttachShader(program, fs));

    GLCall(glLinkProgram(program));
    GLCall(glValidateProgram(program));
    
    GLCall(glDeleteShader(vs));
    GLCall(glDeleteShader(fs));

    return program;
}



int main(void){

    GLFWwindow* window;

    // Initialize the library
    if (!glfwInit()){
        std::cout << "Error initializing glfw! " << std::endl;
        return -1;
    }


    // Create a windowed mode window and its OpenGL Context
    window = glfwCreateWindow(640, 480, "RedCherno", nullptr, nullptr);
    if (!window){
        glfwTerminate();
        return -1;
    }

    // Make the window's context current
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK){
        std::cout << "ERROR while initializing GLEW" << std::endl;
        return -1;
    }

    // Define Vertex Buffer (VBO?) to be allocated in VRAM

    float positions[] = {
        -0.5f, -0.5f, // 0
        0.5f,  -0.5f, // 1
        0.5f,  0.5f, // 2
        -0.5f, 0.5f // 3
    };

    uint indices[]{
        0, 1, 2,
        2, 3, 0
    };

    // The ID - identifier for the buffer
    uint buffer;
    GLCall(glGenBuffers(1, &buffer));
    // Actually select that buffer - BIND
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, buffer));
    // Put data into the buffer
    GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 4 * 2, positions, GL_STATIC_DRAW));
    
    // Stores indices in the GPU
    uint ibo;
    GLCall(glGenBuffers(1, &ibo));
    // Actually select that buffer - BIND
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
    // Put data into the buffer
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint) * 6, indices, GL_STATIC_DRAW));



    GLCall(glEnableVertexAttribArray(0));
    GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0));





    std::string vertexShader = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) in vec4 position;\n"
    "void main(){\n"
    "   gl_Position = position;\n"
    "}\n";


    std::string fragmentShader = 
    "#version 330 core\n"
    "\n"
    "layout(location = 0) out vec4 color;\n"
    "void main(){\n"
    "   color = vec4(0.5, 0.0, 1.0, 1.0);\n"
    "}\n";


    uint shader = CreateShader(vertexShader, fragmentShader);
    GLCall(glUseProgram(shader));

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)){

        // Render Here
        /* clears the specified buffers with the defined colors in glClearColor/glClearDepth/glClearStencil*/
        GLCall(glClear(GL_COLOR_BUFFER_BIT));


        /*Using Modern OpenGl*/
        GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));


        //Swap front and back buffers
        glfwSwapBuffers(window);

        // Pool for and process events
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}








