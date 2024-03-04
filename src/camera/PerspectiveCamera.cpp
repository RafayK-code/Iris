#include "PerspectiveCamera.hpp"

#include <glm/gtc/matrix_transform.hpp>

namespace iris
{
    PerspectiveCamera::PerspectiveCamera(float fov, float aspectRatio, float near, float far)
        : pitch(0.0f), yaw(-90.0f), roll(0.0f)
    {
        position = glm::vec3(0.0f, 0.0f, 0.0f);
        projectionMatrix = glm::perspective(fov, aspectRatio, near, far);
        updateViewMatrix();
    }

    PerspectiveCamera::~PerspectiveCamera()
    {
    }

    void PerspectiveCamera::updateViewMatrix()
    {
        glm::vec3 fr;
        fr.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
        fr.y = glm::sin(glm::radians(pitch));
        fr.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));

        front = glm::normalize(fr);
        right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
        up = glm::normalize(glm::cross(right, front));

        viewMatrix = glm::lookAt(position, position + front, up);
        viewProjectionMatrix = projectionMatrix * viewMatrix;
    }

    const glm::vec3& PerspectiveCamera::getUp() const 
    {
        return up;
    }

    const glm::vec3& PerspectiveCamera::getRight() const 
    {
        return right;
    }

    const glm::vec3& PerspectiveCamera::getForward() const 
    {
        return front;
    }

    float PerspectiveCamera::getPitch() const 
    {
        return pitch;
    }

    void PerspectiveCamera::setPitch(float newPitch)
    {
        pitch = newPitch;
        updateViewMatrix();
    }

    float PerspectiveCamera::getYaw() const 
    {
        return yaw;
    }

    void PerspectiveCamera::setYaw(float newYaw)
    {
        yaw = newYaw;
        updateViewMatrix();
    }

    float PerspectiveCamera::getRoll() const 
    {
        return roll;
    }

    void PerspectiveCamera::setRoll(float newRoll)
    {
        roll = newRoll;
        updateViewMatrix();
    }
}