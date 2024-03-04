#pragma once
#ifndef _VERTEX_HPP
#define _VERTEX_HPP

#include <glm/glm.hpp>

namespace iris
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 color;
        glm::vec2 texUV;
    };
}

#endif