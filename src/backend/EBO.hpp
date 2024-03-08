#pragma once
#ifndef _EBO_HPP
#define _EBO_HPP

#include <GL/glew.h>

#include <vector>

namespace iris::backend
{
    class EBO
    {
    public:
        EBO(std::vector<GLuint>& indices);
        ~EBO();

        EBO(const EBO&) = delete;
        EBO& operator=(const EBO&) = delete;

        GLuint getID() const;

        void bind() const;
        void unbind() const;

    private:
        GLuint eboID;
    };
}

#endif