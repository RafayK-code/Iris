#pragma once
#ifndef _VAO_HPP
#define _VAO_HPP

#include <GL/glew.h>

#include "VBO.hpp"

namespace iris
{
    class VAO
    {
    public:
        VAO();
        ~VAO();

        void linkAttribute(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, GLvoid* offset);
    
    private:
        GLuint vaoID;
    };
};

#endif