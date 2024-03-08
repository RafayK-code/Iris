#pragma once
#ifndef _SHADER_HPP
#define _SHADER_HPP

#include <GL/glew.h>
#include <glm/glm.hpp>

#include <string>
#include <unordered_map>

namespace iris
{
    class Shader
    {
    public:
        Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
        ~Shader();

        GLuint getID() const;

        void activate() const;

        void setUniform4f(const std::string& name, const glm::vec4& vec);
        void setUniform3f(const std::string& name, const glm::vec3& vec);
        void setUniform2f(const std::string& name, const glm::vec2& vec);

        void setUniformMatrix4fv(const std::string& name, const glm::mat4& mat);
    private:
        std::string getFileContents(const std::string& filename);
        GLuint getUniformLocation(const std::string& name);

        GLuint shaderID;
        std::unordered_map<std::string, GLuint> uniformCache;
    };
}

#endif