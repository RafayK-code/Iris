#pragma once
#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <GL/glew.h>

#include <string>

namespace iris
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Shader();

        void activate();
        //void destroy();
    private:
        std::string getFileContents(const std::string& filename);

        GLuint shaderID;
    };
}

#endif