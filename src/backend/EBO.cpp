#include "EBO.hpp"

namespace iris::backend
{
    EBO::EBO(std::vector<GLuint>& indices)
    {
        glGenBuffers(1, &eboID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(GLuint), indices.data(), GL_STATIC_DRAW);
    }

    EBO::~EBO()
    {
        glDeleteBuffers(1, &eboID);
    }

    GLuint EBO::getID() const
    {
        return eboID;
    }

    void EBO::bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboID);
    }

    void EBO::unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}