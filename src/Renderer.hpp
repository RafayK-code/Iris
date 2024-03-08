#pragma once
#ifndef _RENDERER_HPP
#define _RENDERER_HPP

#include <glm/glm.hpp>

#include "RenderObject.hpp"

namespace iris
{
    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        void clear();
        void setClearColor(const glm::vec4& color);
        void draw(const RenderObject& object, GLenum mode = GL_TRIANGLES);

    };
}

#endif