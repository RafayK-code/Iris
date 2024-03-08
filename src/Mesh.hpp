#pragma once
#ifndef _MESH_HPP
#define _MESH_HPP

#include <GL/glew.h>

#include <vector>
#include <memory>

#include "backend/VAO.hpp"
#include "backend/VBO.hpp"
#include "backend/EBO.hpp"

namespace iris
{
    class Mesh
    {
    public:
        Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices);
        ~Mesh();

        const backend::VAO& getVAO() const;
        const backend::EBO& getEBO() const;

        uint32_t getElements() const;

    private:
        backend::VAO vao;
        std::unique_ptr<backend::VBO> vbo;
        std::unique_ptr<backend::EBO> ebo;

        uint32_t eboSize;
    };
}

#endif