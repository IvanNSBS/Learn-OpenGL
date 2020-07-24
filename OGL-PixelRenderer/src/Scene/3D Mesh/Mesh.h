#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <glad/glad.h>

#include "MeshData.h"
#include "../Animation/Joint.h"

#include "Material.h"
#include "../../ImGuiWindows/PropertyWindow/PR_PropertyDef.h"


class Mesh
{
public:

	std::vector<Mesh*> childs;
	std::string name;

	Mesh(std::string name);
	~Mesh();

	void Draw();
	void AddMeshData(MeshData* data);
private:

	std::vector<MeshData*> _meshDataList;
};

