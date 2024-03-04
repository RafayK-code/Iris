#include "Texture.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace iris
{
    Texture::Texture(const std::string& image, const std::string& texType, GLuint slot, GLenum format, GLenum pixelType)
        : type(texType), unit(slot)
    {
        int widthImg, heightImg, numColCh;
        stbi_set_flip_vertically_on_load(true);
        unsigned char* bytes = stbi_load(image.c_str(), &widthImg, &heightImg, &numColCh, 0);

        glGenTextures(1, &texID);
        glActiveTexture(GL_TEXTURE0 + slot);
        glBindTexture(GL_TEXTURE_2D, texID);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, widthImg, heightImg, 0, format, pixelType, bytes);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(bytes);
    }

    Texture::~Texture()
    {
        glDeleteTextures(1, &texID);
    }

    void Texture::texUnit(const Shader& shader, const std::string& uniform)
    {
        GLuint texUni = glGetUniformLocation(shader.getID(), uniform.c_str());
        shader.activate();
        glUniform1i(texUni, unit);
    }

    void Texture::bind() const
    {
        glActiveTexture(GL_TEXTURE0 + unit);
        glBindTexture(GL_TEXTURE_2D, texID);
    }

    void Texture::unbind() const 
    {
        glBindTexture(GL_TEXTURE_2D, 0);
    }
}