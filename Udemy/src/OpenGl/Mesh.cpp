#include "Mesh.h"




void Mesh::CreateMesh(GLfloat* vertices, unsigned int* indices, unsigned int numOfVertices, unsigned int numberOfIndices)
{

    indexCount = numberOfIndices;
    unsigned int indexTypeSize = sizeof(indices[0]);
    unsigned int vertexTypeSize = sizeof(vertices[0]);

    // VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    // IBO
    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexTypeSize * indexCount, indices, GL_STATIC_DRAW);
    // VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertexTypeSize * numOfVertices, vertices, GL_STATIC_DRAW);
    // Attributes
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0])*8, 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0])*8, (void*)(sizeof(vertices[0])*3));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0])*8, (void*)(sizeof(vertices[0])*5));
    glEnableVertexAttribArray(2);
    // Unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

}

void Mesh::RenderMesh()
{
    // Can write condition to check if VAO exists
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Mesh::ClearMesh()
{
    if(IBO) {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }
    if(VBO) {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if(VAO) {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }

    indexCount = 0;
}

Mesh::~Mesh()
{
    ClearMesh();
}