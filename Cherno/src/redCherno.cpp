#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>


static uint CompileShader(const std::string& source, uint type){

    uint id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    // Error Handling
    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE){
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);

        std::cout << "Failed to compile shader" << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << std::endl;
        std::cout << message << std::endl;
        
        glDeleteShader(id);
        return 0;
    }


    return id;
}

static uint CreateShader(const std::string& vertexShader, const std::string& fragmentShader){

    uint program = glCreateProgram();
    uint vs = CompileShader(vertexShader, GL_VERTEX_SHADER);
    uint fs = CompileShader(fragmentShader, GL_FRAGMENT_SHADER);

    glAttachShader(program, vs);
    glAttachShader(program, fs);

    glLinkProgram(program);
    glValidateProgram(program);
    
    glDeleteShader(vs);
    glDeleteShader(fs);

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
    window = glfwCreateWindow(640, 480, "RedCherno", NULL, NULL);
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

    float positions[6] = {
        -0.5f, -0.5f,
        0.0f,   0.5f,
        0.5f,  -0.5f
    };
    // The ID - identifier for the buffer
    uint buffer;
    glGenBuffers(1, &buffer);
    // Actually select that buffer - BIND
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    // Put data into the buffer
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6, positions, GL_STATIC_DRAW);


    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), 0);





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
    "   color = vec4(1.0, 0.0, 0.0, 1.0);\n"
    "}\n";

    uint shader = CreateShader(vertexShader, fragmentShader);
    glUseProgram(shader);

    // Loop until the user closes the window
    while (!glfwWindowShouldClose(window)){

        // Render Here
        /* clears the specified buffers with the defined colors in glClearColor/glClearDepth/glClearStencil*/
        glClear(GL_COLOR_BUFFER_BIT);


        /*Using Modern OpenGl*/

        // If index buffer is not defined 
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // If index defined
        // glDrawElements(GL_TRIANGLES, 3, );

        /* Using Legacy OpenGL*/

        // glBegin(GL_TRIANGLES);
        // glVertex2f(-0.5f, -0.5f);
        // glVertex2f(0.0f, 0.5f  );
        // glVertex2f(0.5f, -0.5f );
        // glEnd();

        //Swap front and back buffers
        glfwSwapBuffers(window);

        // Pool for and process events
        glfwPollEvents();

    }

    glfwTerminate();
    return 0;
}








