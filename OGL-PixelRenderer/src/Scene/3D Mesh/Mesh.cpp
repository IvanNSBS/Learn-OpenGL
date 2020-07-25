#include "Mesh.h"


Mesh::Mesh (std::string nm) : name(nm){ }
Mesh::~Mesh() { }

void Mesh::Draw() {
    for (auto meshData : _meshDataList)
        meshData->Draw();

    for (auto child : childs)
        child->Draw();
}

void Mesh::AddMeshData(MeshData* data)
{
    _meshDataList.push_back(data);
    localTransform = data->transform;
}

void Mesh::AddChild(Mesh* child)
{
    childs.push_back(child);
}
