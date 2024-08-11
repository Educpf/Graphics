#pragma once

#include <GL/glew.h>
#include <signal.h>

#include "VertexArray.h"
#include "IndexBuffer.h"
#include "Shader.h"

#define ASSERT(x) \
    if (!(x)) raise(SIGTRAP)

#define GLCall(x)   \
    GLCLearError(); \
    x;              \
    ASSERT(GLLOGCall(#x, __FILE__, __LINE__))

void GLCLearError();

const char* GetGLErrorString(GLenum error);

bool GLLOGCall(const char* function, const char* file, int line);


class Renderer
{

 public:
    void Clear() const;
    void Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const;


};
