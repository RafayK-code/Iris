#include "VAO.hpp"

namespace iris
{
    VAO::VAO()
    {
        glGenVertexArrays(1, &vaoID);
    }

    VAO::~VAO()
    {
        glDeleteVertexArrays(1, &vaoID);
    }

    void VAO::linkAttribute(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, GLvoid* offset)
    {
        vbo.bind();
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        vbo.unbind();
    }

    GLuint VAO::getID() const 
    {
        return vaoID;
    }

    void VAO::bind() const
    {
        glBindVertexArray(vaoID);
    }

    void VAO::unbind() const
    {
        glBindVertexArray(0);
    }
}