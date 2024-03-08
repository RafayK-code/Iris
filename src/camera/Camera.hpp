#pragma once
#ifndef _CAMERA_HPP
#define _CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.hpp"

namespace iris
{
    class Camera
    {
    public:
        virtual ~Camera() {};

        const glm::vec3& getPosition() const { return position; }

        virtual void setPosition(const glm::vec3& newPosition)
        {
            position = newPosition;
            updateViewMatrix();
        }

        const glm::mat4& getProjectionMatrix() const { return projectionMatrix; }
        const glm::mat4& getViewMatrix() const { return viewMatrix; }
        const glm::mat4& getViewProjectionMatrix() const { return viewProjectionMatrix; }

        void setShaderMatrix(const Shader& shader, const std::string& uniform)
        {
            glUniformMatrix4fv(glGetUniformLocation(shader.getID(), uniform.c_str()), 1, GL_FALSE, glm::value_ptr(viewProjectionMatrix));
        }

    protected:
        virtual void updateViewMatrix() = 0;

        glm::vec3 position;

        glm::mat4 viewMatrix;
        glm::mat4 projectionMatrix;
        glm::mat4 viewProjectionMatrix;
    };
}

#endif