#pragma once

#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include <string>
#include <vector>
#include <glad/glad.h>

//#include "../Animation/Joint.h"

#include "Material.h"
#include "../../Data Types/Vertex.h"
#include "../../Data Types/Texture.h"

class MeshData
{
private:
	GLuint _vertexArray, _vertexBuffer, _indexBuffer;
	//Joint _rootJoint;
	//unsigned int _joint	Count;
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;
	std::string name;

	Material* material = nullptr;
	void Draw();
	void SetMaterial(Material* mat);

	MeshData(std::string name, const std::vector<Vertex>& verts, const std::vector<GLuint>& idxs, Material *mat);
	~MeshData();
};

