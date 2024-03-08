#include "RenderObject.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace iris
{
    RenderObject::RenderObject(std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
        : mesh(vertices, indices), modelMatrix(glm::mat4(1.0f))
    {   
    }

    RenderObject::~RenderObject()
    {
    }

    void RenderObject::identity()
    {
        modelMatrix = glm::mat4(1.0f);
    }

    void RenderObject::translate(const glm::vec3& translation)
    {
        modelMatrix = glm::translate(modelMatrix, translation);
    }

    void RenderObject::rotate(float angle, const glm::vec3& axis)
    {
        modelMatrix = glm::rotate(modelMatrix, angle, axis);
    }

    void RenderObject::scale(const glm::vec3& scaling)
    {
        modelMatrix = glm::scale(modelMatrix, scaling);
    }

    const Mesh& RenderObject::getMesh() const
    {
        return mesh;
    }

    const glm::mat4& RenderObject::getModelMatrix() const
    {
        return modelMatrix;
    }
}