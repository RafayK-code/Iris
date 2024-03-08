#include "Renderer.hpp"

#include <GL/glew.h>

namespace iris
{
    Renderer::Renderer()
    {
    }

    Renderer::~Renderer()
    {
    }

    void Renderer::clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void Renderer::draw(const RenderObject& object, GLenum mode = GL_TRIANGLES)
    {
        object.getMesh().getVAO().bind();
        object.getMesh().getEBO().bind();
        glDrawElements(mode, object.getMesh().getElements(), GL_UNSIGNED_INT, 0);
        object.getMesh().getEBO().unbind();
    }
}