#pragma once
#ifndef _MESH_HPP
#define _MESH_HPP

#include <GL/glew.h>

#include <vector>
#include <memory>

#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"

namespace iris
{
    class Mesh
    {
    public:
        Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
        ~Mesh();

        const VAO& getVAO() const;
        const EBO& getEBO() const;

        uint32_t getElements() const;

    private:
        VAO vao;
        std::unique_ptr<VBO> vbo;
        std::unique_ptr<EBO> ebo;

        uint32_t eboSize;
    };
}

#endif