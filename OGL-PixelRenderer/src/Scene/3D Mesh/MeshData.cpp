#include "MeshData.h"

MeshData::MeshData(
    std::string nm,
    const std::vector<Vertex>& verts, 
    const std::vector<GLuint>& idxs, 
    Material* mat) : name(nm), vertices(verts), indices(idxs)
{
    material = mat;

    glGenVertexArrays(1, &_vertexArray);
    glGenBuffers(1, &_vertexBuffer);
    glGenBuffers(1, &_indexBuffer);

    glBindVertexArray(_vertexArray);

    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    // vertex normals
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);
    // vertex texture coords
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, texUv));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

MeshData::~MeshData()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteVertexArrays(1, &_vertexArray);
    glDeleteBuffers(1, &_vertexBuffer);
    glDeleteBuffers(1, &_indexBuffer);

    delete material;
}

void MeshData::SetMaterial(Material* mat) { material = mat; }

void MeshData::Draw() {
    material->Use();

    glBindVertexArray(_vertexArray);
    //glDrawArrays(GL_TRIANGLES, 0, vertices.size());
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
}