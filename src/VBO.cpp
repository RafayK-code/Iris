#include "VBO.hpp"

namespace iris
{
    VBO::VBO(std::vector<Vertex>& vertices)
    {
        glGenBuffers(1, &vboID);
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), vertices.data(), GL_STATIC_DRAW);
    }

    VBO::~VBO()
    {
        glDeleteBuffers(1, &vboID);
    }

    GLuint VBO::getID() const
    {
        return vboID;
    }
    
    void VBO::bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, vboID);
    }

    void VBO::unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}