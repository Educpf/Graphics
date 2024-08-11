#include "Renderer.h"

#include <iostream>

void GLCLearError() {
    // get errors just to clean them
    while (glGetError() != GL_NO_ERROR);  // or !glGetError()
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

bool GLLOGCall(const char* function, const char* file, int line) {
    // While error is different than 0
    if (GLenum error = glGetError()) {
        std::cout << "[OpenGl Error]: (" << error << " - "
                  << GetGLErrorString(error) << "): " << function << " " << file
                  << ":" << line << std::endl;
        return false;
    }
    return true;
}

void Renderer::Clear() const
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib,
                    const Shader& shader) const {
    shader.Bind();
    va.Bind();
    GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
