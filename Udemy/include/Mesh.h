#pragma once

#include <GL/glew.h>

class Mesh
{

 public:
    Mesh() : VAO(0), VBO(0), IBO(0), indexCount(0){};
    ~Mesh();

 private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;

 public:

    void CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numberOfIndices);
    void RenderMesh();
    void ClearMesh();


};