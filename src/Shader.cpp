#include "Shader.hpp"

#include <glm/gtc/type_ptr.hpp>

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

    GLuint Shader::getID() const 
    {
        return shaderID;
    }

    void Shader::activate() const
    {
        glUseProgram(shaderID);
    }

    void Shader::setUniform4f(const std::string& name, const glm::vec4& vec)
    {
        glUniform4f(getUniformLocation(name), vec.x, vec.y, vec.z, vec.w);
    }

    void Shader::setUniform3f(const std::string& name, const glm::vec3& vec)
    {
        glUniform3f(getUniformLocation(name), vec.x, vec.y, vec.z);
    }

    void Shader::setUniform2f(const std::string& name, const glm::vec2& vec)
    {
        glUniform2f(getUniformLocation(name), vec.x, vec.y);
    }

    void Shader::setUniformMatrix4fv(const std::string& name, const glm::mat4& mat)
    {
        glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    GLuint Shader::getUniformLocation(const std::string& name)
    {
        if (uniformCache.find(name) == uniformCache.end())
            uniformCache[name] = glGetUniformLocation(shaderID, name.c_str());

        return uniformCache[name];
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