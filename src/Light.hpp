#pragma once
#ifndef _LIGHT_HPP
#define _LIGHT_HPP

#include <glm/glm.hpp>

namespace iris
{
    class Light
    {
    public:
        virtual ~Light() {};

        virtual const glm::vec4& getColor() const { return color; }
        virtual void setColor(const glm::vec4& lightColor) { color = lightColor; }

        virtual const glm::vec3& getPosition() const { return position; }
        virtual void setPosition(const glm::vec3 lightPosition) { position = lightPosition; }

        virtual float getIntensity() { return intensity; }
        virtual void setIntensity(float lightIntensity) { intensity = lightIntensity; }

    protected:
        glm::vec4 color;
        glm::vec3 position;
        float intensity;
    };
}

#endif