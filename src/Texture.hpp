#pragma once
#ifndef _TEXTURE_HPP
#define _TEXTURE_HPP

#include <GL/glew.h>
#include <string>

#include "Shader.hpp"

namespace iris
{
    class Texture
    {
    public:
        Texture(const std::string& image, const std::string& texType, GLuint slot, GLenum format, GLenum pixelType);
        ~Texture();

        void texUnit(const Shader& shader, const std::string& uniform);

        GLuint getID() const;
        std::string getType() const;

        void bind() const;
        void unbind() const;

    private:
        GLuint texID;
        GLuint unit;
        std::string type;
    };
}

#endif