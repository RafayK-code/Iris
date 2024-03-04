#pragma once
#ifndef _VBO_HPP
#define _VBO_HPP

#include <GL/glew.h>

#include <vector>

#include "Vertex.hpp"

namespace iris
{
    class VBO
    {
    public:
        VBO(std::vector<Vertex>& vertices);
        ~VBO();

        GLuint getID() const;

        void bind() const;
        void unbind() const;

    private:
        GLuint vboID;
    };
}

#endif