#include "OrthographicCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace iris
{
    OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
        : rotation(0.0f)
    {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        projectionMatrix = glm::ortho(left, right, bottom, top);

        updateViewMatrix();
    }

    OrthographicCamera::~OrthographicCamera()
    {
    }

    void OrthographicCamera::updateViewMatrix() 
    {
        glm::mat4 transform = glm::translate(glm::mat4(1.0f), position) * glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0, 0, 1));

        viewMatrix = glm::inverse(transform);
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

    float OrthographicCamera::getRotation() const 
    {
        return rotation;
    }

    void OrthographicCamera::setRotation(float newRotation)
    {
        rotation = newRotation;
        updateViewMatrix();
    }
}