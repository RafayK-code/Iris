#include "VAO.hpp"

namespace iris
{
    VAO::VAO()
    {

    }

    void VAO::linkAttribute(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, GLvoid* offset)
    {
        vbo.bind();
        glVertexAttribPointer(layout, numComponents, type, GL_FALSE, stride, offset);
        glEnableVertexAttribArray(layout);
        vbo.unbind();
    }
}