#include "Mesh.hpp"

namespace iris
{
    Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<GLuint>& indices)
        : vao(VAO()), eboSize(indices.size())
    {
        vao.bind();

        vbo = std::make_unique<VBO>(vertices);
        ebo = std::make_unique<EBO>(indices);

        vao.linkAttribute(*vbo, 0, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(0 * sizeof(GL_FLOAT)));
        vao.linkAttribute(*vbo, 1, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(3 * sizeof(GL_FLOAT)));
        vao.linkAttribute(*vbo, 2, 3, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(6 * sizeof(GL_FLOAT)));
        vao.linkAttribute(*vbo, 3, 2, GL_FLOAT, 11 * sizeof(GL_FLOAT), (GLvoid*)(9 * sizeof(GL_FLOAT)));

        vbo->unbind();
        ebo->unbind();
        vao.unbind();
    }

    Mesh::~Mesh()
    {
    }

    const VAO& Mesh::getVAO() const
    {
        return vao;
    }

    const EBO& Mesh::getEBO() const
    {
        return *ebo;
    }

    uint32_t Mesh::getElements() const
    {
        return eboSize;
    }
}