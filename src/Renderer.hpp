#pragma once
#ifndef _RENDERER_HPP
#define _RENDERER_HPP

#include <glm/glm.hpp>

#include "Mesh.hpp"

namespace iris
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        void clear();
        void setClearColor(const glm::vec4& color);
        void drawMesh(const Mesh& mesh);
        
    private:

    };
}

#endif