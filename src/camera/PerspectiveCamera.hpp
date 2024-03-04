#pragma once
#ifndef _PERSPECTIVE_CAMERA_HPP
#define _PERSPECTIVE_CAMERA_HPP

#include "Camera.hpp"

namespace iris
{
    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(float fov, float aspectRatio, float near, float far);
        ~PerspectiveCamera();

        const glm::vec3& getUp() const;
        const glm::vec3& getRight() const;
        const glm::vec3& getForward() const;

        float getPitch() const;
        void setPitch(float pitch);

        float getYaw() const;
        void setYaw(float yaw);

        float getRoll() const;
        void setRoll(float roll);

    protected:
        void updateViewMatrix() override;

    private:
        glm::vec3 right;
        glm::vec3 up;
        glm::vec3 front;

        float pitch;  //x-axis
        float yaw;    //y-axis
        float roll;   //z-axis
    };
}

#endif