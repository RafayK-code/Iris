#pragma once
#ifndef _VAO_HPP
#define _VAO_HPP

#include <GL/glew.h>

#include "VBO.hpp"

namespace iris::backend
{
    class VAO
    {
    public:
        VAO();
        ~VAO();

        VAO(const VAO&) = delete;
        VAO& operator=(const VAO&) = delete;

        void linkAttribute(const VBO& vbo, GLuint layout, GLuint numComponents, GLenum type, GLsizeiptr stride, GLvoid* offset);

        GLuint getID() const;

        void bind() const;
        void unbind() const;
    
    private:
        GLuint vaoID;
    };
};

#endif