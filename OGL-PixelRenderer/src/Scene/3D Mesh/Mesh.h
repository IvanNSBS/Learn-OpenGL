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

	glm::mat4 localTransform;

	Mesh(std::string name);
	~Mesh();

	void Draw();
	void AddMeshData(MeshData* data);
	void AddChild(Mesh* child);
	void PrintTree() {
		PrintChildTree(this, 0);
	}
private:

	void PrintChildTree(Mesh* mesh, size_t depth) {
		std::string start = "|-";
		std::string dash = std::string(depth*2, '-');
		std::cout << start + dash << mesh->name;
		
		int vertexCount = 0;
		for (auto data : _meshDataList)
			vertexCount += data->vertices.size();
		
		std::cout << " | Vertex Size: " << vertexCount << "\n" ;

		if (mesh->childs.size() == 0)
			return;
		
		for (auto child : mesh->childs) {
			PrintChildTree(child, depth+1);
		}

	}



	std::vector<MeshData*> _meshDataList;
};

