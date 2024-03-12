#pragma once
#ifndef _MATERIAL_HPP
#define _MATERIAL_HPP

#include <glm/glm.hpp>
#include <memory>

#include "Texture.hpp"

namespace iris
{
    class Material
    {
    public:
        Material();
        ~Material();

    private:
        glm::vec3 diffuse;
        glm::vec3 specular;
        glm::vec3 ambient;
    };
}

#endif