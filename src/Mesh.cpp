#include "Mesh.hpp"

namespace iris
{
    Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
        : vao(backend::VAO()), eboSize(indices.size())
    {
        vao.bind();

        vbo = std::make_unique<backend::VBO>(vertices);
        ebo = std::make_unique<backend::EBO>(indices);

        vao.linkAttribute(*vbo, 0, 3, GL_FLOAT, 11 * sizeof(GLfloat), (GLvoid*)(0 * sizeof(GLfloat)));
        vao.linkAttribute(*vbo, 1, 3, GL_FLOAT, 11 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
        vao.linkAttribute(*vbo, 2, 3, GL_FLOAT, 11 * sizeof(GLfloat), (GLvoid*)(6 * sizeof(GLfloat)));
        vao.linkAttribute(*vbo, 3, 2, GL_FLOAT, 11 * sizeof(GLfloat), (GLvoid*)(9 * sizeof(GLfloat)));

        vbo->unbind();
        ebo->unbind();
        vao.unbind();
    }

    Mesh::~Mesh()
    {
    }

    const backend::VAO& Mesh::getVAO() const
    {
        return vao;
    }

    const backend::EBO& Mesh::getEBO() const
    {
        return *ebo;
    }

    uint32_t Mesh::getElements() const
    {
        return eboSize;
    }
}