#pragma once
#ifndef _ORTHOGRAPHIC_CAMERA_HPP
#define _ORTHOGRAPHIC_CAMERA_HPP

#include "Camera.hpp"

namespace iris
{
    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera(float left, float right, float bottom, float top);
        ~OrthographicCamera();

        float getRotation() const;
        void setRotation(float rotation);

    protected:
        void updateViewMatrix() override;

    private:
        float rotation;
    };
}

#endif