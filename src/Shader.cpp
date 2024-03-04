#include "Shader.hpp"

#include <fstream>
#include <sstream>
#include <cerrno>

namespace iris
{

    Shader::Shader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
    {
        std::string vertexCode = getFileContents(vertexShaderFile);
        std::string fragmentCode = getFileContents(fragmentShaderFile);

        const char* vertexSource = vertexCode.c_str();
        const char* fragmentSource = fragmentCode.c_str();

        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexSource, nullptr);
        glCompileShader(vertexShader);

        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragmentShader, 1, &fragmentSource, nullptr);
        glCompileShader(fragmentShader);

        shaderID = glCreateProgram();
        glAttachShader(shaderID, vertexShader);
        glAttachShader(shaderID, fragmentShader);

        glLinkProgram(shaderID);

        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
    }

    Shader::~Shader()
    {
        glDeleteProgram(shaderID);
    }

    void Shader::activate()
    {
        glUseProgram(shaderID);
    }

    std::string Shader::getFileContents(const std::string& filename)
    {
        std::ifstream file(filename, std::ios::binary);

        if (!file.is_open())
            throw errno;
            
        std::string contents;

        file.seekg(0, std::ios::end);
        contents.resize(file.tellg());
        file.seekg(0, std::ios::beg);
        file.read(&contents[0], contents.size());
        file.close();

        return contents;
    }

}