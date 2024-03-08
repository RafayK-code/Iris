#pragma once
#ifndef _RENDER_OBJECT_HPP
#define _RENDER_OBJECT_HPP

#include <glm/glm.hpp>

#include "Mesh.hpp"

namespace iris
{
    class RenderObject
    {
    public:
        RenderObject(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
        ~RenderObject();

        void identity();

        void translate(const glm::vec3& translation);
        void rotate(float angle, const glm::vec3& axis);
        void scale(const glm::vec3& scaling);

        const Mesh& getMesh() const;
        const glm::mat4& getModelMatrix() const;

    private:
        Mesh mesh;
        glm::mat4 modelMatrix;
    };
}

#endif